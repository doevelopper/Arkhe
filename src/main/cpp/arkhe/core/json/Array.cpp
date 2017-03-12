#include <arkhe/core/json/Array.hpp>

Json::Array::Array()
{
    
}

Json::Array::~Array()
{

}

bool Json::Array::isValid() const
{
    // if (tableOffset + length*sizeof(offset) > size)
    // {
        // return false;
    // }   

    // for (uint32_t i = 0; i < length; ++i) 
    // {
        // if (!at(i).isValid(this))
        // {
            // return false;
        // }
    // }
    return true;
}
