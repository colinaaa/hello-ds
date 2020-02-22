#include <unistd.h>

#include <iostream>
#include <string>

#include "Parser/Parser.hh"

#undef int

#include <getopt.h>

auto main(int argc, char* argv[]) -> int {
  std::string filename;

  Project::Parser p{};
  int choice;
  while (true) {
    static struct option long_options[] = {
        /* Use flags like so:
        {"verbose",	no_argument,	&verbose_flag, 'V'}*/
        /* Argument styles: no_argument, required_argument, optional_argument */
        {"version", no_argument, nullptr, 'v'},
        {"help", no_argument, nullptr, 'h'},
        {"src", no_argument, nullptr, 's'},
        {"debug", no_argument, nullptr, 'g'},
        {"file", required_argument, nullptr, 'f'}};

    int option_index = 0;

    /* Argument parameters:
        no_argument: " "
        required_argument: ":"
        optional_argument: "::" */

    choice = getopt_long(argc, argv, "vhsgf:", long_options, &option_index);

    if (choice == -1) break;

    switch (choice) {
      case 'v':
        std::cout << argv[0] << " Version 0.1.0" << std::endl;
        return 0;

      case 'h':
        std::cout << "Usage: " << argv[0] << " [-h -v -s -g] -f src.c" << std::endl;
        return 0;

      case 'f':
        filename = std::string(optarg);
        break;

      case 's':
        p.setSrc();
        break;

      case 'g':
        p.setDebug();
        break;

      case '?':
        /* getopt_long will have already printed an error */
        break;

      default:
        /* Not sure how to get here... */
        return EXIT_FAILURE;
    }
  }

  /* Deal with non-option arguments here */
  if (optind < argc && filename.empty()) {
    filename = std::string(argv[optind]);
  }

  p.run(filename);
}
