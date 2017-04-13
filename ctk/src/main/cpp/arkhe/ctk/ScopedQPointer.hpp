#ifndef SCOPED_QPOINTER_HPP
#define SCOPED_QPOINTER_HPP
 
#include <QPointer>
#include <memory>
#include <type_traits>
 
#include<arkhe/ctk/ctkExport.hpp>
 
template < class Object, class Deleter = std::default_delete<Object> > 
class ScopedQPointer 
{
public:
    static_assert(std::is_base_of<QObject, Object>{}, "Object must be derived from QObject");
 
    using object_type     = Object;
    using reference       = object_type &;
    using const_reference = object_type const &;
    using pointer         = object_type *;
    using const_pointer   = object_type const *;
 
    explicit ScopedQPointer(Object * p = nullptr);// : qptr{p} {}
 
    ScopedQPointer(ScopedQPointer const &) = delete;
    ScopedQPointer & operator = (ScopedQPointer const &) = delete;
 
    ScopedQPointer(ScopedQPointer && other) Q_DECL_NOEXCEPT;
      // : qptr{ other.release() }
    // { }
 
    ScopedQPointer & operator = (ScopedQPointer && other) Q_DECL_NOEXCEPT 
	{
        ScopedQPointer{std::move(other)}.swap(*this);
        return *this;
    }
 
    ScopedQPointer & operator = (pointer p) 
	{
        reset(p);
        return *this;
    }
 
    ~ScopedQPointer() 
	{
        Deleter{}( qptr.data() );
    }
 
    bool isNull() const 
	{ 
		return qptr.isNull(); 
	}
 
    void swap(ScopedQPointer & other) Q_DECL_NOEXCEPT 
	{ 
		qptr.swap(other.qptr); 
	}
 
    void reset(pointer p = nullptr) 
	{
        ScopedQPointer tmp{p};
        swap(tmp);
    }
 
    QPointer<object_type> release() 
	{
        auto ret = qptr;
        qptr.clear();
        return ret;
    }
 
    pointer   data()        const { return qptr.data(); }
    pointer   operator ->() const { return  data(); }
    reference operator *()  const { return *data(); }
    operator pointer ()     const { return  data(); }
 
private:
    QPointer<object_type> qptr;
};
 
 
class LateDeleter 
{
    template <class Object>
    void operator () (Object * p) const 
	{
        if (p) 
		{
            p->deleteLater();
        }
    }
};
 
template <class Object>
using ScopedQPointerDeleteLater = ScopedQPointer<Object, LateDeleter>;
 
#endif // SCOPED_QPOINTER_HPP