#ifndef ARKHE_CORE_JSONOBJECT_HPP
#define ARKHE_CORE_JSONOBJECT_HPP

#include <arkhe/core/json/JsonValue.hpp>
namespace Json 
{
    class JsonObject
    {
    public:        
        JsonObject();
        virtual ~JsonObject();/*
        JsonObject(std::initializer_list<std::pair<std::string, JsonValue> > args);

        JsonObject(const JsonObject &other);
        JsonObject &operator =(const JsonObject &other);
    
        typedef std::vector<std::string> Keys;

        Keys keys() const;
        int size() const;
        int count() const { return size(); }
        int length() const { return size(); }
        bool isEmpty() const;
    
        JsonValue value(const std::string &key) const;
        JsonValue operator[] (const std::string &key) const;
        JsonValueRef operator[] (const std::string &key);
    
        void remove(const std::string &key);
        JsonValue take(const std::string &key);
        bool contains(const std::string &key) const;
    
        bool operator==(const JsonObject &other) const;
        bool operator!=(const JsonObject &other) const;
    
        class const_iterator;
    
        class iterator
        {
            friend class const_iterator;
            friend class JsonObject;
            JsonObject *o;
            int i;
    
        public:
            typedef std::bidirectional_iterator_tag iterator_category;
            typedef int difference_type;
            typedef JsonValue value_type;
            typedef JsonValueRef reference;
    
            iterator() : o(nullptr), i(0) {}
            iterator(JsonObject *obj, int index) : o(obj), i(index) {}
    
            std::string key() const { return o->keyAt(i); }
            JsonValueRef value() const { return JsonValueRef(o, i); }
            JsonValueRef operator*() const { return JsonValueRef(o, i); }
            JsonValueRefPtr operator->() const { return JsonValueRefPtr(o, i); }
            bool operator==(const iterator &other) const { return i == other.i; }
            bool operator!=(const iterator &other) const { return i != other.i; }
    
            iterator &operator++() { ++i; return *this; }
            iterator operator++(int) { iterator r = *this; ++i; return r; }
            iterator &operator--() { --i; return *this; }
            iterator operator--(int) { iterator r = *this; --i; return r; }
            iterator operator+(int j) const
            { iterator r = *this; r.i += j; return r; }
            iterator operator-(int j) const { return operator+(-j); }
            iterator &operator+=(int j) { i += j; return *this; }
            iterator &operator-=(int j) { i -= j; return *this; }
    
        public:
            bool operator==(const const_iterator &other) const { return i == other.i; }
            bool operator!=(const const_iterator &other) const { return i != other.i; }
        };
        friend class iterator;
    
        class const_iterator
        {
            friend class iterator;
            const JsonObject *o;
            int i;
    
        public:
            typedef std::bidirectional_iterator_tag iterator_category;
            typedef int difference_type;
            typedef JsonValue value_type;
            typedef JsonValue reference;
    
            const_iterator() : o(nullptr), i(0) {}
            const_iterator(const JsonObject *obj, int index)
                : o(obj), i(index) {}
            const_iterator(const iterator &other)
                : o(other.o), i(other.i) {}
    
            std::string key() const { return o->keyAt(i); }
            JsonValue value() const { return o->valueAt(i); }
            JsonValue operator*() const { return o->valueAt(i); }
            JsonValuePtr operator->() const { return JsonValuePtr(o->valueAt(i)); }
            bool operator==(const const_iterator &other) const { return i == other.i; }
            bool operator!=(const const_iterator &other) const { return i != other.i; }
    
            const_iterator &operator++() { ++i; return *this; }
            const_iterator operator++(int) { const_iterator r = *this; ++i; return r; }
            const_iterator &operator--() { --i; return *this; }
            const_iterator operator--(int) { const_iterator r = *this; --i; return r; }
            const_iterator operator+(int j) const
            { const_iterator r = *this; r.i += j; return r; }
            const_iterator operator-(int j) const { return operator+(-j); }
            const_iterator &operator+=(int j) { i += j; return *this; }
            const_iterator &operator-=(int j) { i -= j; return *this; }
    
            bool operator==(const iterator &other) const { return i == other.i; }
            bool operator!=(const iterator &other) const { return i != other.i; }
        };
        friend class const_iterator;
    
        // STL style
        iterator begin() { detach(); return iterator(this, 0); }
        const_iterator begin() const { return const_iterator(this, 0); }
        const_iterator constBegin() const { return const_iterator(this, 0); }
        iterator end() { detach(); return iterator(this, size()); }
        const_iterator end() const { return const_iterator(this, size()); }
        const_iterator constEnd() const { return const_iterator(this, size()); }
        iterator erase(iterator it);
    
        // more Qt
        iterator find(const std::string &key);
        const_iterator find(const std::string &key) const { return constFind(key); }
        const_iterator constFind(const std::string &key) const;
        iterator insert(const std::string &key, const JsonValue &value);
    
        // STL compatibility
        typedef JsonValue mapped_type;
        typedef std::string key_type;
        typedef int size_type;
    
        bool empty() const { return isEmpty(); }
    
    private:
        friend class Internal::Data;
        friend class JsonValue;
        friend class JsonDocument;
        friend class JsonValueRef;
    
        JsonObject(Data *data, Object *object);
        void detach(uint32_t reserve = 0);
        void compact();
    
        std::string keyAt(int i) const;
        JsonValue valueAt(int i) const;
        void setValueAt(int i, const JsonValue &val);
    
        Data *d;
        Object *o;*/
    };
}
#endif
