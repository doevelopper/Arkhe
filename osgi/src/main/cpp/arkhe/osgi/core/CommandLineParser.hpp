#ifndef ARKHE_OSGI_COMMANDLINEPARSER_HPP
#define ARKHE_OSGI_COMMANDLINEPARSER_HPP

#include <QDebug>
#include <QSettings>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QPointer>

#include <arkhe/osgi/osgi.hpp>

/*!
 * @brief .
 */
namespace osgi
{
    class CommandLineParserArgumentDescription
    {
    public:
        CommandLineParserArgumentDescription( const QString& longArg,
                                             const QString& longArgPrefix,
                                            const QString& shortArg,
                                            const QString& shortArgPrefix,
                                            QVariant::Type type,
                                            const QString& argHelp,
                                            const QVariant& defaultValue,
                                            bool ignoreRest,
                                            bool deprecated);

        virtual ~CommandLineParserArgumentDescription();

        bool addParameter(const QString& value);

        QString helpText(int fieldWidth, const char charPad, const QString& settingsValue = "");

        QString LongArg;
        QString LongArgPrefix;
        QString ShortArg;
        QString ShortArgPrefix;
        QString ArgHelp;
        bool    IgnoreRest;
        int     NumberOfParametersToProcess;
        QString RegularExpression;
        QString ExactMatchFailedMessage;
        bool    Deprecated;

        QVariant       DefaultValue;
        QVariant       Value;
        QVariant::Type ValueType;
    };

	class ARKHE_CORE_EXPORT CommandLineParser : public QObject
	{
        Q_OBJECT
        Q_PROPERTY(QString errorString READ errorString)
        Q_PROPERTY(QStringList unparsedArguments READ unparsedArguments)
        Q_PROPERTY(bool settingsEnabled READ settingsEnabled)
	public:

        using Superclass = QObject ;

        CommandLineParser(QObject* newParent = 0);
        CommandLineParser(QSettings* settings, QObject* newParent = 0);
        virtual ~CommandLineParser();
        QHash<QString, QVariant> parseArguments(const QStringList &arguments, bool* ok = 0);
        QHash<QString, QVariant> parseArguments(int argc, char** argv, bool* ok = 0);
        QString errorString() const;
        const QStringList& unparsedArguments() const;
        
        Q_INVOKABLE bool argumentAdded(const QString& argument) const;
        Q_INVOKABLE bool argumentParsed(const QString& argument) const;
        void addArgument(const QString& longarg,
                         const QString& shortarg,
                         QVariant::Type type,
                         const QString& argHelp = QString(),
                         const QVariant& defaultValue = QVariant(),
                         bool ignoreRest = false,
                         bool deprecated = false);

        void addDeprecatedArgument(const QString& longarg,
                                   const QString& shortarg,
                                   const QString& argHelp);
        
        bool setExactMatchRegularExpression(const QString& argument,
                                            const QString& expression,
                                            const QString& exactMatchFailedMessage);
        int fieldWidth() const;
        QString helpText(const char charPad = ' ') const;
        void setArgumentPrefix(const QString& longPrefix, const QString& shortPrefix);
        void beginGroup(const QString& description);
        void endGroup();
        void enableSettings(const QString& disableLongArg = "",
                            const QString& disableShortArg = "");
        void mergeSettings(bool merge);
        bool settingsEnabled() const;
        void setStrictModeEnabled(bool strictMode);
	protected:

	private:
        class Internal
        {
        public:
            Internal(QSettings* settings)
            : Debug(false)
            , FieldWidth(0)
            , UseQSettings(false)
            , Settings(settings)
            , MergeSettings(true)
            , StrictMode(false)
            {
            
            }
        
            virtual ~Internal()
            {
                qDeleteAll(ArgumentDescriptionList);
            }
          
            CommandLineParserArgumentDescription* argumentDescription(const QString& argument);
          
          QList<CommandLineParserArgumentDescription*>                 ArgumentDescriptionList;
          QHash<QString, CommandLineParserArgumentDescription*>        ArgNameToArgumentDescriptionMap;
          QMap<QString, QList<CommandLineParserArgumentDescription*> > GroupToArgumentDescriptionListMap;
          
          QStringList UnparsedArguments; 
          QStringList ProcessedArguments;
          QString     ErrorString;
          bool        Debug;
          int         FieldWidth;
          QString     LongPrefix;
          QString     ShortPrefix;
          QString     CurrentGroup;
          bool        UseQSettings;
          QPointer<QSettings> Settings;
          QString     DisableQSettingsLongArg;
          QString     DisableQSettingsShortArg;
          bool        MergeSettings;
          bool        StrictMode;
        };
        
        Internal * m_internal;
	};
		
}
#endif
