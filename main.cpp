#include "UbuntuImageFetcher.h"
#include <iostream>


int main(int argc, char* argv[]) {
    UbuntuImageFetcher fetcher;

    if (argc > 1) {
        std::string option = argv[1];
        if (option == "--supported") {
            for (const auto& release : fetcher.getSupportedReleases()) {
                std::cout << release << std::endl;
            }
        } else if (option == "--current-lts") {
            std::cout << fetcher.getCurrentLTSRelease() << std::endl;
        } else if (option == "--sha256") {
            if (argc == 3) {
                std::cout << fetcher.getSha256ForDiskImage(argv[2]) << std::endl;
            } else {
                std::cerr << "Please specify a release name." << std::endl;
            }
        } else {
            std::cerr << "Invalid option." << std::endl;
        }
    } else {
        std::cerr << "Please provide an option." << std::endl;
    }
    return 0;
}
