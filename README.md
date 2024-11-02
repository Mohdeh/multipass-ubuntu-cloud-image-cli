# multipass-ubuntu-cloud-image-cli
Multipass is a multi-platform tool for allowing users to easily spin up Ubuntu Cloud instances. It is written in C++ and interfaces with a number of 3rd party libraries and technologies. Multipass strives to have a clean and concise CLI without adding too many options to burden end users.

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
