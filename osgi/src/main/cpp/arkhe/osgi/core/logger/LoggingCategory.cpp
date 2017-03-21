#include <QSettings>
#include <arkhe/osgi/core/logger/LoggingCategory.hpp>


/*! 
 * @brief Add Global logging categories (not class specific) here using LOGGING_CATEGORY
 */
 
Q_LOGGING_CATEGORY(logDebug,    "DEBUG")
Q_LOGGING_CATEGORY(logInfo,     "INFO")
Q_LOGGING_CATEGORY(logWarning,  "WARNING")
Q_LOGGING_CATEGORY(logCritical, "CRITICAL")

// LOGGING_CATEGORY(FirmwareUpgradeLog,        "FirmwareUpgradeLog")
// LOGGING_CATEGORY(FirmwareUpgradeVerboseLog, "FirmwareUpgradeVerboseLog")
// LOGGING_CATEGORY(MissionCommandsLog,        "MissionCommandsLog")
// LOGGING_CATEGORY(MissionItemLog,            "MissionItemLog")
// LOGGING_CATEGORY(ParameterManagerLog,       "ParameterManagerLog")
// LOGGING_CATEGORY(GeotaggingLog,             "GeotaggingLog")


LoggingCategoryRegister* LoggingCategoryRegister::_instance = nullptr;
const char* LoggingCategoryRegister::_filterRulesSettingsGroup = "LoggingFilters";

LoggingCategoryRegister* LoggingCategoryRegister::instance(void)
{
    if (!_instance) 
    {
        _instance = new LoggingCategoryRegister();
        Q_CHECK_PTR(_instance);
    }
    
    return _instance;
}

QStringList LoggingCategoryRegister::registeredCategories(void)
{
    _registeredCategories.sort();
    return _registeredCategories;
}

void LoggingCategoryRegister::registerCategory(const char* category)
{
     _registeredCategories << category; 
}

void LoggingCategoryRegister::setCategoryLoggingOn(const QString& category, bool enable)
{
    QSettings settings;

    settings.beginGroup(_filterRulesSettingsGroup);
    settings.setValue(category, enable);
}

bool LoggingCategoryRegister::categoryLoggingOn(const QString& category)
{
    QSettings settings;

    settings.beginGroup(_filterRulesSettingsGroup);
    return settings.value(category, false).toBool();
}

void LoggingCategoryRegister::setFilterRulesFromSettings(const QString& commandLineLoggingOptions)
{
    if (!commandLineLoggingOptions.isEmpty()) 
    {
        _commandLineLoggingOptions = commandLineLoggingOptions;
    }
    QString filterRules;

    // Turn off bogus ssl warning
    filterRules += "qt.network.ssl.warning=false\n";
    filterRules += "*Log.debug=false\n";

    // Set up filters defined in settings
    foreach (QString category, _registeredCategories) 
    {
        if (categoryLoggingOn(category)) 
        {
            filterRules += category;
            filterRules += ".debug=true\n";
        }
    }

    // Command line rules take precedence, so they go last in the list
    if (!_commandLineLoggingOptions.isEmpty()) 
    {
        QStringList logList = _commandLineLoggingOptions.split(",");

        if (logList[0] == "full") 
        {
            filterRules += "*Log.debug=true\n";
            for(int i=1; i<logList.count(); i++) 
            {
                filterRules += logList[i];
                filterRules += ".debug=false\n";
            }
        } 
        else 
        {
            foreach(const QString &rule, logList) 
            {
                filterRules += rule;
                filterRules += ".debug=true\n";
            }
        }
    }

    qDebug() << "Filter rules" << filterRules;
    QLoggingCategory::setFilterRules(filterRules);
}

// The implementation of the handler
void LoggingCategoryRegister::messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // Open stream file writes
    QTextStream out(m_logFile.data());
    // Write the date of recording
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");
    // By type determine to what level belongs message
    switch (type)
    {
		case QtInfoMsg:     
			out << "INFO "; 
			break;
		case QtDebugMsg:    
			out << "DEBUG ";
			break;
		case QtWarningMsg:  
			out << "WARN "; 
			break;
		case QtCriticalMsg: 
			out << "CRITICAL ";
			break;
		case QtFatalMsg:
			out << "FATAL ";
			break;
    }
    // Write to the output category of the message and the message itself
    out << context.category << ": "
        << msg << endl;
    out.flush();    // Clear the buffered data
}