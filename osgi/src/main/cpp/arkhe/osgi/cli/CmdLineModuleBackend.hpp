#ifndef ARKHE_OSGI_CLI_CMDLINEMODULEBACKEND_HPP
#define ARKHE_OSGI_CLI_CMDLINEMODULEBACKEND_HPP

#include <QByteArray>
#include <arkhe/osgi/osgi.hpp>

/*!
 * @brief 
 * 
 */
template<typename T> 
class QList;
class QUrl;

namespace osgi
{
	namespace cli
	{
		class ARKHE_CORE_PLUGIN_FW_EXPORT CmdLineModuleBackend
		{

		public:
			CmdLineModuleBackend();
			virtual ~CmdLineModuleBackend();
			// virtual QString name() const = 0;
			// virtual QString description() const = 0;
			// virtual QList<QString> schemes() const = 0;
			// virtual qint64 timeStamp(const QUrl& location) const = 0;
			// virtual QByteArray rawXmlDescription(const QUrl& location, int timeout) = 0;
			// QByteArray rawXmlDescription(const QUrl& location);
			// virtual int timeOutForXmlRetrieval() const;
			// virtual CmdLineModuleFuture run(CmdLineModuleFrontend* frontend) = 0;
		protected:

		private:
		};		
	}
}
#endif
