/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/



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
    self().settings_->setValue(key,value);
}

QVariant Settings::value(const QString &key, const QVariant &defaultValue){
    return self().settings_->value(key,defaultValue);
}
