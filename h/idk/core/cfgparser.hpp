#pragma once

#include <map>
#include <string>
#include <vector>

namespace idk
{
    class CfgParser;
}


class idk::CfgParser
{
private:
    using BiMap  = std::map<std::string, std::string>;
    using TriMap = std::map<std::string, BiMap>;

    std::vector<char> mBuf;
    TriMap            mData;
    size_t mIdx, mLine, mCol;

    class bimap_t
    {
    private:
        bool mExists;
        std::map<std::string, std::string> &mData;

    public:
        bimap_t(bool e, BiMap &d): mExists(e), mData(d) {  }
        operator bool() const { return mExists; }

        const char *operator[]( const std::string &key )
        { return mData.contains(key) ? mData[key].c_str() : ""; }

        const char *operator[]( const char *key )
        { return (*this)[std::string(key)]; }
    };

    std::string _readSection();
    std::string _readLabel();
    std::string _readTo(char);
    std::string _readString();
    std::string _readValue();

    void skip(char);
    char peek();
    char advance();
    char retreat();
    char match(char);

public:
    CfgParser( const std::string &path );
    void print();

    bimap_t operator[]( const std::string &sect )
    {
        if (mData.contains(sect))
            return bimap_t(true, mData[sect]);
        return bimap_t(false, mData["__global__"]);
    }
};

