#pragma once

#include <map>
#include <string>
#include <vector>

#include "idk/core/assert.hpp"
#include "idk/core/log.hpp"

namespace idk
{
    class CfgParser;
}


class idk::CfgParser
{
public:
    class TreeBase;
    class TreeLeaf;
    class TreeNode;

    CfgParser(const char *path);
    void print();

private:
    TreeNode *root_;
    std::vector<char> mBuf;
    size_t mIdx, mLine, mCol;

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

    void _parse(TreeNode*);
    void _parse_section(TreeNode*);
    void _print(TreeNode*);
};




class idk::CfgParser::TreeBase
{
public:
    const bool isLeaf;

    TreeBase(bool leaf)
    :   isLeaf(leaf)
    {

    }
};


class idk::CfgParser::TreeLeaf: public TreeBase
{
public:
    std::string mValue;

    TreeLeaf(const std::string &value)
    :   TreeBase(true), mValue(value)
    {

    }
};


class idk::CfgParser::TreeNode: public TreeBase
{
private:
    std::map<std::string, TreeBase*> nodes_;

public:
    std::string mName;

    TreeNode(const std::string &name)
    :   TreeBase(false), mName(name)
    {

    }

    template <typename T, typename... Args>
    T *insert(const std::string &key, Args... args)
    {
        IDK_ASSERT(!nodes_.contains(key), "nodes_ already contains \"{}\"", key);

        T *ndptr = new T(args...);
        nodes_[key] = static_cast<TreeBase*>(ndptr);
        return ndptr;
    }

    auto begin() { return nodes_.begin(); }
    auto end()   { return nodes_.end(); }
};

