#include <csignal>
#include <iostream>
#include <ranges>

#include <argparse/argparse.hh>
#include <indicators/indicators.hh>
#include <tinyxml2/tinyxml2.hh>

#include <rt/common/exception.hh>
#include <rt/loaders/scene_loader.hh>
#include <rt/renderer/renderer.hh>
#include <rt/writers/image_writer.hh>

static void OnExit();
static void OnSignal(int);
static void ListFormats(const std::string&);
static void ApplyCommandLineArgs(argparse::ArgumentParser& parser,
                                 rt::Scene& scene);

int main(int argc, char* argv[]) {
  using namespace std::chrono_literals;

  std::atexit(OnExit);
  signal(SIGINT, OnSignal);
  signal(SIGABRT, OnSignal);
  signal(SIGTERM, OnSignal);
  signal(SIGTSTP, OnSignal);

  argparse::ArgumentParser parser{"ray-tracer"};
  parser.add_argument("input_file").required().help("XML input file");
  parser.add_argument("-r", "--resolution")
      .nargs(2)
      .scan<'u', std::size_t>()
      .help("custom resolution (width, height)");
  parser.add_argument("-b", "--background")
      .nargs(3)
      .scan<'g', double>()
      .help("custom background (red, green, blue)");
  parser.add_argument("-m", "--max-bounces")
      .scan<'u', std::size_t>()
      .help("custom max bounces");
  parser.add_argument("-d", "--duration")
      .scan<'g', double>()
      .default_value<double>(0)
      .help("animation duration in seconds");
  parser.add_argument("--fps")
      .scan<'u', std::size_t>()
      .default_value<std::size_t>(30)
      .help("frames per second");
  parser.add_argument("-o", "--output")
      .default_value("image.png")
      .help("output file");
  parser.add_argument("--formats")
      .action(ListFormats)
      .default_value(false)
      .implicit_value(true)
      .help("list supported formats");

  try {
    parser.parse_args(argc, argv);
  } catch (const std::exception& err) {
    std::cerr << err.what() << std::endl;
    std::cerr << parser;
    return EXIT_FAILURE;
  }

  try {
    tinyxml2::XMLDocument input_file{};
    const auto input_file_path = parser.get("input_file");
    input_file.LoadFile(input_file_path.c_str());
    if (input_file.Error()) {
      throw rt::RuntimeError{"Could not load {}, {}", input_file_path,
                             input_file.ErrorStr()};
    }

    std::cout << "Loading " << input_file_path << std::endl;
    auto root = input_file.RootElement();
    auto directory = std::filesystem::path{input_file_path}.remove_filename();
    rt::SceneLoader loader{root, directory};
    auto scene = loader.Load();
    ApplyCommandLineArgs(parser, *scene);
    // std::cout << scene->ToString() << std::endl;

    auto duration = parser.get<double>("duration");
    auto fps = parser.get<std::size_t>("fps");
    auto frames = std::max<std::size_t>(1, duration * fps);
    std::filesystem::path output_file = parser.get<std::string>("output");
    rt::ImageWriter writer{output_file, scene->camera().width(),
                           scene->camera().height(), frames, fps};

    indicators::show_console_cursor(false);
    indicators::ProgressBar bar{
        indicators::option::BarWidth{50},
        indicators::option::MaxProgress{frames * scene->camera().height()},
        indicators::option::ShowPercentage{true},
        indicators::option::ShowElapsedTime{true},
        indicators::option::ShowRemainingTime{true}};
    rt::Renderer renderer{*scene, [&](auto) { bar.tick(); }};

    for (std::size_t f = 0; f < frames; ++f) {
      bar.set_option(indicators::option::PrefixText{
          std::format("Rendering frame {}/{} ", f + 1, frames)});
      scene->SetTime(1000ms * f / fps);
      auto image = renderer.Render();
      writer.Write(*image, f);
    }
  } catch (const std::exception& err) {
    std::cerr << err.what() << std::endl;
    return EXIT_FAILURE;
  }
}

static void OnExit() {
  indicators::show_console_cursor(true);
}

static void OnSignal(int) {
  OnExit();
  std::exit(EXIT_SUCCESS);
}

static void ListFormats(const std::string&) {
  auto formats = rt::ImageWriter::Formats();
  std::cout << "Supported formats: "
            << std::accumulate(std::next(formats.begin()), formats.end(),
                               formats[0],
                               [](auto a, auto b) { return a + ", " + b; })
            << std::endl;
  std::exit(EXIT_SUCCESS);
}

static void ApplyCommandLineArgs(argparse::ArgumentParser& parser,
                                 rt::Scene& scene) {
  auto resolution = parser.present<std::vector<std::size_t>>("-r");
  if (resolution.has_value()) {
    scene.camera().SetResolution((*resolution)[0], (*resolution)[1]);
  }
  auto background = parser.present<std::vector<double>>("-b");
  if (background.has_value()) {
    scene.SetBackground({(*background)[0], (*background)[1], (*background)[2]});
  }
  auto max_bounces = parser.present<std::size_t>("max-bounces");
  if (max_bounces.has_value()) {
    scene.camera().SetMaxBounces(*max_bounces);
  }
}
