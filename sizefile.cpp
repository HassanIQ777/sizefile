#include "libutils/libutils.hpp"
#include "libutils/src/numutils.hpp"

using namespace std;

const string VERSION = "0.4";

int main(int argc, char *argv[]) {
  CLIParser parser(argc, argv);

  if (argc == 1) {
    Log::error("sizefile needs 1 argument or more.", false);
    Log::info("Usage: sizefile file1 file2 file3 ...");
    Log::info("If it doesn't work you might have to run as sudo.");
    return -1;
  }

  if (parser.hasFlag("-v")) {
    cout << "sizefile version " << VERSION << endl;
    return 0;
  }

  for (int i = 1; i < argc; i++) {
    string filename = parser.getArg(i);
    if (!File::isfile(filename)) {
      //   Log::warn("ERROR: the provided path isn't a file");
      continue;
    }

    float filesize = File::getfilesize(filename); // bytes
    string filesize_with_unit = numutils::bytes(filesize);

    cout << "size of '" << filename << "' is " << filesize_with_unit << endl;
  }
}