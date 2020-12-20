/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/

#include <main.hpp>








int main(int argc, char *argv[]){

    App app(argc,argv);


    return app.run();
}

void App::MessageOutput_(QtMsgType type, const QMessageLogContext &context, const QString &msg){

    QByteArray localMsg = msg.toLocal8Bit();

    auto data = QDate::currentDate().toString();
    auto time = QTime::currentTime().toString();

    switch (type) {
    case QtDebugMsg:

        if(ProgramService::buildType() != ProgramService::RELEASE){
            fprintf(stderr, "%s : %s Debug: %s : (%s:%u, %s)\n",data.toStdString().data(),time.toStdString().data(),localMsg.constData(), context.file, context.line, context.function);
        }

        break;
    case QtInfoMsg:
        fprintf(stderr, "%s : %s Info: %s : (%s:%u, %s)\n",data.toStdString().data(),time.toStdString().data(),localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtWarningMsg:
        fprintf(stderr, "%s : %s Warning: %s : (%s:%u, %s)\n",data.toStdString().data(),time.toStdString().data(),localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "%s : %s Critical: %s : (%s:%u, %s)\n",data.toStdString().data(),time.toStdString().data(),localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "%s : %s Fatal: %s : (%s:%u, %s)\n",data.toStdString().data(),time.toStdString().data(),localMsg.constData(), context.file, context.line, context.function);
        abort();
    }





}

App::App(int argc, char **argv){

    qInstallMessageHandler(MessageOutput_);

    qDebug() << "buildType: " << ProgramService::buildTypeString();

    qApplication_ = new QApplication{argc,argv};


    QWidget* startWindow;

    if(Settings::mainSettingsLoad()){

        if(!GlobalService::waekup())
            throw std::runtime_error("error weakup");

        startWindow = new MainWindow();
    }else
        startWindow = new LoginWidget();


    startWindow->show();

    UpdateService::self().emitGlobalUpdate();


}

App::~App(){

}

int App::run(){
    return qApplication_->exec();
}
