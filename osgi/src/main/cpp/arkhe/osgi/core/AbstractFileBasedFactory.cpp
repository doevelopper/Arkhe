#include <QDirIterator>
#include <arkhe/osgi/core/AbstractFileBasedFactory.hpp>
#include <arkhe/osgi/core/AbstractFactoryFileBasedItem.hpp>

template<typename BaseClassType>
QString osgi::core::AbstractFileBasedFactory<BaseClassType>::pathway(const QString& key)
{
    AbstractFactoryFileBasedItem<BaseClassType>* _item =
        dynamic_cast<AbstractFactoryFileBasedItem<BaseClassType>*>(this->item(key));
    //Q_ASSERT(_item);
     Q_ASSERT_X(_item != 0, "AbstractFileBasedFactory", "item is null");

    return _item->path();
}

template<typename BaseClassType>
void osgi::core::AbstractFileBasedFactory<BaseClassType>::registerAllFileItems(const QStringList& directories)
{

    foreach (QString path, directories) //! Process one path at a time
    {
        QDirIterator it(path);
        while (it.hasNext())
        {
            it.next();
            QFileInfo fileInfo = it.fileInfo();
            if (fileInfo.isSymLink())
            {
                //*! symLinkTarget() handles links pointing to symlinks.
                //*! How about a symlink pointing to a symlink ?
                fileInfo = QFileInfo(fileInfo.symLinkTarget());
            }

            if (!this->isValidFile(fileInfo)) //*! Skip if item isn't a file
            {
                continue;
            }

            this->registerFileItem(fileInfo);
      }
    }
}

template<typename BaseClassType>
QString osgi::core::AbstractFileBasedFactory<BaseClassType>::itemKey(const QFileInfo& fileInfo)const
{
  return this->fileNameToKey(fileInfo.filePath());
}

template<typename BaseClassType>
QString osgi::core::AbstractFileBasedFactory<BaseClassType>::registerFileItem(const QFileInfo& fileInfo)
{
    QString key = this->itemKey(fileInfo);
    bool registered = this->registerFileItem(key, fileInfo);
    return (registered ? key : QString());
}

template<typename BaseClassType>
bool osgi::core::AbstractFileBasedFactory<BaseClassType>::registerFileItem(const QString& key, const QFileInfo& fileInfo)
{
    QString description = QString("Attempt to register \"%1\"").arg(key);

    if (this->item(key))
    {
        this->displayStatusMessage(QtWarningMsg, description, "Already registered", this->verbose());
        return true;
    }

    if(this->sharedItem(key))
    {
        this->displayStatusMessage(QtDebugMsg, description,"Already registered in other factory", this->verbose());
        return (false);
    }

    QSharedPointer<osgi::core::AbstractFactoryItem<BaseClassType> > itemToRegister(this->createFactoryFileBasedItem());
    
    if (itemToRegister.isNull())
    {
        this->displayStatusMessage(QtWarningMsg, description,"Failed to create FileBasedItem", this->verbose());
        return (false);
    }
    
    dynamic_cast<osgi::core::AbstractFactoryFileBasedItem<BaseClassType>*>(itemToRegister.data())->setPath(fileInfo.filePath());
    this->initItem(itemToRegister.data());
    return (this->registerItem(key, itemToRegister));
}

template<typename BaseClassType>
bool osgi::core::AbstractFileBasedFactory<BaseClassType>::isValidFile(const QFileInfo& file)const
{
    return file.isFile();
}

template<typename BaseClassType>
osgi::core::AbstractFactoryItem<BaseClassType>* osgi::core::AbstractFileBasedFactory<BaseClassType>::createFactoryFileBasedItem()
{
    return 0;
}

template<typename BaseClassType>
void osgi::core::AbstractFileBasedFactory<BaseClassType>::initItem(osgi::core::AbstractFactoryItem<BaseClassType>* item)
{
    item->setVerbose(this->verbose());
}

template<typename BaseClassType>
QString osgi::core::AbstractFileBasedFactory<BaseClassType>::fileNameToKey(const QString& fileName)const
{
    return QFileInfo(fileName).baseName();
}
