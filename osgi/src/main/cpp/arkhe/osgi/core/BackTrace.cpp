#include <QList>
#include <vector>
#include <arkhe/osgi/core/BackTrace.hpp>

#include <stdlib.h>
#include <sstream>

size_t const osgi::core::BackTrace::DEFAULT_STACK_SIZE = 128;

osgi::core::BackTrace::BackTrace(const BackTrace& other)
  : d(new BackTracePrivate(*other.d.data()))
{
}
//*
osgi::core::BackTrace::BackTrace(size_t framesNumber)
  : d(new BackTracePrivate)
{
  if(framesNumber == 0)
  {
    return;
  }
  /*
  d->Frames.resize(framesNumber, 0);
  size_t size = d->trace(&d->Frames.front(), framesNumber);
  d->Frames.resize(size);
  */
}

osgi::core::BackTrace::~BackTrace() throw()
{
}

size_t osgi::core::BackTrace::stackSize() const
{
  //return d->Frames.size();
}

void* osgi::core::BackTrace::returnAddress(unsigned frameNumber) const
{
  if(frameNumber < stackSize())
  {
    //return d->Frames[frameNumber];
  }
  return 0;
}

QString osgi::core::BackTrace::stackFrame(unsigned frameNumber) const
{
 // if(frameNumber < d->Frames.size())
  {
    //return QString::fromStdString(d->getSymbol(d->Frames[frameNumber]));
  }
  return QString();
}

QList<QString> osgi::core::BackTrace::stackTrace() const
{
  QList<QString> trace;
/*
  if(d->Frames.empty())
  {
    return trace;
  }

  for (std::size_t i = 0; i < d->Frames.size(); ++i)
  {
        std::string s = d->getSymbol(d->Frames[i]);
        if (!s.empty())
        {
            trace.push_back(QString::fromStdString(s));
        }
  }
*/
  return trace;
  //std::ostringstream res;
  //d->writeSymbols(&d->Frames.front(), d->Frames.size(), res, framePrefix.toStdString());
  //return QString::fromStdString(res.str());
}
//*/