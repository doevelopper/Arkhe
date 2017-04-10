#ifndef ARKHE_OSGI_CORE_FRAMEWORK_PLUGINSTORAGE_HPP
#define ARKHE_OSGI_CORE_FRAMEWORK_PLUGINSTORAGE_HPP

#include <QUrl>
#include <QStringList>
#include <QSharedPointer>

#include <arkhe/osgi/osgi.hpp>


/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		class PluginArchive;

		class PluginStorage
		{

		public:

			PluginStorage();
			virtual ~PluginStorage();

			virtual QSharedPointer<PluginArchive> insertPlugin(const QUrl& location, const QString& localPath) = 0;
			virtual QSharedPointer<PluginArchive> updatePluginArchive(QSharedPointer<PluginArchive> old, const QUrl& updateLocation, const QString& localPath) = 0;
			virtual void replacePluginArchive(QSharedPointer<PluginArchive> oldPA, QSharedPointer<PluginArchive> newPA) = 0;
			virtual bool removeArchive(QSharedPointer<PluginArchive> pa) = 0;
			virtual QList<QSharedPointer<PluginArchive> > getAllPluginArchives() const = 0;
			virtual QList<QString> getStartOnLaunchPlugins() const = 0;
			virtual void close() = 0;

		protected:

		private:

		};		
	}
}
#endif
