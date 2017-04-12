
#include <arkhe/core/json/Header.hpp>

Json::Header::Header()
{
}

Json::Header::~Header()
{
}

Json::Base * Json::Header::root ()
{
    return (Json::Base *)( this + 1 );
}
