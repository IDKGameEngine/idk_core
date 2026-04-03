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



#ifdef __linux__
    #include <sys/mman.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <stdio.h>
    #include <unistd.h>

    idk::MMapFile::MMapFile(const char *path)
    {
        file_ = open(path, O_RDONLY);
        struct stat st;
        fstat(file_, &st);

        base = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, file_, 0);
        size = st.st_size;

        if (base == MAP_FAILED)
        {
            perror("mmap failed");
            exit(1);
        }
    }

    idk::MMapFile::~MMapFile()
    {
        munmap(base, size);
        close(file_);
    }

#endif // __linux__

