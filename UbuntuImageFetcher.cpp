#include "IUbuntuImageFetcher.h"
#include <nlohmann/json.hpp>
#include <curl/curl.h>
#include <iostream>
#include <stdexcept>

#include <string>
#include <vector>

#include <sstream>


void fetchData() {
    // Fetch the JSON data from URL and store it in jsonData
    // This function handles network requests using cURL or another library
}


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
