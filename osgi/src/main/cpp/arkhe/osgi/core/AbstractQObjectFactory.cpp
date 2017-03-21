#include <arkhe/osgi/core/AbstractQObjectFactory.hpp>

template<typename BaseClassType>
osgi::AbstractQObjectFactory<BaseClassType>::AbstractQObjectFactory()
{
}


template<typename BaseClassType>
osgi::AbstractQObjectFactory<BaseClassType>::~AbstractQObjectFactory()
{
}


template<typename BaseClassType>
QString osgi::AbstractQObjectFactory<BaseClassType>::objectNameToKey(const QString& objectName)
{
    return objectName; 
}


template<typename BaseClassType>
template<typename ClassType>
bool osgi::AbstractQObjectFactory<BaseClassType>::registerQObject(QString& key)
{
    key = this->objectNameToKey(QString::fromLatin1(ClassType::staticMetaObject.className()));
    return this->AbstractObjectFactory<BaseClassType>::template registerObject<ClassType>(key);
}

