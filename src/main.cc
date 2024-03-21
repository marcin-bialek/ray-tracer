#include <iostream>

#include <argparse/argparse.hh>
#include <tinyxml2/tinyxml2.hh>

#include <rt/loaders/scene_loader.hh>
#include <rt/renderer/renderer.hh>
#include <rt/writers/image_writer.hh>

int main(int argc, char* argv[]) {
  argparse::ArgumentParser parser{"ray-tracer"};
  parser.add_argument("input_file").required().help("XML input file");
  parser.add_argument("-r", "--resolution")
      .nargs(2)
      .scan<'u', std::size_t>()
      .help("custom resolution");

  try {
    parser.parse_args(argc, argv);
  } catch (const std::exception& err) {
    std::cerr << err.what() << std::endl;
    std::cerr << parser;
    return EXIT_FAILURE;
  }

  tinyxml2::XMLDocument input_file{};
  const auto input_file_path = parser.get("input_file");
  const auto err = input_file.LoadFile(input_file_path.c_str());
  if (err != tinyxml2::XML_SUCCESS) {
    std::cerr << "Could not load input file: " << input_file.ErrorIDToName(err)
              << std::endl;
    return EXIT_FAILURE;
  }

  rt::SceneLoader loader{&input_file};
  auto scene = loader.Load();

  auto resolution = parser.present<std::vector<std::size_t>>("-r");
  if (resolution.has_value()) {
    scene->camera()->SetResolution(resolution->at(0), resolution->at(1));
  }

  std::cout << scene->ToString() << std::endl;

  rt::Renderer renderer{};
  auto image = renderer.Render(*scene);

  rt::ImagerWriter writer{"image.png"};
  writer.Write(image);
}
