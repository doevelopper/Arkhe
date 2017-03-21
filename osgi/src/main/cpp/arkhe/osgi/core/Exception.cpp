#include <typeinfo>
#include <QString>
#include <QDebug>
#include <arkhe/osgi/core/Exception.hpp>

osgi::Exception::TraceManipulator::TraceManipulator(const Exception* e)
  : Exc(e)
{
}

QDebug osgi::Exception::TraceManipulator::print(QDebug dbg) const
{
    if (Exc)
    {
      Exc->printStackTrace(dbg);
    }
    return (dbg.maybeSpace());
}

osgi::Exception::Exception(const QString& msg)
  : Msg(msg)
  , NestedException(0)
{
}

osgi::Exception::Exception(const QString& msg, const Exception& cause)
  : Msg(msg)
  , NestedException(cause.clone())
{
}

osgi::Exception::Exception(const osgi::Exception& exc)
  : std::exception(exc)
  , BackTrace(exc)
  , Msg(exc.Msg)
{
    NestedException = exc.NestedException ? exc.NestedException->clone() : 0;
}

osgi::Exception::~Exception() throw()
{
  delete NestedException;
}

osgi::Exception& osgi::Exception::operator=(const osgi::Exception& exc)
{
    if (&exc != this)
    {
        delete NestedException;
        Msg = exc.Msg;
        NestedException = exc.NestedException ? exc.NestedException->clone() : 0;
    }
  return *this;
}


const osgi::Exception* osgi::Exception::cause() const throw()
{
  return NestedException;
}

void osgi::Exception::setCause(const osgi::Exception& cause)
{
    delete NestedException;
    NestedException = cause.clone();
}

const char *osgi::Exception::name() const throw()
{
  return "osgi::Exception";
}

const char* osgi::Exception::className() const throw()
{
    return typeid(*this).name();
}

const char* osgi::Exception::what() const throw()
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

QString osgi::Exception::message() const throw()
{
    return Msg;
}

osgi::Exception::TraceManipulator osgi::Exception::printStackTrace() const
{
  return TraceManipulator(this);
}

osgi::Exception* osgi::Exception::clone() const
{
  return (new osgi::Exception(*this));
}

void osgi::Exception::rethrow() const
{
  throw *this;
}

QDebug osgi::Exception::printStackTrace(QDebug dbg) const
{
    QSet<const osgi::Exception*> dejaVu;
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


void osgi::Exception::printEnclosedStackTrace(QDebug dbg, const QList<QString>& enclosingTrace,
                                                const QString& caption,
                                                const QString& prefix,
                                                QSet<const osgi::Exception*>& dejaVu)
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


QDebug operator<<(QDebug dbg, const osgi::Exception& exc)
{
    dbg << exc.what();
    return dbg.maybeSpace();
}

QDebug operator<<(QDebug dbg, const osgi::Exception::TraceManipulator& trace)
{
    return trace.print(dbg);
}
