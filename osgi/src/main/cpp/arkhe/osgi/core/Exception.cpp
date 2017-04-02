#include <typeinfo>
#include <QString>
#include <QDebug>
#include <arkhe/osgi/core/Exception.hpp>

osgi::core::Exception::TraceManipulator::TraceManipulator(const Exception* e)
  : Exc(e)
{
}

QDebug osgi::core::Exception::TraceManipulator::print(QDebug dbg) const
{
    if (Exc)
    {
      Exc->printStackTrace(dbg);
    }
    return (dbg.maybeSpace());
}

osgi::core::Exception::Exception(const QString& msg)
  : Msg(msg)
  , NestedException(0)
{
}

osgi::core::Exception::Exception(const QString& msg, const Exception& cause)
  : Msg(msg)
  , NestedException(cause.clone())
{
}

osgi::core::Exception::Exception(const osgi::core::Exception& exc)
  : std::exception(exc)
  , BackTrace(exc)
  , Msg(exc.Msg)
{
    NestedException = exc.NestedException ? exc.NestedException->clone() : 0;
}

osgi::core::Exception::~Exception() throw()
{
  delete NestedException;
}

osgi::core::Exception& osgi::core::Exception::operator=(const osgi::core::Exception& exc)
{
    if (&exc != this)
    {
        delete NestedException;
        Msg = exc.Msg;
        NestedException = exc.NestedException ? exc.NestedException->clone() : 0;
    }
  return *this;
}


const osgi::core::Exception* osgi::core::Exception::cause() const throw()
{
  return NestedException;
}

void osgi::core::Exception::setCause(const osgi::core::Exception& cause)
{
    delete NestedException;
    NestedException = cause.clone();
}

const char *osgi::core::Exception::name() const throw()
{
  return "osgi::core::Exception";
}

const char* osgi::core::Exception::className() const throw()
{
    return typeid(*this).name();
}

const char* osgi::core::Exception::what() const throw()
{
    if (WhatMsg.empty())
    {
        WhatMsg = std::string(name());
        if (!Msg.isEmpty())
        {
            WhatMsg += ": ";
            WhatMsg += Msg.toStdString();
        }
    }
  return WhatMsg.c_str();
}

QString osgi::core::Exception::message() const throw()
{
    return Msg;
}

osgi::core::Exception::TraceManipulator osgi::core::Exception::printStackTrace() const
{
  return TraceManipulator(this);
}

osgi::core::Exception* osgi::core::Exception::clone() const
{
  return (new osgi::core::Exception(*this));
}

void osgi::core::Exception::rethrow() const
{
  throw *this;
}

QDebug osgi::core::Exception::printStackTrace(QDebug dbg) const
{
    QSet<const osgi::core::Exception*> dejaVu;
    dejaVu.insert(this);

  // Print our stack trace
    dbg.nospace() << this->what() << '\n';
    QList<QString> trace = stackTrace();
  foreach(QString traceElement, trace)
  {
    dbg.nospace() << "\tat " << qPrintable(traceElement) << '\n';
  }

  // Print cause, if any
    if (NestedException)
    {
        NestedException->printEnclosedStackTrace(dbg, trace, "Caused by: ", "", dejaVu);
    }
    return dbg;
}


void osgi::core::Exception::printEnclosedStackTrace(QDebug dbg, const QList<QString>& enclosingTrace,
                                                const QString& caption,
                                                const QString& prefix,
                                                QSet<const osgi::core::Exception*>& dejaVu)
{
    if (dejaVu.contains(this))
    {
        dbg.nospace() << "\t[CIRCULAR REFERENCE:" << this->what() << "]\n";
    }
    else
    { 
        dejaVu.insert(this);
        // Compute number of frames in common between this and enclosing trace
        QList<QString> trace = stackTrace();

        int m = trace.size() - 1;
        int n = enclosingTrace.size() - 1;

        while (m >= 0 && n >=0 && trace[m] == enclosingTrace[n])
        {
          m--;
          n--;
        }
        int framesInCommon = trace.size() - 1 - m;

        // Print our stack trace
        dbg.nospace() << qPrintable(prefix) << qPrintable(caption) << this->what() << '\n';
        for (int i = 0; i <= m; i++)
        {
          dbg.nospace() << qPrintable(prefix) << "\tat " << qPrintable(trace[i]) << '\n';
        }
        if (framesInCommon != 0)
        {
          dbg.nospace() << qPrintable(prefix) << "\t... " << framesInCommon << " more\n";
        }

    // Print cause, if any
        if (NestedException)
        {
            NestedException->printEnclosedStackTrace(dbg, trace, "Caused by: ", prefix, dejaVu);
        }
    }
}


QDebug operator<<(QDebug dbg, const osgi::core::Exception& exc)
{
    dbg << exc.what();
    return dbg.maybeSpace();
}

QDebug operator<<(QDebug dbg, const osgi::core::Exception::TraceManipulator& trace)
{
    return trace.print(dbg);
}
