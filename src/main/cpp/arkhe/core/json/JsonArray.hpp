#ifndef ARKHE_CORE_JSONARRAY_HPP
#define ARKHE_CORE_JSONARRAY_HPP

#include <initializer_list>
#include <arkhe/core/json/JsonValue.hpp>
#include <arkhe/core/json/JsonValueRef.hpp>
#include <arkhe/core/json/JsonValueRefPtr.hpp>
#include <arkhe/core/json/JsonValuePtr.hpp>

namespace Json 
{
    class JsonArray
    {
    public:        
        JsonArray();
        virtual ~JsonArray();
/*        
        JsonArray(std::initializer_list<JsonValue> args);
        JsonArray(const JsonArray &other);
        JsonArray &operator=(const JsonArray &other);
    
        int size() const;
        int count() const
        {
            return size();
        }
    
        bool isEmpty() const;
        JsonValue at(int i) const;
        JsonValue first() const;
        JsonValue last() const;
    
        void prepend(const JsonValue &value);
        void append(const JsonValue &value);
        void removeAt(int i);
        JsonValue takeAt(int i);
        void removeFirst()
        {
            removeAt(0);
        }
        
        void removeLast()
        {
            removeAt(size() - 1);
        }
    
        void insert(int i, const JsonValue &value);
        void replace(int i, const JsonValue &value);
    
        bool contains(const JsonValue &element) const;
        JsonValueRef operator[](int i);
        JsonValue operator[](int i) const;
    
        bool operator==(const JsonArray &other) const;
        bool operator!=(const JsonArray &other) const;

        class const_iterator;

        class iterator
        {
        public:
            JsonArray *a;
            int i;
            typedef std::random_access_iterator_tag  iterator_category;
            typedef int difference_type;
            typedef JsonValue value_type;
            typedef JsonValueRef reference;
            typedef JsonValueRefPtr pointer;
    
            iterator() : a(nullptr), i(0) { }
            explicit iterator(JsonArray *array, int index) : a(array), i(index) { }
    
            JsonValueRef operator*() const { return JsonValueRef(a, i); }
            JsonValueRefPtr operator->() const { return JsonValueRefPtr(a, i); }
            JsonValueRef operator[](int j) const { return JsonValueRef(a, i + j); }
    
            bool operator==(const iterator &o) const { return i == o.i; }
            bool operator!=(const iterator &o) const { return i != o.i; }
            bool operator<(const iterator& other) const { return i < other.i; }
            bool operator<=(const iterator& other) const { return i <= other.i; }
            bool operator>(const iterator& other) const { return i > other.i; }
            bool operator>=(const iterator& other) const { return i >= other.i; }
            bool operator==(const const_iterator &o) const { return i == o.i; }
            bool operator!=(const const_iterator &o) const { return i != o.i; }
            bool operator<(const const_iterator& other) const { return i < other.i; }
            bool operator<=(const const_iterator& other) const { return i <= other.i; }
            bool operator>(const const_iterator& other) const { return i > other.i; }
            bool operator>=(const const_iterator& other) const { return i >= other.i; }
            iterator &operator++() { ++i; return *this; }
            iterator operator++(int) { iterator n = *this; ++i; return n; }
            iterator &operator--() { i--; return *this; }
            iterator operator--(int) { iterator n = *this; i--; return n; }
            iterator &operator+=(int j) { i+=j; return *this; }
            iterator &operator-=(int j) { i-=j; return *this; }
            iterator operator+(int j) const { return iterator(a, i+j); }
            iterator operator-(int j) const { return iterator(a, i-j); }
            int operator-(iterator j) const { return i - j.i; }
        };
        
        friend class iterator;

        class const_iterator
        {
        public:
            const JsonArray *a;
            int i;
            typedef std::random_access_iterator_tag  iterator_category;
            typedef std::ptrdiff_t difference_type;
            typedef JsonValue value_type;
            typedef JsonValue reference;
            typedef JsonValuePtr pointer;
    
            const_iterator() : a(nullptr), i(0) { }
            explicit const_iterator(const JsonArray *array, int index) : a(array), i(index) { }
            const_iterator(const iterator &o) : a(o.a), i(o.i) {}
    
            JsonValue operator*() const { return a->at(i); }
            JsonValuePtr operator->() const { return JsonValuePtr(a->at(i)); }
            JsonValue operator[](int j) const { return a->at(i+j); }
            bool operator==(const const_iterator &o) const { return i == o.i; }
            bool operator!=(const const_iterator &o) const { return i != o.i; }
            bool operator<(const const_iterator& other) const { return i < other.i; }
            bool operator<=(const const_iterator& other) const { return i <= other.i; }
            bool operator>(const const_iterator& other) const { return i > other.i; }
            bool operator>=(const const_iterator& other) const { return i >= other.i; }
            const_iterator &operator++() { ++i; return *this; }
            const_iterator operator++(int) { const_iterator n = *this; ++i; return n; }
            const_iterator &operator--() { i--; return *this; }
            const_iterator operator--(int) { const_iterator n = *this; i--; return n; }
            const_iterator &operator+=(int j) { i+=j; return *this; }
            const_iterator &operator-=(int j) { i-=j; return *this; }
            const_iterator operator+(int j) const { return const_iterator(a, i+j); }
            const_iterator operator-(int j) const { return const_iterator(a, i-j); }
            int operator-(const_iterator j) const { return i - j.i; }
        };

        friend class const_iterator;

        iterator begin()
        {
            detach();
            return (iterator(this, 0));
        }

        const_iterator begin() const
        {
            return (const_iterator(this, 0));
        }

        const_iterator constBegin() const
        {
            return (const_iterator(this, 0));
        }

        iterator end()
        {
            detach();
            return (iterator(this, size()));
        }

        const_iterator end() const
        {
            return const_iterator(this, size());
        }

        const_iterator constEnd() const
        {
            return (const_iterator(this, size()));
        }
        
        iterator insert(iterator before, const JsonValue &value)
        {
            insert(before.i, value); return before;
        }
        
        iterator erase(iterator it)
        {
            removeAt(it.i); return it;
        }

        void push_back(const JsonValue &t)
        {
            append(t);
        }
        
        void push_front(const JsonValue &t)
        {
            prepend(t);
        }
        
        void pop_front()
        {
            removeFirst();
        }
        
        void pop_back()
        {
            removeLast();
        }
        
        bool empty() const
        {
            return (isEmpty());
        }

        typedef int size_type;
        typedef JsonValue value_type;
        typedef value_type *pointer;
        typedef const value_type *const_pointer;
        typedef JsonValueRef reference;
        typedef JsonValue const_reference;
        typedef int difference_type;

    private:
        friend class Data;
        friend class JsonValue;
        friend class JsonDocument;

        JsonArray(Data *data, Array *array);
        void compact();
        void detach(uint32_t reserve = 0);

        Data *d;
        Array *a;
*/
    };
}
#endif
