#include <rt/common/strings.hh>

#include "image_writer.hh"

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libswscale/swscale.h>
}

namespace rt::details {

class FFmpegImplementation : public ImageWriterImplementation {
 public:
  explicit FFmpegImplementation(const std::filesystem::path& path,
                                std::size_t width, std::size_t height,
                                std::size_t frames, std::size_t fps)
      : path_{path} {
    avformat_alloc_output_context2(&format_ctx_, nullptr, nullptr,
                                   path_.c_str());
    auto codec = avcodec_find_encoder(format_ctx_->oformat->video_codec);
    packet_ = av_packet_alloc();
    stream_ = avformat_new_stream(format_ctx_, codec);
    stream_->id = 0;
    stream_->time_base.num = 1;
    stream_->time_base.den = fps;
    codec_ctx_ = avcodec_alloc_context3(codec);
    codec_ctx_->codec_id = format_ctx_->oformat->video_codec;
    codec_ctx_->bit_rate = 5'000'000;
    codec_ctx_->width = width;
    codec_ctx_->height = height;
    codec_ctx_->time_base = stream_->time_base;
    codec_ctx_->gop_size = fps;
    codec_ctx_->pix_fmt = AV_PIX_FMT_YUV420P;
    if (format_ctx_->oformat->flags & AVFMT_GLOBALHEADER) {
      codec_ctx_->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
    }
    avcodec_open2(codec_ctx_, codec, nullptr);
    frame_ = av_frame_alloc();
    frame_->format = codec_ctx_->pix_fmt;
    frame_->width = codec_ctx_->width;
    frame_->height = codec_ctx_->height;
    av_frame_get_buffer(frame_, 0);
    avcodec_parameters_from_context(stream_->codecpar, codec_ctx_);
    av_dump_format(format_ctx_, 0, path_.c_str(), 1);
    avio_open(&format_ctx_->pb, path_.c_str(), AVIO_FLAG_WRITE);
    avformat_write_header(format_ctx_, nullptr);

    sws_ctx_ = sws_getContext(width, height, AV_PIX_FMT_RGBA, width, height,
                              codec_ctx_->pix_fmt, SWS_BICUBIC, nullptr,
                              nullptr, nullptr);
  }

  ~FFmpegImplementation() noexcept {
    auto ret = avcodec_send_frame(codec_ctx_, nullptr);
    while (ret >= 0) {
      ret = avcodec_receive_packet(codec_ctx_, packet_);
      if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
        break;
      }
      av_packet_rescale_ts(packet_, codec_ctx_->time_base, stream_->time_base);
      packet_->stream_index = stream_->index;
      av_interleaved_write_frame(format_ctx_, packet_);
    }
    av_write_trailer(format_ctx_);
    avcodec_free_context(&codec_ctx_);
    av_frame_free(&frame_);
    av_packet_free(&packet_);
    avio_closep(&format_ctx_->pb);
    avformat_free_context(format_ctx_);
    sws_freeContext(sws_ctx_);
  }

  void Write(const Image& image, std::size_t frame) override {
    av_frame_make_writable(frame_);
    auto buffer = image.ToRGBABuffer();
    uint8_t* src_data[1];
    src_data[0] = buffer.data();
    int src_linesize[1];
    src_linesize[0] = 4 * image.width();
    sws_scale(sws_ctx_, src_data, src_linesize, 0, image.height(), frame_->data,
              frame_->linesize);
    frame_->pts = next_pts_++;
    auto ret = avcodec_send_frame(codec_ctx_, frame_);
    while (ret >= 0) {
      ret = avcodec_receive_packet(codec_ctx_, packet_);
      if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
        break;
      }
      av_packet_rescale_ts(packet_, codec_ctx_->time_base, stream_->time_base);
      packet_->stream_index = stream_->index;
      av_interleaved_write_frame(format_ctx_, packet_);
    }
  }

  static std::vector<std::string> Formats() noexcept {
    std::vector<std::string> formats;
    void* opaque = nullptr;
    while (auto format = av_muxer_iterate(&opaque)) {
      if (format && format->extensions && format->mime_type &&
          std::string_view{format->mime_type}.starts_with("video/")) {
        auto extensions = Split(format->extensions, ",");
        formats.insert(formats.end(), extensions.begin(), extensions.end());
      }
    }
    return formats;
  }

  static bool Supports(const std::filesystem::path& path) noexcept {
    if (path.has_extension()) {
      auto ext = path.extension().string().substr(1);
      for (auto format : Formats()) {
        if (format == ext) {
          return true;
        }
      }
    }
    return false;
  }

 private:
  std::filesystem::path path_;
  AVFormatContext* format_ctx_;
  AVCodecContext* codec_ctx_;
  AVPacket* packet_;
  AVStream* stream_;
  AVFrame* frame_;
  int64_t next_pts_{0};
  SwsContext* sws_ctx_;
};

[[gnu::constructor]] static void RegisterFFmpegImplementation() {
  ImageWriter::Register<FFmpegImplementation>();
}

}  // namespace rt::details
