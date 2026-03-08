#include "idk/core/file.hpp"
#include "idk/core/assert.hpp"
#include <fstream>
#include <vector>


namespace idk::file
{
    std::string loadRaw(const std::string &path);
}


std::string idk::file::loadRaw(const std::string &path)
{
    std::ifstream stream(path, std::ifstream::binary);
    IDK_ASSERT(stream.is_open(), "Failed opening file \"{}\"", path.c_str());

    stream.seekg(0, std::ifstream::end);
    std::string buf;  buf.resize(stream.tellg());

    stream.seekg(0, std::ifstream::beg);
    stream.read((char*)(buf.data()), buf.size());

    return buf;
}



size_t idk::file::load_raw(const char *filepath, void *buf, size_t bufsz)
{
    size_t filesz = 0;

    std::string path(filepath);
    std::ifstream stream(path, std::ifstream::binary);
    IDK_ASSERT(stream.is_open(), "Failed opening file \"{}\"", path.c_str());

    stream.seekg(0, std::ifstream::end);
    filesz = stream.tellg();
    IDK_ASSERT(filesz<=bufsz, "Failed to load file, too large: %s", filepath);

    stream.seekg(0, std::ifstream::beg);
    stream.read(static_cast<char*>(buf), filesz);

    return filesz;
}
