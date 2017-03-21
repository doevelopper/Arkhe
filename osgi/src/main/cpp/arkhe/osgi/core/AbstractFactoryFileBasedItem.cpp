#include <arkhe/osgi/core/AbstractFactoryFileBasedItem.hpp>

template<typename BaseClassType>
osgi::AbstractFactoryFileBasedItem<BaseClassType>::AbstractFactoryFileBasedItem()
{
    
}

template<typename BaseClassType>
osgi::AbstractFactoryFileBasedItem<BaseClassType>::~AbstractFactoryFileBasedItem()
{
       
}

template<typename BaseClassType>
void osgi::AbstractFactoryFileBasedItem<BaseClassType>::path(const QString& path)
{
  this->m_path = path;
}

template<typename BaseClassType>
QString osgi::AbstractFactoryFileBasedItem<BaseClassType>::path()const
{
  return this->m_path;
}
