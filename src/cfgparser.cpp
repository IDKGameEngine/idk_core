#include "idk/core/cfgparser.hpp"
#include "idk/core/file.hpp"
#include "idk/core/log.hpp"
#include <cstring>

using namespace idk;


void CfgParser::skip(char)
{
    char ch = mBuf[mIdx];

    while (mIdx < mBuf.size() && ch)
    {
        ch = mBuf[mIdx++];
    }

    if (mIdx >= mBuf.size() - 1)
    {
        mIdx = mBuf.size() - 1;
    }
}


char CfgParser::peek()
{
    if (mIdx >= mBuf.size() - 1)
    {
        mIdx = mBuf.size() - 1;
        return '\0';
    }
    return mBuf[mIdx];
}


char CfgParser::advance()
{
    char ch = peek();
    if (!ch) return ch;

    mIdx += 1;
    mCol += 1;

    if (ch == '\n')
    {
        mLine += 1;
        mCol = 1;
    }

    return ch;
}


char CfgParser::retreat()
{
    mIdx -= 1;
    return peek();
}


char CfgParser::match( char ch )
{
    if (peek() == ch)
        return advance();
    return '\0';    
}


std::string CfgParser::_readLabel()
{
    std::string str = "";
    while (char ch = advance())
    {
        if (ch=='=' || (!isalnum(ch) && ch!='_' && ch!='-' && ch!='.'))
            break;
        str.push_back(ch);
    }
    return str;
}


std::string CfgParser::_readTo(char stop)
{
    std::string str = "";
    while (char ch = advance())
    {
        if (ch==stop) break;
        str.push_back(ch);
    }
    return str;
}


CfgParser::CfgParser(const char *path)
:   root_(new TreeNode("__global__")),
    mIdx(0), mLine(0), mCol(0)
{
    idk::FileLoader loader(path);
    idk::FileReader reader(path);

    auto  *src = static_cast<const char*>(reader.getData());
    auto  *end = src + reader.getSize();

    while (*src && (src < end))
    {
        char ch = *(src++);
        if (ch == ' ')
            continue;
        mBuf.push_back(ch);
    }

    mIdx  = 0;
    mLine = 1;
    mCol  = 1;

    _parse(root_);
}


void CfgParser::_parse(TreeNode *curr)
{
    // SysLog log("_parse \"%s\"", curr->mName.c_str());
    while (char ch = peek())
    {
        if (match('\n'))
        {
            continue;
        }

        else if (match('['))
        {
            std::string sname = _readTo(']');
            // log("[A] curr->insert<TreeNode>(%s, %s);", sname.c_str(), sname.c_str());
            _parse_section(curr->insert<TreeNode>(sname, sname));
        }
    
        else if (isalpha(ch))
        {
            // log("[ ] ch==\'%c\'", ch);
            IDK_ASSERT(false, "Invalid format");
        }
    }
}

void CfgParser::_parse_section(TreeNode *curr)
{
    // SysLog log("_parse_section \"%s\"", curr->mName.c_str());
    _readTo('{'); // [SectionName] { ...

    while (char ch = peek())
    {
        if (match('\n'))
        {
            continue;
        }

        else if (match('}'))
        {
            // log("match(\'}\'), return");
            return;
        }

        else if (match('['))
        {
            std::string sname = _readTo(']');
            // log("[B] curr->insert<TreeNode>(%s, %s);", sname.c_str(), sname.c_str());
            _parse_section(curr->insert<TreeNode>(sname, sname));
        }

        else if (isalpha(ch))
        {
            std::string key = _readLabel();

            if (match('\"'))
            {
                std::string value = _readTo('\"');
                // log("[C] curr->insert<TreeLeaf>(%s, %s);", key.c_str(), value.c_str());
                curr->insert<TreeLeaf>(key, value);
            }
            else
            {
                std::string value = _readTo('\n');
                // log("[D] curr->insert<TreeLeaf>(%s, %s);", key.c_str(), value.c_str());
                curr->insert<TreeLeaf>(key, value);
            }
        }
    }
}



void CfgParser::print() { _print(root_); }
void CfgParser::_print(CfgParser::TreeNode *currNode)
{
    TreeNode &curr = *currNode;
    SysLog log("%s", curr.mName.c_str());

    for (auto &[key, nd]: curr)
    {
        if (nd->isLeaf)
            log("%s = \"%s\"", key.c_str(), ((TreeLeaf*)nd)->mValue.c_str());
        else
            _print((TreeNode*)nd);
    }
}



// {
//     for (auto &[section, keyval]: mData)
//     {
//         idk::SysLog log("Section %s", section.c_str());

//         for (auto &[key, value]: keyval)
//         {
//             log("%s = \"%s\"", key.c_str(), value.c_str());
//         }
//     }
// }





// TreeBase *operator[](const std::string &key)
// {
//     if (nodes_.contains(key))
//     {
//         return nodes_[key];
//     }
// }


