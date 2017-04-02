#include <QSharedPointer>
#include <arkhe/osgi/core/AbstractObjectFactory.hpp>
#include <arkhe/osgi/core/FactoryObjectItem.hpp>
        
template<typename BaseClassType>
osgi::core::AbstractObjectFactory<BaseClassType>::AbstractObjectFactory()
    :osgi::core::AbstractFactory<BaseClassType>()
{
}

template<typename BaseClassType>
osgi::core::AbstractObjectFactory<BaseClassType>::~AbstractObjectFactory()
{
}

template<typename BaseClassType>
template<typename ClassType>
bool osgi::core::AbstractObjectFactory<BaseClassType>::registerObject(const QString& key)
{

    QString description = QString("Attempt to register \"%1\"").arg(key);
    if (this->item(key))
    {
        this->displayStatusMessage(QtWarningMsg, description, "Already registered", this->verbose());
        return (false);
    }

    if (this->sharedItem(key))
    {
        this->displayStatusMessage(QtDebugMsg, description,
                               "Already registered in other factory", this->verbose());
        return (false);
    }

    QSharedPointer<FactoryObjectItem<BaseClassType, ClassType>> objectItem =
        QSharedPointer<FactoryObjectItem<BaseClassType, ClassType> >(
            new FactoryObjectItem<BaseClassType, ClassType>());

    objectItem->setVerbose(this->verbose());

    return (this->registerItem(key, objectItem));
}
