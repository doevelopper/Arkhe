#include <arkhe/osgi/core/AbstractFactoryFileBasedItem.hpp>

template<typename BaseClassType>
osgi::core::AbstractFactoryFileBasedItem<BaseClassType>::AbstractFactoryFileBasedItem()
{
    
}

template<typename BaseClassType>
osgi::core::AbstractFactoryFileBasedItem<BaseClassType>::~AbstractFactoryFileBasedItem()
{
       
}

template<typename BaseClassType>
void osgi::core::AbstractFactoryFileBasedItem<BaseClassType>::path(const QString& path)
{
  this->m_path = path;
}

template<typename BaseClassType>
QString osgi::core::AbstractFactoryFileBasedItem<BaseClassType>::path()const
{
  return this->m_path;
}
