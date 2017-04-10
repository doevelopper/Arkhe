#ifndef ARKHE_OSGI_BACKTRACECOLLECTOR_HPP
#define ARKHE_OSGI_BACKTRACECOLLECTOR_HPP

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include <QProcess>

namespace osgi
{
	namespace core 
	{

		QT_FORWARD_DECLARE_CLASS(BacktraceCollectorPrivate)

		class BacktraceCollector : public QObject
		{
		  Q_OBJECT
		public:
			explicit BacktraceCollector(QObject *parent = 0);
			virtual  ~BacktraceCollector();
			void run(Q_PID pid);
			bool isRunning() const;
			void kill();
		protected:

		private:
			QString createTemporaryCommandFile();
			BacktraceCollectorPrivate *d;
		signals:
			void error(const QString &errorMessage);
			void backtrace(const QString &backtrace);
			void backtraceChunk(const QString &chunk);

		public slots:

		private slots:
			void onDebuggerOutputAvailable();
			void onDebuggerFinished(int exitCode, QProcess::ExitStatus exitStatus);
			void onDebuggerError(QProcess::ProcessError err);
		};
	}
}
#endif
