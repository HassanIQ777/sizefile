#include "libutils/libutils.hpp"

const std::string VERSION = "0.4";

int main(int argc, char *argv[]) {
  CLIParser parser(argc, argv);

  if (argc == 1) {
    Log::error("sizefile needs 1 argument or more.", false);
    Log::info("Usage: sizefile file1 file2 file3 ...");
    Log::info("If it doesn't work you might have to run as sudo.");
    return -1;
  }

  if (parser.hasFlag("-v")) {
    std::cout << "sizefile version " << VERSION << std::endl;
  }

  for (int i = 1; i < argc; i++) {
    std::string filename = parser.getArg(i);
    if (!File::isfile(filename)) {
      //   Log::warn("ERROR: the provided path isn't a file");
      continue;
    }

    uintmax_t filesize = File::getfilesize(filename); // bytes
    std::string filesize_with_unit = numutils::bytes(filesize);

    std::cout << filename << ": " << filesize_with_unit << std::endl;
  }
}