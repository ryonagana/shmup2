#include "Utils/CUtils.h"

template<typename T>
std::ostream &BinaryUtils::write_bin(std::ostream &fs, const T &val)
{
    return fs.write(reinterpret_cast<const char*>(&val), sizeof (T));
}

template<typename T>
std::istream &BinaryUtils::read_bin(std::istream &fs, T &val)
{
    return fs.read(reinterpret_cast<char*>(&val), sizeof (T));

}
