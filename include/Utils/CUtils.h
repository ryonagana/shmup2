#ifndef CUTILS_H
#define CUTILS_H
#include <iostream>
#include <ostream>
#include <fstream>

namespace BinaryUtils {

    template<typename T>
    std::ostream& write_bin(std::ostream &fs, const T& val);

    template <typename T>
    std::istream &read_bin(std::istream &fs, T& val);
}

#endif // CUTILS_H
