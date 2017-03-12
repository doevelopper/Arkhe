#ifndef ARKHE_CORE_ENTRY_HPP
#define ARKHE_CORE_ENTRY_HPP

#include <arkhe/core/json/Json.hpp>
#include <arkhe/core/json/String.hpp>
#include <arkhe/core/json/Value.hpp>

namespace Json 
{
    class Entry
    {
    public:
   
        Entry();
        virtual ~Entry();

        Value value;

        int size() const
        {
            int s = sizeof(Entry);
            s += sizeof(uint32_t) + (*(int *) ((const char *)this + sizeof(Entry)));
            return alignedSize(s);
        }

        int usedStorage(Base *b) const
        {
            // return size() + value.usedStorage(b);
        }

        String shallowKey() const
        {
            // return String((const char *)this + sizeof(Entry));
        }

        std::string key() const
        {
            // return shallowKey().toString();
        }

        bool operator==(const std::string &key) const;
        bool operator!=(const std::string &key) const 
        { 
            // return !operator==(key); 
        }
        
        bool operator>=(const std::string &key) const 
        { 
            // return shallowKey() >= key; 
        }

        bool operator==(const Entry &other) const;
        bool operator>=(const Entry &other) const;

    };
    
    inline bool operator<(const std::string &key, const Entry &e)
    {
        //return e >= key;
    }

}
#endif

