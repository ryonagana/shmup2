#ifndef FS_H
#define FS_H
#include <cstring>
#include <string>
#include <fstream>
#include <istream>
#include <ostream>
#include "shared.h"



class FileIO {
public:
     enum  FileIOMode : int {
        READ = (1<<0),
        WRITE = (1<<1),
        BINARY = (1<<2),
        TEXT = (1<<3),
        APPEND = (1 << 4),
        TRUNCATE = (1<< 5)
    };

    FileIO(const std::string& filepath, int mode_flags);
    bool isBad();
    bool isOpen();


    int32_t ReadInt32();
    byte ReadByte();
    int32_t ReadInt32(size_t size);
    byte ReadByte(size_t size);

    void WriteByte(byte data);
    void WriteInt(int32_t data);
    int mode = 0;

private:
    std::ifstream in;
    std::ofstream out;

    std::string filepath;
};

#endif // FS_H
