#ifndef ARKHE_OSGI_ABSTRACTFACTORYITEM_HPP
#define ARKHE_OSGI_ABSTRACTFACTORYITEM_HPP

#include <QString>
#include <QHash>
#include <QSharedPointer>
#include <QStringList>

#include <arkhe/osgi/osgi.hpp>
/*!
 * @brief AbstractFactoryItem the base class of factory items.
 */
namespace osgi
{

	template<typename BaseClassType>
	class AbstractFactoryItem
	{
	public:
        //explicit AbstractFactoryItem();
        AbstractFactoryItem();
        virtual ~AbstractFactoryItem();
      
        virtual bool load() = 0;
      
        QStringList instantiateErrorStrings()const;
        QStringList instantiateWarningStrings()const;
      
        QStringList loadErrorStrings()const;
        QStringList loadWarningStrings()const;
      
        BaseClassType* instantiate();
        bool isInstantiated()const;
        BaseClassType* instance()const;
        virtual void uninstantiate();
      
        void setVerbose(bool value);
        bool verbose()const;
        
    protected:
    
        void appendInstantiateErrorString(const QString& msg);
        void clearInstantiateErrorStrings();
      
        void appendInstantiateWarningString(const QString& msg);
        void clearInstantiateWarningStrings();
      
        void appendLoadErrorString(const QString& msg);
        void clearLoadErrorStrings();
      
        void appendLoadWarningString(const QString& msg);
        void clearLoadWarningStrings();
      
        /// Must be reimplemented in subclasses to instanciate a BaseClassType*
        virtual BaseClassType* instanciator() = 0;
        BaseClassType* Instance;
        
    private:
        QStringList InstantiateErrorStrings;
        QStringList InstantiateWarningStrings;
        QStringList LoadErrorStrings;
        QStringList LoadWarningStrings;
        bool Verbose;
	};
		
}
#endif
