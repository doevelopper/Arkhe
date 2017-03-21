#include <arkhe/osgi/core/AbstractFactory.hpp>

template<typename BaseClassType>
osgi::AbstractFactory<BaseClassType>::AbstractFactory()
{
  this->Verbose = false;
  this->SharedRegisteredItemMap = QSharedPointer<HashType>(new HashType);
}

template<typename BaseClassType>
osgi::AbstractFactory<BaseClassType>::~AbstractFactory()
{
}

template<typename BaseClassType>
void osgi::AbstractFactory<BaseClassType>::printAdditionalInfo()
{
  qDebug() << "ctkAbstractFactory<BaseClassType> (" << this << ")";
  // TODO
}

template<typename BaseClassType>
BaseClassType* osgi::AbstractFactory<BaseClassType>::instantiate(const QString& itemKey)
{
  AbstractFactoryItem<BaseClassType>* _item = this->item(itemKey);
  BaseClassType* instance = 0;
  bool wasInstantiated = false;
  if (_item)
    {
    wasInstantiated = _item->isInstantiated();
    instance = wasInstantiated ? _item->instance() : _item->instantiate();
    }
  if (!wasInstantiated)
    {
    this->displayStatusMessage(instance ? QtDebugMsg : QtCriticalMsg,
                               QString("Attempt to instantiate \"%1\"").arg(itemKey),
                               instance ? "OK" : "Failed", this->verbose());
    if (_item)
      {
      if(!_item->instantiateErrorStrings().isEmpty())
        {
        qCritical().nospace() << qPrintable(QString(" ").repeated(2) + QLatin1String("Error(s):\n"))
                              << qPrintable(QString(" ").repeated(4) +
                                            _item->instantiateErrorStrings().join(
                                              QString("\n") + QString(" ").repeated(4)));
        }
      if(!_item->instantiateWarningStrings().isEmpty())
        {
        qWarning().nospace() << qPrintable(QString(" ").repeated(2) + QLatin1String("Warning(s):\n"))
                             << qPrintable(QString(" ").repeated(4) +
                                           _item->instantiateWarningStrings().join(
                                             QString("\n") + QString(" ").repeated(4)));
        }
      }
    }
  return instance;
}


template<typename BaseClassType>
osgi::AbstractFactoryItem<BaseClassType> * osgi::AbstractFactory<BaseClassType>::item(const QString& itemKey)const
{
    ConstIterator iter = this->RegisteredItemMap.find(itemKey);
    if ( iter == this->RegisteredItemMap.constEnd())
    {
      return 0;
    }

    return iter.value().data();
}

template<typename BaseClassType>
osgi::AbstractFactoryItem<BaseClassType> * osgi::AbstractFactory<BaseClassType>::sharedItem(const QString& itemKey)const
{
    if(this->SharedRegisteredItemMap.isNull())
    {
        return 0;
    }

    ConstIterator iter = this->SharedRegisteredItemMap.data()->find(itemKey);

    if ( iter == this->SharedRegisteredItemMap.data()->constEnd())
    {
        return 0;
    }

  return iter.value().data();
}

template<typename BaseClassType>
BaseClassType* osgi::AbstractFactory<BaseClassType>::instance(const QString& itemKey)
{
    osgi::AbstractFactoryItem<BaseClassType>* factoryItem = this->item(itemKey);
    return (factoryItem ? factoryItem->instance() : 0);
}

template<typename BaseClassType>
void osgi::AbstractFactory<BaseClassType>::uninstantiate(const QString& itemKey)
{
    AbstractFactoryItem<BaseClassType> * _item = this->item(itemKey);
    if (!_item)
    {
        return;
    }
    _item->uninstantiate();
}

template<typename BaseClassType>
void osgi::AbstractFactory<BaseClassType>::setVerbose(bool value)
{
    this->Verbose = value;
}

template<typename BaseClassType>
bool osgi::AbstractFactory<BaseClassType>::verbose()const
{
    return this->Verbose;
}

template<typename BaseClassType>
void osgi::AbstractFactory<BaseClassType>::setSharedItems(const QSharedPointer<HashType>& items)
{
    this->SharedRegisteredItemMap = items;
}

template<typename BaseClassType>
QSharedPointer<typename osgi::AbstractFactory<BaseClassType>::HashType>
osgi::AbstractFactory<BaseClassType>::sharedItems()
{
  return this->SharedRegisteredItemMap;
}

template<typename BaseClassType>
QStringList osgi::AbstractFactory<BaseClassType>::itemKeys() const
{
  // Since by construction, we checked if a name was already in the QHash,
  // there is no need to call 'uniqueKeys'
  return this->RegisteredItemMap.keys();
}

template<typename BaseClassType>
void osgi::AbstractFactory<BaseClassType>::displayStatusMessage(
    const QtMsgType& type, const QString& description, const QString& status, bool display)
{
    QString msg = QString("%1 [%2]").arg(description + " ", -70, QChar('.')).arg(status);
    if (display)
    {
        switch(type)
        {
            case QtFatalMsg:
                qFatal("%s", qPrintable(msg));
                break;
            case QtCriticalMsg:
                qCritical("%s", qPrintable(msg));
                break;
            case QtWarningMsg:
                qWarning("%s", qPrintable(msg));
                break;
            case QtDebugMsg:
                qDebug("%s", qPrintable(msg));
                break;
        }
    }
}

template<typename BaseClassType>
bool osgi::AbstractFactory<BaseClassType>::registerItem(const QString& key,
  const QSharedPointer<osgi::AbstractFactoryItem<BaseClassType> > & _item)
{
  // Sanity checks
    if (!_item)
    {
        if (this->verbose())
        {
          qDebug() << __FUNCTION__ << "key is empty - item: " << _item;
        }
        return false;
    }

    QString description = QString("Attempt to register \"%1\"").arg(key);

    if (this->item(key))
    {
        this->displayStatusMessage(QtWarningMsg, description, "Already registered", this->verbose());
        return false;
    }

    if (this->sharedItem(key))
    {
        this->displayStatusMessage(QtDebugMsg, description,
                               "Already registered in other factory", this->verbose());
        return false;
    }
  
  // Attempt to load it
    if (!_item->load())
    {
        this->displayStatusMessage(QtCriticalMsg, description, "Failed", this->verbose());
        if(!_item->loadErrorStrings().isEmpty())
        {
            qCritical().nospace() << qPrintable(QString(" ").repeated(2) + QLatin1String("Error(s):\n"))
                            << qPrintable(QString(" ").repeated(4) +
                                          _item->loadErrorStrings().join(
                                            QString("\n") + QString(" ").repeated(4)));
        }

        if(!_item->loadWarningStrings().isEmpty())
        {
            qWarning().nospace() << qPrintable(QString(" ").repeated(2) + QLatin1String("Warning(s):\n"))
                           << qPrintable(QString(" ").repeated(4) +
                                         _item->loadWarningStrings().join(
                                           QString("\n") + QString(" ").repeated(4)));
        }

        return false;
    }
  
  // Store item reference using a QSharedPointer
    this->RegisteredItemMap.insert(key, _item);
    this->SharedRegisteredItemMap.data()->insert(key, _item);

    this->displayStatusMessage(QtDebugMsg, description, "OK", this->verbose());
    return true;
}
