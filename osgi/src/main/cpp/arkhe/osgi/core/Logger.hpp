#ifndef ARKHE_OSGI_LOGGER_HPP
#define ARKHE_OSGI_LOGGER_HPP

#include <QFileInfo>
#include <QPluginLoader>

#include <arkhe/osgi/osgi.hpp>


/*!
 * @brief .
 */
namespace osgi
{
	namespace core
	{
		class ctkLoggerPrivate;

		class ARKHE_CORE_EXPORT Logger : public QObject
		{
		public:
			class LoggerPrivate
			{
				public:
				//Log4cxx::Logger *logger;
			};

			using Superclass = QObject;

			explicit Logger(QString name, QObject* parent = 0);
			Logger();
			virtual ~Logger();
			void configure();
			void debug(const QString& s);
			void info(const QString& s);
			void trace(const QString& s);
			void warn(const QString& s);
			void error(const QString& s);
			void fatal(const QString& s);

			void setOff();
			void setDebug();
			void setInfo();
			void setTrace();
			void setWarn();
			void setError();
			void setFatal();
		protected:

			QScopedPointer<LoggerPrivate> d_ptr;

		private:
		  Q_DECLARE_PRIVATE(Logger);
		  Q_DISABLE_COPY(Logger);
		};
	}
		
}
#endif
