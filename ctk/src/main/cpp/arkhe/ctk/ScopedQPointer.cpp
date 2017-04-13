#include<arkhe/ctk/ScopedQPointer.hpp>
  
template < class Object, class Deleter > 
ScopedQPointer<Object,Deleter>::ScopedQPointer(Object * p)
 : qptr{p} 
 {
	 
 }
 
 template < class Object, class Deleter > 
 ScopedQPointer<Object,Deleter>::ScopedQPointer(ScopedQPointer && other) Q_DECL_NOEXCEPT
      : qptr{ other.release() }
{
}
