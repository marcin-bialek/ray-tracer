#include <iostream>

#include <argparse/argparse.hh>
#include <tinyxml2/tinyxml2.hh>

#include <rt/loaders/scene_loader.hh>
#include <rt/math/vector3.hh>

int main(int argc, char* argv[]) {
  argparse::ArgumentParser parser{"ray-tracer"};
  parser.add_argument("input_file").required().help("XML input file");

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
  std::cout << scene->ToString() << std::endl;
}
