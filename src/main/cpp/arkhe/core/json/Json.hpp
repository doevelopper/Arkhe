#ifndef ARKHE_CORE_JSON_HPP
#define ARKHE_CORE_JSON_HPP
#include <string>
#include <climits>

#include <arkhe/core/json/Base.hpp>

namespace Json 
{
    // round the size up to the next 4 byte boundary
    inline int alignedSize(int size) 
    { 
        return (size + 3) & ~3; 
    }

    inline int qStringSize(const std::string &ba);

    inline void copyString(char *dest, const std::string &str);
    // returns INT_MAX if it can't compress it into 28 bits
    inline int compressedNumber(double d);
    inline void toInternal(char *addr, const char *data, int size);
}
#endif

