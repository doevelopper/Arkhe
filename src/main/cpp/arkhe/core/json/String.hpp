#ifndef ARKHE_CORE_STRING_HPP
#define ARKHE_CORE_STRING_HPP

#include <cstring>
#include <string>
#include <arkhe/core/json/Data.hpp>

namespace Json 
{
    class String
    {
    public:
        String();
        virtual ~String();
        
        String(const char *data);

        struct Data 
        {
            int length;
            char utf8[1];
        };

        Data *d;

        void operator=(const std::string &ba)
        {
            d->length = static_cast<int>(ba.length());
            memcpy(d->utf8, ba.data(), ba.length());
        }

        bool operator==(const std::string &ba) const 
        {
            return toString() == ba;
        }
        
        bool operator!=(const std::string &str) const 
        {
            return !operator==(str);
        }
        
        bool operator>=(const std::string &str) const 
        {
            return toString() >= str;
        }

        bool operator==(const String &str) const 
        {
            if (d->length != str.d->length)
            {
                return false;
            }

            return !memcmp(d->utf8, str.d->utf8, d->length);
        }

        bool operator<(const String &other) const;
        bool operator>=(const String &other) const 
        { 
            return !(*this < other); 
        }

        std::string toString() const;
    };
}
#endif

