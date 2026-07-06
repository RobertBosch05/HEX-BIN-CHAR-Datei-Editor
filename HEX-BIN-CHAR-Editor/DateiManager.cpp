#include "DateiManager.hpp"
#include <fstream>

bool DateiManager::load(const std::string& path,
    std::vector<unsigned char>& data) const
{
    std::ifstream file(path, std::ios::binary);
    if (!file) return false;

    data.assign(std::istreambuf_iterator<char>(file),
        std::istreambuf_iterator<char>());
    return true;
}

bool DateiManager::save(const std::string& path,
    const std::vector<unsigned char>& data) const
{
    std::ofstream file(path, std::ios::binary | std::ios::trunc);
    if (!file) return false;

    file.write(reinterpret_cast<const char*>(data.data()),
        static_cast<std::streamsize>(data.size()));
    return file.good();
}
