#ifndef ARKHE_CORE_OBJECT_HPP
#define ARKHE_CORE_OBJECT_HPP
#include <string>
#include <arkhe/core/json/Base.hpp>
// #include <arkhe/core/json/Entry.hpp>
namespace Json 
{
	class Entry;
    class Object : public Json::Base
    {
    public:
        Object();
        virtual ~Object();
        Entry *entryAt(int i) const;
        int indexOf(const std::string &key, bool *exists);
        bool isValid() const;
    };
}
#endif


