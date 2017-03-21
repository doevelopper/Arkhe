#include <arkhe/osgi/core/CommandLineParser.hpp>

#include <stdexcept>
#include <QHash>
#include <QStringList>
#include <QTextStream>
#include <QDebug>
#include <QSettings>
#include <QPointer>

osgi::CommandLineParserArgumentDescription::CommandLineParserArgumentDescription(const QString& longArg,
                                             const QString& longArgPrefix,
                                            const QString& shortArg,
                                            const QString& shortArgPrefix,
                                            QVariant::Type type,
                                            const QString& argHelp,
                                            const QVariant& defaultValue,
                                            bool ignoreRest,
                                            bool deprecated)
: LongArg(longArg)
, LongArgPrefix(longArgPrefix)
, ShortArg(shortArg)
, ShortArgPrefix(shortArgPrefix)
, ArgHelp(argHelp)
, IgnoreRest(ignoreRest)
, NumberOfParametersToProcess(0)
, Deprecated(deprecated)
, DefaultValue(defaultValue)
, Value(type)
, ValueType(type)
{
    if (defaultValue.isValid())
    {
        Value = defaultValue;
    }

    switch (type)
    {
        case QVariant::String:
        {
            NumberOfParametersToProcess = 1;
            RegularExpression = ".*";
        }
            break;
        case QVariant::Bool:
        {
            NumberOfParametersToProcess = 0;
            RegularExpression = "";
        }
            break;
        case QVariant::StringList:
        {
            NumberOfParametersToProcess = -1;
            RegularExpression = ".*";
        }
            break;
        case QVariant::Int:
        {
            NumberOfParametersToProcess = 1;
            RegularExpression = "-?[0-9]+";
            ExactMatchFailedMessage = "A negative or positive integer is expected.";
        }
            break;
        case QVariant::Double:
        {
            NumberOfParametersToProcess = 1;
            RegularExpression = "-?[0-9]*\\.?[0-9]+";
            ExactMatchFailedMessage = "A double is expected.";
        }
            break;
        default:
            ExactMatchFailedMessage = QString("Type %1 not supported.").arg(static_cast<int>(type));
    }    
}


osgi::CommandLineParserArgumentDescription::~CommandLineParserArgumentDescription()
{
            
}

bool osgi::CommandLineParserArgumentDescription::addParameter(const QString& value)
{
    if (!RegularExpression.isEmpty())
    {
        // Validate value
        QRegExp regexp(this->RegularExpression);
        if (!regexp.exactMatch(value))
        {
            return (false);
        }
    }

    switch (Value.type())
    {
        case QVariant::String:
        {
            Value.setValue(value);
        }
            break;
        case QVariant::Bool:
        {
            Value.setValue(!QString::compare(value, "true", Qt::CaseInsensitive));
        }
            break;
        case QVariant::StringList:
        {
            if (Value.isNull())
            {
                QStringList list;
                list << value;
                Value.setValue(list);
            }
            else
            {
                QStringList list = Value.toStringList();
                list << value;
                Value.setValue(list);
            }
        }
            break;
        case QVariant::Int:
        {
            Value.setValue(value.toInt());
        }
            break;
        case QVariant::Double:
        {
            Value.setValue(value.toDouble());
        }
            break;
        default:
            return (false);
    }

  return (true);
}

QString osgi::CommandLineParserArgumentDescription::helpText(int fieldWidth
                                                             , const char charPad
                                                             , const QString& settingsValue)
{
    QString text;
    QTextStream stream(&text);
    stream.setFieldAlignment(QTextStream::AlignLeft);
    stream.setPadChar(charPad);

    QString shortAndLongArg;
    if (!this->ShortArg.isEmpty())
    {
        shortAndLongArg += QString("  %1%2").arg(this->ShortArgPrefix).arg(this->ShortArg);
    }

    if (!this->LongArg.isEmpty())
    {
        if (this->ShortArg.isEmpty())
        {
            shortAndLongArg.append("  ");
        }
        else
        {
            shortAndLongArg.append(", ");
        }

        shortAndLongArg += QString("%1%2").arg(this->LongArgPrefix).arg(this->LongArg);
    }

    if(!this->ArgHelp.isEmpty())
    {
        stream.setFieldWidth(fieldWidth);
    }

    stream  << shortAndLongArg;
    stream.setFieldWidth(0);
    stream << this->ArgHelp;
    if (!settingsValue.isNull())
    {
        stream << " (default: " << settingsValue << ")";
    }
    else if (!this->DefaultValue.isNull())
    {
        stream << " (default: " << this->DefaultValue.toString() << ")";
    }
    
    stream << "\n";
    return (text);
}

osgi::CommandLineParserArgumentDescription*
  osgi::CommandLineParser::Internal::argumentDescription(const QString& argument)
{
    QString unprefixedArg = argument;
    if (!LongPrefix.isEmpty() && argument.startsWith(LongPrefix))
    {
        // Case when (ShortPrefix + UnPrefixedArgument) matches LongPrefix
        if (argument == LongPrefix && !ShortPrefix.isEmpty() && argument.startsWith(ShortPrefix))
        {
            unprefixedArg = argument.mid(ShortPrefix.length());
        }
        else
        {
            unprefixedArg = argument.mid(LongPrefix.length());
        }
    }
    else if (!ShortPrefix.isEmpty() && argument.startsWith(ShortPrefix))
    {
        unprefixedArg = argument.mid(ShortPrefix.length());
    }
    else if (!LongPrefix.isEmpty() && !ShortPrefix.isEmpty())
    {
        return (0);
    }

    if (this->ArgNameToArgumentDescriptionMap.contains(unprefixedArg))
    {
        return (this->ArgNameToArgumentDescriptionMap[unprefixedArg]);
    }

    return (0);
}

osgi::CommandLineParser::CommandLineParser(QObject* newParent)
: Superclass(newParent)
{
    this->m_internal = new Internal(0);
}

osgi::CommandLineParser::CommandLineParser(QSettings* settings, QObject* newParent)
:  Superclass(newParent)
{
    this->m_internal = new Internal(settings);
}

osgi::CommandLineParser::~CommandLineParser()
{
  delete this->m_internal;
}

QHash<QString, QVariant> osgi::CommandLineParser::parseArguments(const QStringList& arguments, bool* ok)
{

    this->m_internal->UnparsedArguments.clear();
    this->m_internal->ProcessedArguments.clear();
    this->m_internal->ErrorString.clear();

    foreach (CommandLineParserArgumentDescription* desc, this->m_internal->ArgumentDescriptionList)
    {
        desc->Value = QVariant(desc->ValueType);
        if (desc->DefaultValue.isValid())
        {
            desc->Value = desc->DefaultValue;
        }
    }

    bool error = false;
    bool ignoreRest = false;
    bool useSettings = this->m_internal->UseQSettings;
    CommandLineParserArgumentDescription * currentArgDesc = 0;
    QList<CommandLineParserArgumentDescription*> parsedArgDescriptions;
    for(int i = 1; i < arguments.size(); ++i)
    {
        QString argument = arguments.at(i);
        if (this->m_internal->Debug)
        {
            qDebug() << "Processing" << argument;
        }

        // should argument be ignored ?
        if (ignoreRest)
        {
            if (this->m_internal->Debug)
            {
                qDebug() << "  Skipping: IgnoreRest flag was been set";
            }
            this->m_internal->UnparsedArguments << argument;
            continue;
        }

        // Skip if the argument does not start with the defined prefix
        if (!(argument.startsWith(this->m_internal->LongPrefix)
        || argument.startsWith(this->m_internal->ShortPrefix)))
        {
            if (this->m_internal->StrictMode)
            {
                this->m_internal->ErrorString = QString("Unknown argument %1").arg(argument);
                error = true;
                break;
            }
            if (this->m_internal->Debug)
            {
                qDebug() << "  Skipping: It does not start with the defined prefix";
            }
            this->m_internal->UnparsedArguments << argument;
            continue;
        }

            // Skip if argument has already been parsed ...
        if (this->m_internal->ProcessedArguments.contains(argument))
        {
            if (this->m_internal->StrictMode)
            {
                this->m_internal->ErrorString = QString("Argument %1 already processed !").arg(argument);
                error = true;
                break;
            }

            if (this->m_internal->Debug)
            {
                qDebug() << "  Skipping: Already processed !";
            }
            continue;
        }

        // Retrieve corresponding argument description
        currentArgDesc = this->m_internal->argumentDescription(argument);

        // Is there a corresponding argument description ?
        if (currentArgDesc)
        {
        // If the argument is deprecated, print the help text but continue processing
            if (currentArgDesc->Deprecated)
            {
                qWarning().nospace() << "Deprecated argument " << argument << ": "  << currentArgDesc->ArgHelp;
            }
            else
            {
                parsedArgDescriptions.push_back(currentArgDesc);
            }

        // Is the argument the special "disable QSettings" argument?
            if ((!currentArgDesc->LongArg.isEmpty()
             && currentArgDesc->LongArg == this->m_internal->DisableQSettingsLongArg)
            || (!currentArgDesc->ShortArg.isEmpty()
            && currentArgDesc->ShortArg == this->m_internal->DisableQSettingsShortArg))
            {
                useSettings = false;
            }

            this->m_internal->ProcessedArguments << currentArgDesc->ShortArg << currentArgDesc->LongArg;
            int numberOfParametersToProcess = currentArgDesc->NumberOfParametersToProcess;
            ignoreRest = currentArgDesc->IgnoreRest;
            if (this->m_internal->Debug && ignoreRest)
            {
                qDebug() << "  IgnoreRest flag is True";
            }

      // Is the number of parameters associated with the argument being processed known ?
            if (numberOfParametersToProcess == 0)
            {
                currentArgDesc->addParameter("true");
            }
            else if (numberOfParametersToProcess > 0)
            {
                QString missingParameterError = "Argument %1 has %2 value(s) associated whereas exacly %3 are expected.";
                for(int j=1; j <= numberOfParametersToProcess; ++j)
                {
                    if (i + j >= arguments.size())
                    {
                        this->m_internal->ErrorString = missingParameterError.arg(argument).arg(j-1).arg(numberOfParametersToProcess);
                        if (this->m_internal->Debug)
                        {
                            qDebug() << this->m_internal->ErrorString;
                        }
                        if (ok)
                        {
                            *ok = false;
                        }
                        return QHash<QString, QVariant>();
                    }
                    QString parameter = arguments.at(i + j);
                    if (this->m_internal->Debug)
                    {
                        qDebug() << "  Processing parameter" << j << ", value:" << parameter;
                    }
                    if (this->argumentAdded(parameter))
                    {
                        this->m_internal->ErrorString = missingParameterError.arg(argument).arg(j-1).arg(numberOfParametersToProcess);
                        if (this->m_internal->Debug)
                        {
                            qDebug() << this->m_internal->ErrorString;
                            
                        }
                        
                        if (ok)
                        {
                            *ok = false;
                        }
                        return QHash<QString, QVariant>();
                    }
                    if (!currentArgDesc->addParameter(parameter))
                    {
                        this->m_internal->ErrorString = QString("Value(s) associated with argument %1 are incorrect. %2").arg(argument).arg(currentArgDesc->ExactMatchFailedMessage);

                        if (this->m_internal->Debug)
                        {
                            qDebug() << this->m_internal->ErrorString;
                        }
                        if (ok)
                        {
                            *ok = false;
                        }
                        return QHash<QString, QVariant>();
                    }
                }
                // Update main loop increment
                i = i + numberOfParametersToProcess;
            }
            else if (numberOfParametersToProcess == -1)
            {
                if (this->m_internal->Debug)
                {
                    qDebug() << "  Proccessing StringList ...";
                }
                int j = 1;

                while(j + i < arguments.size())
                {
                    if (this->argumentAdded(arguments.at(j + i)))
                    {
                        if (this->m_internal->Debug)
                        {
                            qDebug() << "  No more parameter for" << argument;
                        }
                        break;
                    }
                    QString parameter = arguments.at(j + i);
                    if (this->m_internal->Debug)
                    {
                        qDebug() << "  Processing parameter" << j << ", value:" << parameter;
                    }

                    if (!currentArgDesc->addParameter(parameter))
                    {
                        this->m_internal->ErrorString = QString("Value(s) associated with argument %1 are incorrect. %2").arg(argument).arg(currentArgDesc->ExactMatchFailedMessage);
                        if (this->m_internal->Debug)
                        {
                            qDebug() << this->m_internal->ErrorString;
                        }
                        if (ok)
                        {
                            *ok = false;
                        }
                        return QHash<QString, QVariant>();
                    }
                    j++;
                }
                // Update main loop increment
                i = i + j;
            }
        }
        else
        {
            if (this->m_internal->StrictMode)
            {
                this->m_internal->ErrorString = QString("Unknown argument %1").arg(argument);
                error = true;
                break;
            }
            if (this->m_internal->Debug)
            {
                qDebug() << "  Skipping: Unknown argument";
            }
            this->m_internal->UnparsedArguments << argument;
        }
    }

    if (ok)
    {
        *ok = !error;
    }

    QSettings* settings = 0;
    if (this->m_internal->UseQSettings && useSettings)
    {
        if (this->m_internal->Settings)
        {
            settings = this->m_internal->Settings;
        }
        else
        {
            // Use a default constructed QSettings instance
            settings = new QSettings();
        }
    }

    QHash<QString, QVariant> parsedArguments;
    QListIterator<CommandLineParserArgumentDescription*> it(this->m_internal->ArgumentDescriptionList);

    while (it.hasNext())
    {
        QString key;
        CommandLineParserArgumentDescription* desc = it.next();
        if (!desc->LongArg.isEmpty())
        {
            key = desc->LongArg;
        }
        else
        {
            key = desc->ShortArg;
        }

        if (parsedArgDescriptions.contains(desc))
        {
            // The argument was supplied on the command line, so use the given value

            if (this->m_internal->MergeSettings && settings)
            {
                // Merge with QSettings
                QVariant settingsVal = settings->value(key);

                if (desc->ValueType == QVariant::StringList && settingsVal.canConvert(QVariant::StringList))
                {
                    QStringList stringList = desc->Value.toStringList();
                    stringList.append(settingsVal.toStringList());
                    parsedArguments.insert(key, stringList);
                }
                else
                {
                    // do a normal insert
                    parsedArguments.insert(key, desc->Value);
                }
            }
            else
            {
                // No merging, just insert all user values
                parsedArguments.insert(key, desc->Value);
            }
        }
        else
        {
            if (settings)
            {
                // If there is a valid QSettings entry for the argument, use the value
                QVariant settingsVal = settings->value(key, desc->Value);
                if (!settingsVal.isNull())
                {
                    parsedArguments.insert(key, settingsVal);
                }
            }
            else
            {
                // Just insert the arguments with valid default values
                if (!desc->Value.isNull())
                {
                    parsedArguments.insert(key, desc->Value);
                }
            }
        }
    }

    // If we created a default QSettings instance, delete it
    if (settings && !this->m_internal->Settings)
    {
        delete settings;
    }

    return parsedArguments;
}

// -------------------------------------------------------------------------
QHash<QString, QVariant> osgi::CommandLineParser::parseArguments(int argc, char** argv, bool* ok)
{
  QStringList arguments;

  // Create a QStringList of arguments
    for(int i = 0; i < argc; ++i)
    {
        arguments << argv[i];
    }

    return this->parseArguments(arguments, ok);
}

QString osgi::CommandLineParser::errorString() const
{
    return this->m_internal->ErrorString;
}

const QStringList& osgi::CommandLineParser::unparsedArguments() const
{
    return (this->m_internal->UnparsedArguments);
}

void osgi::CommandLineParser::addArgument(const QString& longarg, const QString& shortarg,
                                       QVariant::Type type, const QString& argHelp,
                                       const QVariant& defaultValue, bool ignoreRest,
                                       bool deprecated)
{
    Q_ASSERT_X(!(longarg.isEmpty() && shortarg.isEmpty()), "addArgument", "both long and short argument names are empty");
    if (longarg.isEmpty() && shortarg.isEmpty())
    {
        return;
    }
    
    Q_ASSERT_X(!defaultValue.isValid() || defaultValue.type() == type, "addArgument", "defaultValue type does not match");
    if (defaultValue.isValid() && defaultValue.type() != type)
    {
        throw std::logic_error("The QVariant type of defaultValue does not match the specified type");
    }

  /* Make sure it's not already added */
    bool added = this->m_internal->ArgNameToArgumentDescriptionMap.contains(longarg);
    Q_ASSERT_X(!added, "addArgument", "long argument already added");
    if (added)
    {
        return;
    }

    added = this->m_internal->ArgNameToArgumentDescriptionMap.contains(shortarg);

    Q_ASSERT_X(!added, "addArgument", "short argument already added");
    if (added)
    {
        return;
    }

    CommandLineParserArgumentDescription* argDesc =
    new CommandLineParserArgumentDescription(longarg, this->m_internal->LongPrefix,
                                             shortarg, this->m_internal->ShortPrefix, type,
                                             argHelp, defaultValue, ignoreRest, deprecated);

    int argWidth = 0;

    if (!longarg.isEmpty())
    {
        this->m_internal->ArgNameToArgumentDescriptionMap[longarg] = argDesc;
        argWidth += longarg.length() + this->m_internal->LongPrefix.length();
    }
    
    if (!shortarg.isEmpty())
    {
        this->m_internal->ArgNameToArgumentDescriptionMap[shortarg] = argDesc;
        argWidth += shortarg.length() + this->m_internal->ShortPrefix.length() + 2;
    }

    argWidth += 5;

    if (argWidth > this->m_internal->FieldWidth)
    {
        this->m_internal->FieldWidth = argWidth;
    }

    this->m_internal->ArgumentDescriptionList << argDesc;
    this->m_internal->GroupToArgumentDescriptionListMap[this->m_internal->CurrentGroup] << argDesc;
}

void osgi::CommandLineParser::addDeprecatedArgument(
    const QString& longarg, const QString& shortarg, const QString& argHelp)
{
  addArgument(longarg, shortarg, QVariant::StringList, argHelp, QVariant(), false, true);
}


bool osgi::CommandLineParser::setExactMatchRegularExpression(
    const QString& argument,
    const QString& expression,
    const QString& exactMatchFailedMessage)
{
    CommandLineParserArgumentDescription * argDesc = this->m_internal->argumentDescription(argument);

    if (!argDesc)
    {
        return (false);
    }

    if (argDesc->Value.type() == QVariant::Bool)
    {
        return (false);
    }
    argDesc->RegularExpression = expression;
    argDesc->ExactMatchFailedMessage = exactMatchFailedMessage;
    return (true);
}

int osgi::CommandLineParser::fieldWidth() const
{
    return (this->m_internal->FieldWidth);
}

void osgi::CommandLineParser::beginGroup(const QString& description)
{
    this->m_internal->CurrentGroup = description;
}

void osgi::CommandLineParser::endGroup()
{
    this->m_internal->CurrentGroup.clear();
}

void osgi::CommandLineParser::enableSettings(const QString& disableLongArg, const QString& disableShortArg)
{
  this->m_internal->UseQSettings = true;
  this->m_internal->DisableQSettingsLongArg = disableLongArg;
  this->m_internal->DisableQSettingsShortArg = disableShortArg;
}

void osgi::CommandLineParser::mergeSettings(bool merge)
{
    this->m_internal->MergeSettings = merge;
}

bool osgi::CommandLineParser::settingsEnabled() const
{
    return (this->m_internal->UseQSettings);
}

QString osgi::CommandLineParser::helpText(const char charPad) const
{
    QString text;
    QTextStream stream(&text);

    QList<CommandLineParserArgumentDescription*> deprecatedArgs;

  // Loop over grouped argument descriptions
    QMapIterator<QString, QList<CommandLineParserArgumentDescription*> > it(this->m_internal->GroupToArgumentDescriptionListMap);

    while(it.hasNext())
    {
        it.next();
        if (!it.key().isEmpty())
        {
            stream << "\n" << it.key() << "\n";
        }
        foreach(CommandLineParserArgumentDescription* argDesc, it.value())
        {
            if (argDesc->Deprecated)
            {
                deprecatedArgs << argDesc;
            }
            else
            {
             // Extract associated value from settings if any
                QString settingsValue;
                if (this->m_internal->Settings)
                {
                    QString key;
                    if (!argDesc->LongArg.isEmpty())
                    {
                        key = argDesc->LongArg;
                    }
                    else
                    {
                    key = argDesc->ShortArg;
                    }
                    settingsValue = this->m_internal->Settings->value(key).toString();
                }
                stream << argDesc->helpText(this->m_internal->FieldWidth, charPad, settingsValue);
            }
        }
    }

    if (!deprecatedArgs.empty())
    {
        stream << "\nDeprecated arguments:\n";
        foreach(CommandLineParserArgumentDescription* argDesc, deprecatedArgs)
        {
            stream << argDesc->helpText(this->m_internal->FieldWidth, charPad);
        }
    }

    return (text);
}

bool osgi::CommandLineParser::argumentAdded(const QString& argument) const
{
  return (this->m_internal->ArgNameToArgumentDescriptionMap.contains(argument));
}

bool osgi::CommandLineParser::argumentParsed(const QString& argument) const
{
    return (this->m_internal->ProcessedArguments.contains(argument));
}

void osgi::CommandLineParser::setArgumentPrefix(const QString& longPrefix, const QString& shortPrefix)
{
    this->m_internal->LongPrefix = longPrefix;
    this->m_internal->ShortPrefix = shortPrefix;
}

void osgi::CommandLineParser::setStrictModeEnabled(bool strictMode)
{
    this->m_internal->StrictMode = strictMode;
}

