#include <arkhe/core/json/Entry.hpp>

Json::Entry::Entry()
{
    
}

Json::Entry::~Entry()
{

}

bool Json::Entry::operator==(const std::string &key) const
{
    // return shallowKey() == key;
}

bool Json::Entry::operator==(const Entry &other) const
{
    // return shallowKey() == other.shallowKey();
}

bool Json::Entry::operator>=(const Entry &other) const
{
    // return shallowKey() >= other.shallowKey();
}


