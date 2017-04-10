#include <arkhe/osgi/core/framework/ServiceProperties.hpp>

osgi::core::ServiceProperties::ServiceProperties()
{
}

osgi::core::ServiceProperties::~ServiceProperties()
{
}

osgi::core::ServiceProperties::ServiceProperties(const osgi::Properties& props)
{
  for(osgi::Properties::ConstIterator i = props.begin(), end = props.end();
      i != end; ++i)
  {
    if (find(i.key()) != -1)
    {
      QString msg("ctkProperties object contains case variants of the key: ");
      msg += i.key();
      // throw InvalidArgumentException(msg);
    }
    ks.append(i.key());
    vs.append(i.value());
  }
}

QVariant osgi::core::ServiceProperties::value(const QString &key) const
{
  int index = find(key);
  if (index < 0) return QVariant();
  return vs[index];
}

QVariant osgi::core::ServiceProperties::value(int index) const
{
  return (index < 0 || index >= vs.size()) ? QVariant() : vs[index];
}

QStringList osgi::core::ServiceProperties::keys() const
{
  QStringList result;
  for(int i = 0; i < ks.size(); ++i)
  {
    result.append(ks[i]);
  }
  return result;
}

int osgi::core::ServiceProperties::find(const QString &key) const
{
  for (int i = 0; i < ks.size(); ++i)
  {
    if (ks[i].compare(key, Qt::CaseInsensitive) == 0)
      return i;
  }
  return -1;
}

int osgi::core::ServiceProperties::findCaseSensitive(const QString &key) const
{
  for (int i = 0; i < ks.size(); ++i)
  {
    if (ks[i] == key)
      return i;
  }
  return -1;
}
