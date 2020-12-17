#ifndef NOLCRM_SETTINGS_HPP
#define NOLCRM_SETTINGS_HPP

#include <QSettings>
#include <QDebug>


class Settings{


    Settings();
    Settings(const Settings& root) = delete;
    Settings& operator=(const Settings&) = delete;


    QSettings* settings_ = nullptr;


public:

    ~Settings();

    static Settings& self();


    void setValue( const QString& key, const QVariant& value);

    QVariant value( const QString& key, const QVariant& defaultValue);


    static bool mainSettingsLoad(){
        QString dbName = Settings::self().value("database/name","@NULL").toString();
        return dbName != "@NULL";
    }

};

#endif
