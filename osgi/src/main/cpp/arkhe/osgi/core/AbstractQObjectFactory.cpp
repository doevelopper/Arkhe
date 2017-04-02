#include <arkhe/osgi/core/AbstractQObjectFactory.hpp>

template<typename BaseClassType>
osgi::core::AbstractQObjectFactory<BaseClassType>::AbstractQObjectFactory()
{
}


template<typename BaseClassType>
osgi::core::AbstractQObjectFactory<BaseClassType>::~AbstractQObjectFactory()
{
}


template<typename BaseClassType>
QString osgi::core::AbstractQObjectFactory<BaseClassType>::objectNameToKey(const QString& objectName)
{
    return objectName; 
}


template<typename BaseClassType>
template<typename ClassType>
bool osgi::core::AbstractQObjectFactory<BaseClassType>::registerQObject(QString& key)
{
    key = this->objectNameToKey(QString::fromLatin1(ClassType::staticMetaObject.className()));
    return this->AbstractObjectFactory<BaseClassType>::template registerObject<ClassType>(key);
}

