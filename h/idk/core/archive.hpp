// #pragma once

// #include "idk/core/types.hpp"

// namespace idk
// {
//     class FileArchive;
// }


// class idk::FileArchive
// {
// public:
//     struct Header
//     {
//         uint64_t magic; // 0xDEADBEBE
//         uint64_t numEntries;
//         // HeaderTableEntry[numEntries];
//     };

//     struct HeaderEntry
//     {
//         uint64_t offset;
//         uint64_t length;
//         char name[256 - 2*sizeof(uint64_t)];
//     };

//     void dsaaffsa()
//     {
//         uint8_t buf[2048];
    
//         auto *H = (FileArchive::Header*)(buf + 0);
//         H->magic = 0xDEADBEBE;
//         H->numEntries = 4;
//     }

// private:

// };


// void asddsadaef(uint8_t *dst, size_t dstSize)
// {
//     auto *H = (idk::FileArchive::Header*)(dst + 0);
//     H->magic = 0xDEADBEBE;
//     H->numEntries = 1;

//     auto *E = (idk::FileArchive::HeaderEntry*)(dst + sizeof(idk::FileArchive::Header));
//     E->offset = 256;
//     E->length = 512*1024;
//     // E->name
// }

