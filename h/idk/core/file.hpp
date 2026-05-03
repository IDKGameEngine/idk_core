#pragma once

#include "idk/core/types.hpp"

namespace idk
{
    class FileLoader;
    class FileReader;
}


class idk::FileLoader: public idk::NonCopyable, public idk::NonMovable
{
private:
    friend class idk::FileReader;
    const char *path_;
    void  *data_;
    size_t size_;

public:
    FileLoader(const char *filepath);
    ~FileLoader();
};


class idk::FileReader: public idk::NonCopyable, public idk::NonMovable
{
private:
    const idk::FileLoader *loader_;

public:
    FileReader(const char *filepath);
    const void *getData() const { return loader_->data_; }
    size_t getSize() const { return loader_->size_; }
};

