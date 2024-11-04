# multipass-ubuntu-cloud-image-cli
Multipass is a multi-platform tool for allowing users to easily spin up Ubuntu Cloud instances. It is written in C++ and interfaces with a number of 3rd party libraries and technologies. Multipass strives to have a clean and concise CLI without adding too many options to burden end users.


## Building and Running the CLI
1. **Build Instructions**:
   - Clone the repository.
   - Run `cmake .` in the project directory.
   - Run `make` to build the executable.
     
2. **Usage**:
   - `./UbuntuImageCLI --supported`: List all supported releases.
   - `./UbuntuImageCLI --current-lts`: Display the current LTS version.
   - `./UbuntuImageCLI --sha256 <release_name>`: Display the `sha256` checksum for `disk1.img` of the specified release.



## Project Structure and Dependencies
1. Language & Libraries:
   - The code will be written in C++17.
   - JSON parsing: Use a third-party JSON library like nlohmann/json for ease of use and C++17 compatibility.
   - HTTP requests: Use a library like cURL or Poco (since Poco is already present in the tech stack). This will simplify downloading the JSON file from the Ubuntu cloud images URL.
   - Build system: Use CMake to manage builds on Linux, macOS, and Windows.
    
2. Project Structure:

   - A main directory with subfolders:
     - src/: For the main C++ source files.
     - include/: For header files.
     - lib/: For any third-party libraries (if necessary).
     - build/: For compiled objects (ignored by .gitignore).
  
  - CMakeLists.txt: To handle building and dependencies.
  - README.md: To provide instructions on how to build and run the CLI.




## Design and Implementation
1. Define an Interface Class:
   - Create an interface `IUbuntuImageFetcher` that declares the required methods:
     - std::vector<std::string> getSupportedReleases() const
     - std::string getCurrentLTSRelease() const
     - std::string getSha256ForDiskImage(const std::string& release) const
       
   - The implementation class will fetch and parse the JSON data, extracting the required information.

2. Implement the Derived Class:
   - **Fetch JSON Data**: Implement a function that downloads the JSON file from the specified URL.
   - **Parse JSON Data**: Use `nlohmann::json` (or another JSON parser) to extract the list of supported releases, the current LTS version, and the `sha256` hash of the `disk1.img` for a given release.
   - **Data Processing and Storage**: Store the fetched data in member variables for reuse. This avoids repeated network requests.

3. Methods for Each Requirement:
   - **Get Supported Releases**: Parse the JSON to get all Ubuntu releases that are currently supported.
   - **Get Current LTS Version**: Filter the JSON data to find the LTS version by checking the release property.
   - **Get** `sha256` **for** `disk1.img`: Extract and return the `sha256` checksum for the `disk1.img` of a specified release.

4. CLI Implementation:
   - Use `argc` and `argv` to handle command-line arguments.
   - Based on the input, call the appropriate method and display the output in the CLI.

