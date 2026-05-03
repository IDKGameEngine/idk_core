#include "idk/core/file.hpp"
#include "idk/core/assert.hpp"
#include "idk/core/log.hpp"

#include <cstring>
#include <map>

static std::map<std::string, idk::FileLoader*> file_loaders_;

static idk::FileLoader *getFileLoader(const char *path)
{
    IDK_ASSERT(file_loaders_.contains(path), "File not loaded \"{}\"", path);
    return file_loaders_[path];
}



idk::FileLoader::FileLoader(const char *path)
:   path_(path), data_(nullptr), size_(0)
{
    IDK_ASSERT(!file_loaders_.contains(path), "File already loaded \"{}\"", path);

    std::FILE *fh = std::fopen(path, "r");
    IDK_ASSERT(fh!=NULL, "Failure loading \"{}\"", path);

    std::fseek(fh, 0, SEEK_END);
    size_ = std::ftell(fh);
    data_ = std::malloc(size_);

    std::fseek(fh, 0, SEEK_SET);
    IDK_ASSERT(size_==std::fread(data_, 1, size_, fh), "Failure loading \"{}\"", path);
    std::fclose(fh);

    file_loaders_[path] = this;
    VLOG_INFO("[FileLoader::FileLoader] Success loading \"{}\"", path);
}


idk::FileLoader::~FileLoader()
{
    if (data_)
    {
        IDK_ASSERT(file_loaders_.contains(path_), "This should never happen");
        file_loaders_.erase(path_);
        std::free(data_);
    }
}



idk::FileReader::FileReader(const char *path)
:   loader_(getFileLoader(path))
{

}

