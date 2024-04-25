#ifndef FILESYSTEM_HPP_
#define FILESYSTEM_HPP_

#include <string>

class FileSystem {
private:
  static std::string s_resourcesPath;

public:
  static const std::string &getResourcesPath();
  static void setResourcesPath(std::string path);
};

#endif // FILESYSTEM_HPP_
