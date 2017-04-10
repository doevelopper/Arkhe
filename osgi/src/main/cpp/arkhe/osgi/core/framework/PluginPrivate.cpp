#include <typeinfo>

#include <arkhe/osgi/core/framework/PluginPrivate.hpp>

const osgi::core::Plugin::States osgi::core::PluginPrivate::RESOLVED_FLAGS = osgi::core::Plugin::RESOLVED 
	| osgi::core::Plugin::STARTING | osgi::core::Plugin::ACTIVE | osgi::core::Plugin::STOPPING;

osgi::core::PluginPrivate::PluginPrivate()
{
}

osgi::core::PluginPrivate::PluginPrivate(QWeakPointer<Plugin> qq, PluginFrameworkContext* fw, QSharedPointer<PluginArchive> pa)
    : q_ptr(qq)
	, fwCtx(fw)
	, id(pa->getPluginId())
	, location(pa->getPluginLocation().toString())
	, state(Plugin::INSTALLED)
	, archive(pa)
	, pluginContext(0)
	, pluginActivator(0)
	, pluginLoader(pa->getLibLocation())
	, resolveFailException(0)
	, eagerActivation(false)
	, wasStarted(false)
{
  //TODO
  //checkCertificates(pa);

  // Get library load hints
  if (fw->props.contains(PluginConstants::FRAMEWORK_PLUGIN_LOAD_HINTS))
  {
    QVariant loadHintsVariant = fw->props[PluginConstants::FRAMEWORK_PLUGIN_LOAD_HINTS];
    if (loadHintsVariant.isValid())
    {
      QLibrary::LoadHints loadHints = loadHintsVariant.value<QLibrary::LoadHints>();
      pluginLoader.setLoadHints(loadHints);
    }
  }

  checkManifestHeaders();

  pluginDir = fwCtx->getDataStorage(id);
//  int oldStartLevel = archive->getStartLevel();
  try
  {
    //TODO: StartLevel Service
    //if (fwCtx->startLevelController == 0)
    //{
      archive->setStartLevel(0);
    //}
//    else
//    {
//      if (oldStartLevel == -1)
//      {
//        archive->setStartLevel(fwCtx->startLevelController->getInitialPluginStartLevel());
//      }
//    }
  }
  catch (const std::exception& e)
  {
    qDebug() << "Failed to set start level on #" << id << ":" << e.what();
  }

  lastModified = archive->getLastModified();
  if (lastModified.isNull())
  {
    modified();
  }

  // fill require list
  QString requireString = archive->getAttribute(PluginConstants::REQUIRE_PLUGIN);
  QList<QMap<QString, QStringList> > requireList = PluginFrameworkUtil::parseEntries(PluginConstants::REQUIRE_PLUGIN,
                                                                                        requireString, true, true, false);
  QListIterator<QMap<QString, QStringList> > i(requireList);
  while (i.hasNext())
  {
    const QMap<QString, QStringList>& e = i.next();
    const QStringList& res = e.value(PluginConstants::RESOLUTION_DIRECTIVE);
    const QStringList& version = e.value(PluginConstants::PLUGIN_VERSION_ATTRIBUTE);
    RequirePlugin* rp = new RequirePlugin(this, e.value("$key").front(),
                                                res.empty() ? QString() : res.front(),
                                                version.empty() ? QString() : version.front());
    require.push_back(rp);
  }
}

osgi::core::PluginPrivate::PluginPrivate(QWeakPointer<Plugin> qq,
                                   PluginFrameworkContext* fw,
                                   long id, const QString& loc, const QString& sym, const Version& ver)
: q_ptr(qq)
, fwCtx(fw)
, id(id)
, location(loc)
, symbolicName(sym)
, version(ver)
, state(Plugin::INSTALLED)
, archive(0)
, pluginContext(0)
, pluginActivator(0)
, resolveFailException(0)
, eagerActivation(false)
, wasStarted(false)
{
  modified();
}


osgi::core::PluginPrivate::~PluginPrivate()
{
  qDeleteAll(require);
}

void osgi::core::PluginPrivate::LockObject::lock()
{
  m_Lock.lock();
}


bool osgi::core::PluginPrivate::LockObject::tryLock()
{
  return m_Lock.tryLock();
}

bool osgi::core::PluginPrivate::LockObject::tryLock(int timeout)
{
  return m_Lock.tryLock(timeout);
}

void osgi::core::PluginPrivate::LockObject::unlock()
{
  m_Lock.unlock();
}


bool osgi::core::PluginPrivate::LockObject::wait(unsigned long time)
{
  return m_Condition.wait(&m_Lock, time);
}

void osgi::core::PluginPrivate::LockObject::wakeAll()
{
  m_Condition.wakeAll();
}


void osgi::core::PluginPrivate::LockObject::wakeOne()
{
  m_Condition.wakeOne();
}


osgi::core::Plugin::State osgi::core::PluginPrivate::getUpdatedState()
{
  if (state & Plugin::INSTALLED)
  {
    Locker sync(&operationLock);
    getUpdatedState_unlocked();
  }
  return state;
}

osgi::core::Plugin::State osgi::core::PluginPrivate::getUpdatedState_unlocked()
{
  if (state & Plugin::INSTALLED)
  {
    try
    {
      if (state == Plugin::INSTALLED)
      {
        operation.fetchAndStoreOrdered(RESOLVING);
        fwCtx->resolvePlugin(this);
        state = Plugin::RESOLVED;
        // TODO plugin threading
        //bundleThread().bundleChanged(new BundleEvent(BundleEvent.RESOLVED, this));
        fwCtx->listeners.emitPluginChanged( PluginEvent(PluginEvent::RESOLVED, this->q_func()));
        operation.fetchAndStoreOrdered(IDLE);
      }
    }
    // catch (const PluginException& pe)
    {
      if (resolveFailException) delete resolveFailException;
      resolveFailException = new PluginException(pe);
      this->fwCtx->listeners.frameworkError(this->q_func(), pe);
    }
  }
  return state;
}

QFileInfo osgi::core::PluginPrivate::getDataRoot()
{
  return pluginDir;
}

void osgi::core::PluginPrivate::setStateInstalled(bool sendEvent)
{
  Locker sync(&operationLock);

  // Make sure that the context is invalid
  if (pluginContext != 0)
  {
    pluginContext->d_func()->invalidate();
    pluginContext.reset();
  }
  state = Plugin::INSTALLED;
  if (sendEvent)
  {
    operation.fetchAndStoreOrdered(UNRESOLVING);
    // TODO: plugin thread
    //bundleThread().bundleChanged(new BundleEvent(BundleEvent.UNRESOLVED, this));
    fwCtx->listeners.emitPluginChanged(PluginEvent(PluginEvent::UNRESOLVED, this->q_func()));
  }
  operation.fetchAndStoreOrdered(IDLE);
}


void osgi::core::PluginPrivate::purge()
{
  if (state == Plugin::UNINSTALLED)
  {
    fwCtx->plugins->remove(location);
  }
//  Vector fix = oldGenerations;
//  if (fix != null) {
//    oldGenerations = null;
//    for (Iterator i = fix.iterator(); i.hasNext();) {
//      ((BundleGeneration)i.next()).purge(true);
//    }
//  }
}


void osgi::core::PluginPrivate::setAutostartSetting(const Plugin::StartOptions& setting) {
  try
  {
    if (archive)
    {
      archive->setAutostartSetting(setting);
    }
  }
  // catch (const PluginDatabaseException& e)
  {
    this->fwCtx->listeners.frameworkError(this->q_func(), e);
  }
}

void osgi::core::PluginPrivate::ignoreAutostartSetting()
{
  try
  {
    if (archive)
    {
      archive->setAutostartSetting(-1);
    }
  }
  catch (const PluginDatabaseException& e)
  {
    this->fwCtx->listeners.frameworkError(this->q_func(), e);
  }
}


void osgi::core::PluginPrivate::modified()
{
  lastModified = QDateTime::currentDateTime();
  if (archive)
  {
    archive->setLastModified(lastModified);
  }
}

void osgi::core::PluginPrivate::checkManifestHeaders()
{
  symbolicName = archive->getAttribute(PluginConstants::PLUGIN_SYMBOLICNAME);

  if (symbolicName.isEmpty())
  {
    // throw InvalidArgumentException(QString("Plugin has no symbolic name, location=") +  location);
  }

  QString mpv = archive->getAttribute(PluginConstants::PLUGIN_VERSION);
  if (!mpv.isEmpty())
  {
    try
    {
      version = Version(mpv);
    }
    catch (const std::exception& e)
    {
      throw InvalidArgumentException(QString("Plugin does not specify a valid ") + PluginConstants::PLUGIN_VERSION + " header. Got exception: " + e.what());
    }
  }

  QSharedPointer<Plugin> snp = fwCtx->plugins->getPlugin(symbolicName, version);
  // TBD! Should we allow update to same version?
  if (!snp.isNull() && snp->d_func() != this)
  {
    throw InvalidArgumentException(QString("Plugin with same symbolic name and version is already installed (")
                                      + symbolicName + ", " + version.toString() + ")");
  }

  QString ap = archive->getAttribute(PluginConstants::PLUGIN_ACTIVATIONPOLICY);
  if (PluginConstants::ACTIVATION_EAGER == ap)
  {
    eagerActivation = true;
  }

}

void osgi::core::PluginPrivate::finalizeActivation()
{
  Locker sync(&operationLock);

  // 4: Resolve plugin (if needed)
  switch (getUpdatedState_unlocked())
  {
  case Plugin::INSTALLED:
    Q_ASSERT_X(resolveFailException != 0, Q_FUNC_INFO, "no resolveFailException");
    throw PluginException(*resolveFailException);
  case Plugin::STARTING:
    if (operation.fetchAndAddOrdered(0) == ACTIVATING) return; // finalization already in progress.
    // Lazy activation; fall through to RESOLVED.
  case Plugin::RESOLVED:
  {
    //6:
    state = Plugin::STARTING;
    operation.fetchAndStoreOrdered(ACTIVATING);
    if (fwCtx->debug.lazy_activation)
    {
      qDebug() << "activating #" << this->id;
    }
    //7:
    if (!pluginContext)
    {
      pluginContext.reset(new PluginContext(this));
    }
    // start dependencies
    startDependencies();
    //TODO plugin threading
    //RuntimeException* e = bundleThread().callStart0(this);
    RuntimeException* e = start0();
    operation.fetchAndStoreOrdered(IDLE);
    operationLock.wakeAll();
    if (e)
    {
      RuntimeException re(*e);
      delete e;
      throw re;
    }
    break;
  }
  case Plugin::ACTIVE:
    break;
  case Plugin::STOPPING:
    // This happens if start is called from inside the PluginActivator::stop method.
    // Don't allow it.
    throw PluginException("start called from PluginActivator::stop",
                             PluginException::ACTIVATOR_ERROR);
  case Plugin::UNINSTALLED:
    throw IllegalStateException("Plugin is in UNINSTALLED state");
  }
}


const osgi::core::RuntimeException* osgi::core::PluginPrivate::stop0()
{
  wasStarted = state == ctkPlugin::ACTIVE;
  // 5:
  state = Plugin::STOPPING;
  operation.fetchAndStoreOrdered(DEACTIVATING);
  // 6-13:
  // TODO plugin threading
  //const RuntimeException* savedException = pluginThread().callStop1(this);
  const RuntimeException* savedException = stop1();
  if (state != Plugin::UNINSTALLED)
  {
    state = Plugin::RESOLVED;
    // TODO plugin threading
    //bundleThread().bundleChanged(new BundleEvent(BundleEvent.STOPPED, this));
    fwCtx->listeners.emitPluginChanged(PluginEvent(PluginEvent::STOPPED, this->q_func()));

    operationLock.wakeAll();
    operation.fetchAndStoreOrdered(IDLE);
  }
  return savedException;
}


const osgi::core::RuntimeException* osgi::core::PluginPrivate::stop1()
{
  const RuntimeException* res = 0;

  //6:
  fwCtx->listeners.emitPluginChanged(PluginEvent(PluginEvent::STOPPING, q_func()));

  //7:
  if (wasStarted && pluginActivator)
  {
    try
    {
      pluginActivator->stop(pluginContext.data());
      if (state != Plugin::STOPPING)
      {
        if (state == Plugin::UNINSTALLED)
        {
          return new IllegalStateException("Plug-in is uninstalled");
        }
        else
        {
          return new IllegalStateException("Plug-in changed state because of refresh during stop");
        }
      }
    }
    catch (const Exception& e)
    {
      res = new PluginException("Plugin::stop: PluginActivator stop failed",
                                   PluginException::ACTIVATOR_ERROR, e);
    }
    catch (...)
    {
      res = new PluginException("Plugin::stop: PluginActivator stop failed",
                                   PluginException::ACTIVATOR_ERROR);
    }
    pluginActivator = 0;
  }

  if (operation.fetchAndAddOrdered(0) == DEACTIVATING)
  {
    // Call hooks after we've called PluginActivator::stop(), but before we've
    // cleared all resources
    if (pluginContext)
    {
      // TODO service listener hooks
      //fwCtx->listeners.serviceListeners.hooksBundleStopped(this);

      //8-10:
      removePluginResources();
      pluginContext->d_func()->invalidate();
      pluginContext.reset();
    }
  }

  // This would unload the shared library and delete the activator if
  // there are no dependencies. However, objects from the plug-in might
  // have been created via C-function symbol lookups. Hence we cannot
  // safely unload the DLL. Maybe implement a in-DLL counter later
  // (http://stackoverflow.com/questions/460809/c-dll-unloading-issue and
  // http://boost.2283326.n4.nabble.com/shared-ptr-A-smarter-smart-pointer-proposal-for-dynamic-libraries-td2649749.html).
  // The activator itself will be delete during program termination
  // (by the QPluginLoader instance).
  //pluginLoader.unload();

  return res;
}


void osgi::core::PluginPrivate::update0(const QUrl& updateLocation, bool wasActive)
{
  const bool wasResolved = state == Plugin::RESOLVED;
  const int oldStartLevel = getStartLevel();
  QSharedPointer<PluginArchive> newArchive;

  operation.fetchAndStoreOrdered(UPDATING);
  try
  {
    // New plugin as stream supplied?
    QUrl updateUrl(updateLocation);
    if (updateUrl.isEmpty())
    {
      // Try Plugin-UpdateLocation
      QString update = archive != 0 ? archive->getAttribute(PluginConstants::PLUGIN_UPDATELOCATION) : QString();
      if (update.isEmpty())
      {
        // Take original location
        updateUrl = location;
      }
    }

    if(updateUrl.scheme() != "file")
    {
      QString msg = "Unsupported update URL:";
      msg += updateUrl.toString();
      throw PluginException(msg);
    }

    newArchive = fwCtx->storage->updatePluginArchive(archive, updateUrl, updateUrl.toLocalFile());
    //checkCertificates(newArchive);
    checkManifestHeaders();
    newArchive->setStartLevel(oldStartLevel);
    fwCtx->storage->replacePluginArchive(archive, newArchive);
  }
  catch (const std::exception& e)
  {
    if (!newArchive.isNull())
    {
      newArchive->purge();
    }
    operation.fetchAndStoreOrdered(IDLE);
    if (wasActive)
    {
      try
      {
        this->q_func().data()->start();
      }
      catch (const PluginException& pe)
      {
        fwCtx->listeners.frameworkError(this->q_func(), pe);
      }
    }
    try
    {
      const PluginException& pe = dynamic_cast<const PluginException&>(e);
      throw pe;
    }
    catch (std::bad_cast)
    {
      throw PluginException(QString("Failed to get update plugin: ") + e.what(),
                               PluginException::UNSPECIFIED);
    }
  }

  bool purgeOld = false;
  // TODO: check if dependent plug-ins are started. If not, set purgeOld to true.

  // Activate new plug-in
  QSharedPointer<PluginArchive> oldArchive = archive;
  archive = newArchive;
  cachedRawHeaders.clear();
  state = Plugin::INSTALLED;

  // Purge old archive
  if (purgeOld)
  {
    //secure.purge(this, oldProtectionDomain);
    if (oldArchive != 0)
    {
      oldArchive->purge();
    }
  }

  // Broadcast events
  if (wasResolved)
  {
    // TODO: use plugin threading
    //bundleThread().bundleChanged(new BundleEvent(BundleEvent.UNRESOLVED, this));
    fwCtx->listeners.emitPluginChanged(PluginEvent(PluginEvent::UNRESOLVED, this->q_func()));
  }
  //bundleThread().bundleChanged(new BundleEvent(BundleEvent.UPDATED, this));
  fwCtx->listeners.emitPluginChanged(PluginEvent(PluginEvent::UPDATED, this->q_func()));
  operation.fetchAndStoreOrdered(IDLE);

   // Restart plugin previously stopped in the operation
   if (wasActive)
   {
     try
     {
       this->q_func().data()->start();
     }
     catch (const PluginException& pe)
     {
       fwCtx->listeners.frameworkError(this->q_func(), pe);
     }
   }
 }


int osgi::core::PluginPrivate::getStartLevel()
{
  if (archive != 0)
  {
    return archive->getStartLevel();
  }
  else
  {
    return 0;
  }
}


void osgi::core::PluginPrivate::waitOnOperation(LockObject* lock, const QString& src, bool longWait)
{
  if (operation.fetchAndAddOrdered(0) != IDLE)
  {
    qint64 left = longWait ? 20000 : 500;
    QDateTime waitUntil = QDateTime::currentDateTime().addMSecs(left);
    do
    {
      lock->wait(left);
      if (operation.fetchAndAddOrdered(0) == IDLE)
      {
        return;
      }
      // TODO use Qt 4.7 QDateTime::msecsTo() API
      //left = QDateTime::currentDateTime().msecsTo(waitUntil);
      left = ::msecsTo(QDateTime::currentDateTime(), waitUntil);
    } while (left > 0);

    QString op;
    switch (operation.fetchAndAddOrdered(0))
    {
    case IDLE:
      // Should not happen!
      return;
    case ACTIVATING:
      op = "start";
      break;
    case DEACTIVATING:
      op = "stop";
      break;
    case RESOLVING:
      op = "resolve";
      break;
    case UNINSTALLING:
      op = "uninstall";
      break;
    case UNRESOLVING:
      op = "unresolve";
      break;
    case UPDATING:
      op = "update";
      break;
    default:
      op = "unknown operation";
      break;
    }
    throw PluginException(src + " called during " + op + " of plug-in",
                             PluginException::STATECHANGE_ERROR);
  }
}


QStringList osgi::core::PluginPrivate::findResourceEntries(const QString& path,
                                                  const QString& pattern, bool recurse) const
{
  QStringList result;
  QStringList resources = archive->findResourcesPath(path);
  foreach(QString fp, resources)
  {
    QString lastComponentOfPath = fp.section('/', -1);
    bool isDirectory = fp.endsWith("/");

    if (!isDirectory &&
        (pattern.isNull() || PluginFrameworkUtil::filterMatch(pattern, lastComponentOfPath)))
    {
      result << (path + fp);
    }
    if (isDirectory && recurse)
    {
      QStringList subResources = findResourceEntries(fp, pattern, recurse);
      foreach (QString subResource, subResources)
      {
        result << (path + subResource);
      }
    }
  }
  return result;
}


void osgi::core::PluginPrivate::startDependencies()
{
  QListIterator<RequirePlugin*> i(this->require);
  while (i.hasNext())
  {
    RequirePlugin* pr = i.next();
    QList<Plugin*> pl = fwCtx->plugins->getPlugins(pr->name, pr->pluginRange);
    if (pl.isEmpty())
    {
      if (pr->resolution == PluginConstants::RESOLUTION_MANDATORY)
      {
        // We should never get here, since the plugin can only be
        // started if all its dependencies could be resolved.
        throw PluginException(
            QString("Internal error: dependent plugin %1 inside version range %2 is not installed.").
            arg(pr->name).arg(pr->pluginRange.toString()));
      }
      else
      {
        continue;
      }
    }

    // We take the first plugin in the list (highest version number)
    // Immediately start the dependencies (no lazy activation) but do not
    // change the autostart setting of the plugin.
    pl.front()->start(Plugin::START_TRANSIENT);
  }
}


osgi::core::PluginException* osgi::core::PluginPrivate::start0()
{
  PluginException* res = 0;

  fwCtx->listeners.emitPluginChanged(PluginEvent(PluginEvent::STARTING, this->q_func()));

  PluginException::Type error_type = PluginException::MANIFEST_ERROR;
  try {
    pluginLoader.load();
    if (!pluginLoader.isLoaded())
    {
      error_type = PluginException::ACTIVATOR_ERROR;
      throw PluginException(QString("Loading plugin %1 failed: %2").arg(pluginLoader.fileName()).arg(pluginLoader.errorString()),
                               PluginException::ACTIVATOR_ERROR);
    }

    pluginActivator = qobject_cast<PluginActivator*>(pluginLoader.instance());
    if (!pluginActivator)
    {
      throw PluginException(QString("Creating PluginActivator instance from %1 failed: %2").arg(pluginLoader.fileName()).arg(pluginLoader.errorString()),
                               PluginException::ACTIVATOR_ERROR);
    }

    pluginActivator->start(pluginContext.data());

    if (state != Plugin::STARTING)
    {
      error_type = PluginException::STATECHANGE_ERROR;
      if (Plugin::UNINSTALLED == state)
      {
        throw PluginException("Plugin uninstalled during start()", PluginException::STATECHANGE_ERROR);
      }
      else
      {
        throw PluginException("Plugin changed state because of refresh during start()", PluginException::STATECHANGE_ERROR);
      }
    }
    state = Plugin::ACTIVE;
  }
  catch (const Exception& e)
  {
    res = new PluginException("Plugin start failed", error_type, e);
  }
  catch (...)
  {
    res = new PluginException("Plugin start failed", error_type);
  }

  if (fwCtx->debug.lazy_activation)
  {
    qDebug() << "activating #" << id << "completed.";
  }

  if (res == 0)
  {
    //10:
    fwCtx->listeners.emitPluginChanged(PluginEvent(PluginEvent::STARTED, this->q_func()));
  }
  else if (operation.fetchAndAddOrdered(0) == ACTIVATING)
  {
    // 8:
    state = Plugin::STOPPING;
    fwCtx->listeners.emitPluginChanged(PluginEvent(PluginEvent::STOPPING, this->q_func()));
    removePluginResources();
    pluginContext->d_func()->invalidate();
    pluginContext.reset();
    state = Plugin::RESOLVED;
    fwCtx->listeners.emitPluginChanged(PluginEvent(PluginEvent::STOPPED, this->q_func()));
  }

  return res;
}


void osgi::core::PluginPrivate::removePluginResources()
{
  // automatic disconnect due to Qt signal slot
  //fwCtx->listeners.removeAllListeners(this);

  QList<ServiceRegistration> srs = fwCtx->services->getRegisteredByPlugin(this);
  QMutableListIterator<ServiceRegistration> i(srs);
  while (i.hasNext())
  {
    try
    {
      i.next().unregister();
    }
    catch (const IllegalStateException& /*ignore*/)
    {
      // Someone has unregistered the service after stop completed.
      // This should not occur, but we don't want get stuck in
      // an illegal state so we catch it.
    }
  }

  QList<ServiceRegistration> s = fwCtx->services->getUsedByPlugin(q_func());
  QListIterator<ServiceRegistration> i2(s);
  while (i2.hasNext())
  {
    i2.next().getReference().d_func()->ungetService(q_func(), false);
  }

}

