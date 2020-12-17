/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/

#include <main.hpp>



logFile::logFile(){

    auto fileName = Settings::self().value("log/file","nolcrm.log").toString();
    file = fopen(fileName.toStdString().data(),"a");

    qDebug()<<"log file open";
}

logFile::~logFile(){
    qDebug()<<"log file down";
    fflush(file);
    fclose(file);
}

void MessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg){

    static logFile logf;

    QByteArray localMsg = msg.toLocal8Bit();

    auto data = QDate::currentDate().toString();
    auto time = QTime::currentTime().toString();

    //TODO: reples
    if(ProgramService::buildType()==ProgramService::RELEASE){

        switch (type) {
        case QtDebugMsg:break;
        case QtInfoMsg:
            fprintf(stderr, "%s : %s Info: %s : (%s:%u, %s)\n",data.toStdString().data(),time.toStdString().data(),localMsg.constData(), context.file, context.line, context.function);
            fprintf(logf.file, "%s : %s Info: %s : (%s:%u, %s)\n",data.toStdString().data(),time.toStdString().data(),localMsg.constData(), context.file, context.line, context.function);
            break;
        case QtWarningMsg:
            fprintf(stderr, "%s : %s Warning: %s : (%s:%u, %s)\n",data.toStdString().data(),time.toStdString().data(),localMsg.constData(), context.file, context.line, context.function);
            fprintf(logf.file, "%s : %s Warning: %s : (%s:%u, %s)\n",data.toStdString().data(),time.toStdString().data(),localMsg.constData(), context.file, context.line, context.function);
            break;
        case QtCriticalMsg:
            fprintf(stderr, "%s : %s Critical: %s : (%s:%u, %s)\n",data.toStdString().data(),time.toStdString().data(),localMsg.constData(), context.file, context.line, context.function);
            fprintf(logf.file, "%s : %s Critical: %s : (%s:%u, %s)\n",data.toStdString().data(),time.toStdString().data(),localMsg.constData(), context.file, context.line, context.function);
            break;
        case QtFatalMsg:
            fprintf(stderr, "%s : %s Fatal: %s : (%s:%u, %s)\n",data.toStdString().data(),time.toStdString().data(),localMsg.constData(), context.file, context.line, context.function);
            fprintf(logf.file, "%s : %s Fatal: %s : (%s:%u, %s)\n",data.toStdString().data(),time.toStdString().data(),localMsg.constData(), context.file, context.line, context.function);
            abort();
        }
    }
    else{
        switch (type) {
        case QtDebugMsg:
            fprintf(stderr, "%s : %s Debug: %s : (%s:%u, %s)\n",data.toStdString().data(),time.toStdString().data(),localMsg.constData(), context.file, context.line, context.function);
            fprintf(logf.file, "%s : %s Debug: %s : (%s:%u, %s)\n",data.toStdString().data(),time.toStdString().data(),localMsg.constData(), context.file, context.line, context.function);
            break;
        case QtInfoMsg:
            fprintf(stderr, "%s : %s Info: %s : (%s:%u, %s)\n",data.toStdString().data(),time.toStdString().data(),localMsg.constData(), context.file, context.line, context.function);
            fprintf(logf.file, "%s : %s Info: %s : (%s:%u, %s)\n",data.toStdString().data(),time.toStdString().data(),localMsg.constData(), context.file, context.line, context.function);
            break;
        case QtWarningMsg:
            fprintf(stderr, "%s : %s Warning: %s : (%s:%u, %s)\n",data.toStdString().data(),time.toStdString().data(),localMsg.constData(), context.file, context.line, context.function);
            fprintf(logf.file, "%s : %s Warning: %s : (%s:%u, %s)\n",data.toStdString().data(),time.toStdString().data(),localMsg.constData(), context.file, context.line, context.function);
            break;
        case QtCriticalMsg:
            fprintf(stderr, "%s : %s Critical: %s : (%s:%u, %s)\n",data.toStdString().data(),time.toStdString().data(),localMsg.constData(), context.file, context.line, context.function);
            fprintf(logf.file, "%s : %s Critical: %s : (%s:%u, %s)\n",data.toStdString().data(),time.toStdString().data(),localMsg.constData(), context.file, context.line, context.function);
            break;
        case QtFatalMsg:
            fprintf(stderr, "%s : %s Fatal: %s : (%s:%u, %s)\n",data.toStdString().data(),time.toStdString().data(),localMsg.constData(), context.file, context.line, context.function);
            fprintf(logf.file, "%s : %s Fatal: %s : (%s:%u, %s)\n",data.toStdString().data(),time.toStdString().data(),localMsg.constData(), context.file, context.line, context.function);
            abort();
        }

    }

}

int main(int argc, char *argv[]){

    qInstallMessageHandler(MessageOutput);

    QApplication app(argc, argv);

    qDebug() << "buildType: " << ProgramService::buildTypeString();
    QWidget* startWindow;

    if(Settings::mainSettingsLoad()){

        if(!GlobalService::waekup())
            return EXIT_FAILURE;

        startWindow = new MainWindow();
    }else
        startWindow = new LoginWidget();


    startWindow->show();

    UpdateService::self().emitGlobalUpdate();
    return app.exec();
}
