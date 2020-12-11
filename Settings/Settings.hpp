#pragma once
#include <QSettings>
#include <QDebug>


class Settings{


    Settings(){
        settings_ = new QSettings("mpa-technology","mpacrm");
        settings_->sync();
        qDebug()<<"Settings:up" << settings_->fileName();
    }
    Settings(const Settings& root) = delete;
    Settings& operator=(const Settings&) = delete;


    QSettings* settings_ = nullptr;


public:

    ~Settings(){
        settings_->sync();
        delete  settings_;
    }

    static Settings& self(){
        static Settings sig;
        return sig;
    }


    void setValue( const QString& key, const QVariant& value){
        settings_->setValue(key,value);
    }

    QVariant value( const QString& key, const QVariant& defaultValue){
        return settings_->value(key,defaultValue);
    }


};


