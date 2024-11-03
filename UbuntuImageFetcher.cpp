#include "IUbuntuImageFetcher.h"
#include <nlohmann/json.hpp>
#include <curl/curl.h>
#include <iostream>
#include <stdexcept>


class UbuntuImageFetcher : public IUbuntuImageFetcher {
public:
    UbuntuImageFetcher() {
        fetchData();
    }

    std::vector<std::string> getSupportedReleases() const override {
        // Parse JSON to return supported releases
    }

    std::string getCurrentLTSRelease() const override {
        // Parse JSON to find the current LTS release
    }

    std::string getSha256ForDiskImage(const std::string& release) const override {
        // Find sha256 checksum for disk1.img for a given release
    }

private:
    void fetchData() {
        // Use cURL to fetch JSON data from URL
        // Parse and store in a member variable
    }
};
