#include <string>
#include <vector>

class IUbuntuImageFetcher {
public:
    virtual ~IUbuntuImageFetcher() = default;
    virtual std::vector<std::string> getSupportedReleases() const = 0;
    virtual std::string getCurrentLTSRelease() const = 0;
    virtual std::string getSha256ForDiskImage(const std::string& release) const = 0;
};
