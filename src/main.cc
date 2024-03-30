#include <iostream>

#include <argparse/argparse.hh>
#include <tinyxml2/tinyxml2.hh>

#include <rt/common/exception.hh>
#include <rt/loaders/scene_loader.hh>
#include <rt/renderer/renderer.hh>
#include <rt/writers/image_writer.hh>

static void ApplyCommandLineArgs(argparse::ArgumentParser& parser,
                                 rt::Scene& scene) {
  auto resolution = parser.present<std::vector<std::size_t>>("-r");
  if (resolution.has_value()) {
    scene.camera()->SetResolution(resolution->at(0), resolution->at(1));
  }
  auto background = parser.present<std::vector<double>>("-b");
  if (background.has_value()) {
    scene.SetBackground({
        std::clamp(background->at(0), 0.0, 1.0),
        std::clamp(background->at(1), 0.0, 1.0),
        std::clamp(background->at(2), 0.0, 1.0),
    });
  }
  auto max_bounces = parser.present<std::size_t>("max-bounces");
  if (max_bounces.has_value()) {
    scene.camera()->SetMaxBounces(*max_bounces);
  }
}

int main(int argc, char* argv[]) {
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
  parser.add_argument("-g", "--gamma")
      .default_value(false)
      .implicit_value(true)
      .help("use gamma correction");
  parser.add_argument("-o", "--output")
      .default_value("image.png")
      .help("output file");

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
    std::cout << scene->ToString() << std::endl;

    rt::Renderer renderer{};
    auto image = renderer.Render(*scene);

    auto output_file = parser.get<std::string>("output");
    std::cout << "Saving " << output_file << std::endl;
    rt::ImagerWriter::Config iw_config{};
    iw_config.path = output_file;
    iw_config.gamma_correction = parser.get<bool>("-g");
    rt::ImagerWriter writer{iw_config};
    writer.Write(*image);
  } catch (const std::exception& err) {
    std::cerr << err.what() << std::endl;
    return EXIT_FAILURE;
  }
}
