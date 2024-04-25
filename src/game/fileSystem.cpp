#include "fileSystem.hpp"

std::string FileSystem::s_resourcesPath{""};

const std::string &FileSystem::getResourcesPath() { return s_resourcesPath; };

void FileSystem::setResourcesPath(std::string path) { s_resourcesPath = path; };
