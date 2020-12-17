#include "Settings.hpp"


Settings::Settings(){
    settings_ = new QSettings("mpa-technology","nolcrm");
    settings_->sync();
    qDebug()<<"Settings:up" << settings_->fileName();
}

Settings::~Settings(){
    settings_->sync();
    delete  settings_;
}

Settings &Settings::self(){
    static Settings sig;
    return sig;
}

void Settings::setValue(const QString &key, const QVariant &value){
    settings_->setValue(key,value);
}

QVariant Settings::value(const QString &key, const QVariant &defaultValue){
    return settings_->value(key,defaultValue);
}
