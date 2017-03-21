#include <arkhe/osgi/core/FactoryPluginItem.hpp>
#include <arkhe/osgi/core/ScopedCurrentDir.hpp>

template<typename BaseClassType>
bool osgi::FactoryPluginItem<BaseClassType>::load()
{
    osgi::ScopedCurrentDir scopedCurrentDir(QFileInfo(this->path()).path());
    this->Loader.setFileName(this->path());
    bool loaded = this->Loader.load();
    if (!loaded)
    {
        this->appendLoadErrorString(this->loadErrorString());
    }

    return loaded;
}

template<typename BaseClassType>
QString osgi::FactoryPluginItem<BaseClassType>::loadErrorString()const
{
    return this->Loader.errorString();
}

template<typename BaseClassType>
BaseClassType* osgi::FactoryPluginItem<BaseClassType>::instanciator()
{
  //qDebug() << "PluginItem::instantiate - name:" << this->path();
    QObject * object = this->Loader.instance();
    if (!object)
    {
        if (this->verbose())
        {
            this->appendLoadErrorString(QString("Failed to instantiate plugin: %1").arg(this->path()));
        }

        return (0);
    }

    BaseClassType* castedObject = qobject_cast<BaseClassType*>(object);
    if (!castedObject)
    {
        if (this->verbose())
        {
            this->appendLoadErrorString(
                QString("Plugin %1 - Failed to access expected interface [%2] - Instead got object of type [%3]")
                    .arg(this->path())
                    .arg(BaseClassType::staticMetaObject.className())
                    .arg(object->metaObject()->className()));
        }

        delete object;

    return (0);
    }
    
    return (castedObject);
}
