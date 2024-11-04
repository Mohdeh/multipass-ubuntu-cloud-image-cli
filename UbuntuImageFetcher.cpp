#include "IUbuntuImageFetcher.h"
#include <nlohmann/json.hpp>
#include <curl/curl.h>
#include <iostream>
#include <stdexcept>

#include <string>
#include <vector>

#include <sstream>



class UbuntuImageFetcher : public IUbuntuImageFetcher {
public:
    UbuntuImageFetcher() {
        fetchData();
    }


    std::vector<std::string> getSupportedReleases() const override {
        std::vector<std::string> releases;
        // Parse JSON to return supported releases
        try {
            for (const auto& product : jsonData["products"].items()) {
                const auto& release_name = product.value()["release"].get<std::string>();
                // Add the release name to our list, avoiding duplicates
                if (std::find(releases.begin(), releases.end(), release_name) == releases.end()) {
                    releases.push_back(release_name);
                }
            }
        } catch (const std::exception& e) {
            throw std::runtime_error("Error parsing supported releases: " + std::string(e.what()));
        }
    
        return releases;
    }

    
    std::string getCurrentLTSRelease() const override {
        std::string lts_release;
        // Parse JSON to find the current LTS release
        try {
            for (const auto& product : jsonData["products"].items()) {
                const auto& release_name = product.value()["release"].get<std::string>();
                const auto& version = product.value()["version"].get<std::string>();
    
                // Check if the release name indicates an LTS version
                if (release_name.find("LTS") != std::string::npos) {
                    // Keep track of the latest LTS version
                    if (lts_release.empty() || version > lts_release) {
                        lts_release = version;
                    }
                }
            }
        } catch (const std::exception& e) {
            throw std::runtime_error("Error parsing LTS release: " + std::string(e.what()));
        }
    
        if (lts_release.empty()) {
            throw std::runtime_error("No LTS release found in data.");
        }
    
        return lts_release;
    }

    

    std::string getSha256ForDiskImage(const std::string& release) const override {
        // Find sha256 checksum for disk1.img for a given release
        try {
            for (const auto& product : jsonData["products"].items()) {
                const auto& product_data = product.value();
    
                // Match the release name and architecture (amd64)
                if (product_data["release"].get<std::string>() == release &&
                    product_data["arch"].get<std::string>() == "amd64") {
    
                    // Find `disk1.img` under "images" and return its sha256
                    const auto& images = product_data["versions"]["arch"]["images"];
                    for (const auto& image : images.items()) {
                        if (image.value()["path"] == "disk1.img") {
                            return image.value()["sha256"].get<std::string>();
                        }
                    }
                }
            }
        } catch (const std::exception& e) {
            throw std::runtime_error("Error finding sha256 for disk1.img: " + std::string(e.what()));
        }
    
        throw std::runtime_error("Release or disk1.img not found for " + release);
    }


private:

    nlohmann::json jsonData; // JSON object to store fetched data

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* data) {
        size_t totalSize = size * nmemb;
        data->append(static_cast<char*>(contents), totalSize);
        return totalSize;
    }

    void fetchData() {
        const std::string url = "https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json";
        std::string jsonResponse;
        // Initialize cURL
        CURL* curl = curl_easy_init();
        if (!curl) {
            throw std::runtime_error("Failed to initialize cURL");
        }
        
        // Use cURL to fetch JSON data from URL
        // Set the URL and the write function callback
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &jsonResponse);

        // Perform the HTTP GET request
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            curl_easy_cleanup(curl);
            throw std::runtime_error("cURL request failed: " + std::string(curl_easy_strerror(res)));
        }

        // Clean up cURL
        curl_easy_cleanup(curl);
        
        // Parse and store in a member variable
        // Parse the JSON response
        try {
            jsonData = nlohmann::json::parse(jsonResponse);
        } catch (const nlohmann::json::parse_error& e) {
            throw std::runtime_error("Failed to parse JSON data: " + std::string(e.what()));
        }
    }
};
