#include <arkhe/core/json/Object.hpp>

Json::Object::Object()
{
    
}

Json::Object::~Object()
{

}


Json::Entry *Json::Object::entryAt(int i) const 
{
    return reinterpret_cast<Json::Entry *>(((char *)this) + table()[i]);
}


int Json::Object::indexOf(const std::string &key, bool *exists)
{
    int min = 0;
    int n = length;
    // while (n > 0)
    // {
        // int half = n >> 1;
        // int middle = min + half;
        // if (*entryAt(middle) >= key)
        // {
            // n = half;
        // }
        // else
        // {
            // min = middle + 1;
            // n -= half + 1;
        // }
    // }

    // if (min < (int)length && *entryAt(min) == key)
    // {
        // *exists = true;
        // return min;
    // }
    
    // *exists = false;

    // return min;
}

bool Json::Object::isValid() const
{
    // if (tableOffset + length*sizeof(offset) > size)
    // {
        // return false;
    // }

    // std::string lastKey;
    
    // for (uint32_t i = 0; i < length; ++i)
    // {
        // offset entryOffset = table()[i];
        
        // if (entryOffset + sizeof(Entry) >= tableOffset)
        // {
            // return false;
        // }
        
        // Entry *e = entryAt(i);
        // int s = e->size();
        
        // if (table()[i] + s > tableOffset)
        // {
            // return false;
        // }
        
        // std::string key = e->key();
        
        // if (key < lastKey)
        // {
            // return false;
        // }
        
        // if (!e->value.isValid(this))
        // {
            // return false;
        // }
        
        // lastKey = key;
    // }
    // return true;
}




