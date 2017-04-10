#ifndef ARKHE_OSGI_BACKTRACECOLLECTORPRIVATE_HPP
#define ARKHE_OSGI_BACKTRACECOLLECTORPRIVATE_HPP

#include <QtCore/qglobal.h>
#include <QDebug>
#include <QScopedPointer>
#include <QTemporaryFile>
#include <QProcess>

namespace osgi
{
	namespace core 
	{
		class BacktraceCollectorPrivate
		{

		public:

		  BacktraceCollectorPrivate();
		  virtual ~BacktraceCollectorPrivate();

		  QProcess getDebugger() const;
		  void setDebugger(const QProcess &value);

		  QString getOutput() const;
		  void setOutput(const QString &value);

		  bool getErrorOccurred() const;
		  void setErrorOccurred(bool value);

		  // QScopedPointer<QTemporaryFile> getCommandFile() const;
		  // void setCommandFile(const QScopedPointer<QTemporaryFile> &value);

		  bool errorOccurred;
		  // QScopedPointer<QTemporaryFile> commandFile;
		  QProcess debugger;
		  QString output;

		private:


		};
	}
}
#endif
