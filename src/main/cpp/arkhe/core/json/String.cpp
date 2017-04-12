
#include <arkhe/core/json/String.hpp>

Json::String::String()
{
}

Json::String::~String()
{
}

Json::String::String(const char * data)
{
    d = (Data *)data;
}

std::string Json::String::toString () const
{
    return std::string(d->utf8, d->length);
}
