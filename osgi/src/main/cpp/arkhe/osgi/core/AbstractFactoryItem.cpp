#include <arkhe/osgi/core/AbstractFactoryItem.hpp>

template<typename BaseClassType>
osgi::core::AbstractFactoryItem<BaseClassType>::AbstractFactoryItem()
  :Instance()
{
    this->Verbose = false;
}

template<typename BaseClassType>
osgi::core::AbstractFactoryItem<BaseClassType>::~AbstractFactoryItem()
{
}

template<typename BaseClassType>
QStringList osgi::core::AbstractFactoryItem<BaseClassType>::instantiateErrorStrings()const
{
    return this->InstantiateErrorStrings;
}

template<typename BaseClassType>
void osgi::core::AbstractFactoryItem<BaseClassType>::appendInstantiateErrorString(const QString& errorString)
{
    this->InstantiateErrorStrings << errorString;
}

template<typename BaseClassType>
void osgi::core::AbstractFactoryItem<BaseClassType>::clearInstantiateErrorStrings()
{
    this->InstantiateErrorStrings.clear();
}

template<typename BaseClassType>
QStringList osgi::core::AbstractFactoryItem<BaseClassType>::instantiateWarningStrings()const
{
    return this->InstantiateWarningStrings;
}

template<typename BaseClassType>
void osgi::core::AbstractFactoryItem<BaseClassType>::appendInstantiateWarningString(const QString& msg)
{
  this->InstantiateWarningStrings << msg;
}

template<typename BaseClassType>
void osgi::core::AbstractFactoryItem<BaseClassType>::clearInstantiateWarningStrings()
{
  this->InstantiateWarningStrings.clear();
}

template<typename BaseClassType>
QStringList osgi::core::AbstractFactoryItem<BaseClassType>::loadErrorStrings()const
{
  return this->LoadErrorStrings;
}

template<typename BaseClassType>
void osgi::core::AbstractFactoryItem<BaseClassType>::appendLoadErrorString(const QString& errorString)
{
  this->LoadErrorStrings << errorString;
}

template<typename BaseClassType>
QStringList osgi::core::AbstractFactoryItem<BaseClassType>::loadWarningStrings()const
{
  return this->LoadWarningStrings;
}

template<typename BaseClassType>
void osgi::core::AbstractFactoryItem<BaseClassType>::appendLoadWarningString(const QString& msg)
{
  this->LoadWarningStrings << msg;
}

template<typename BaseClassType>
void osgi::core::AbstractFactoryItem<BaseClassType>::clearLoadWarningStrings()
{
    this->LoadWarningStrings.clear();
}

template<typename BaseClassType>  
BaseClassType* osgi::core::AbstractFactoryItem<BaseClassType>::instantiate()
{
    this->clearInstantiateErrorStrings();
    this->clearInstantiateWarningStrings();
    this->Instance = this->instanciator();
    return this->Instance;
}

template<typename BaseClassType>
bool osgi::core::AbstractFactoryItem<BaseClassType>::isInstantiated()const
{
  return (this->Instance != 0);
}

template<typename BaseClassType>
BaseClassType* osgi::core::AbstractFactoryItem<BaseClassType>::instance()const
{
  return this->Instance;
}

template<typename BaseClassType>
void osgi::core::AbstractFactoryItem<BaseClassType>::uninstantiate()
{
  if (!this->Instance)
    {
    return;
    }
  delete this->Instance;
  // Make sure the pointer is set to 0. Doing so, Will prevent attempt to
  // delete unextising object if uninstantiate() methods is called multiple times.
  this->Instance = 0; 
}

template<typename BaseClassType>
void osgi::core::AbstractFactoryItem<BaseClassType>::setVerbose(bool value)
{
  this->Verbose = value;
}

template<typename BaseClassType>
bool osgi::core::AbstractFactoryItem<BaseClassType>::verbose()const
{
  return this->Verbose;
}

