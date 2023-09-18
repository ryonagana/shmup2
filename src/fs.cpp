#include "fs.h"

FileIO::FileIO(const std::string &filepath, int mode_flags)
{
   int flags;

    if(mode_flags & FileIOMode::READ){
        flags = std::ios::in;
         this->mode = FileIOMode::READ;

    }else if(mode_flags & FileIOMode::BINARY &&  mode_flags & FileIOMode::READ){
        flags = std::ios::in | std::ios::binary;
        this->mode = FileIOMode::READ;
    }

    if(mode_flags & FileIOMode::WRITE){
         flags = std::ios::out;
         this->mode = FileIOMode::WRITE;
    }else if(mode_flags & FileIOMode::BINARY &&  mode_flags & FileIOMode::WRITE){
         flags = std::ios::out | std::ios::binary;
         this->mode = FileIOMode::WRITE;
    }

    if(mode_flags & FileIOMode::APPEND){
         flags = std::ios::app;
    }

    if(mode_flags & FileIOMode::TRUNCATE){
        flags = std::ios::trunc;
    }

    std::_Ios_Openmode m = static_cast<std::_Ios_Openmode>(flags);

    if(this->mode){
        in.open(filepath.c_str(), m);
    }else {
         out.open(filepath.c_str(),  m);
    }


}

bool FileIO::isBad()
{
    if(mode == FileIOMode::READ){
        return in.bad();
    }

    return out.bad();
}

bool FileIO::isOpen()
{
    if(mode == FileIOMode::READ){
        return in.is_open();
    }

    return out.is_open();
}

int32_t FileIO::ReadInt32()
{
    char buf[5];

    in.read(buf, sizeof(int32_t));
    return std::atoi(buf);

}

byte FileIO::ReadByte()
{
    return in.get();
}

int32_t FileIO::ReadInt32(size_t size)
{
    char *buf = new char[size];
    in.read(buf, sizeof(int32_t) * size );
    char output[255];
    snprintf(output, sizeof(output), "%s", buf);
    delete[] buf;

    return std::atoi(output);
}

byte FileIO::ReadByte(size_t size)
{
    char *buf = new char[size];
    in.read(buf, sizeof(char) * size );
    char output[16];
    snprintf(output, sizeof(output), "%s", buf);
    delete[] buf;

    return std::atoi(output);
}

void FileIO::WriteByte(byte data)
{
    out.put(data);
}

void FileIO::WriteInt(int32_t data)
{
    char buf[8];
    itoa(data, buf, 2);

    out.write(buf, sizeof(int32_t));
}
