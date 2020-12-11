#include <QApplication>
#include <QMessageBox>
#include <QSettings>
#include <QtGlobal>
#include <QFile>

#include "DataBase/Service.hpp"
#include "MainWindow/MainWindow.hpp"
#include "DataBase/DataBase.hpp"
#include "DataBase/TableStorage.hpp"
#include "Settings/Settings.hpp"

struct logFile{

    FILE* file = nullptr;

    logFile(){

        auto fileName = Settings::self().value("log/file","mpa.log").toString();
        file  = fopen(fileName.toStdString().data(),"w+");
    }

    ~logFile(){
        fclose(file);
    }

};


void MessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg){

    static logFile logf;

    QByteArray localMsg = msg.toLocal8Bit();

    auto data = QDate::currentDate().toString();
    auto time = QTime::currentTime().toString();

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






int main(int argc, char *argv[]){

    qInstallMessageHandler(MessageOutput);

    QApplication mpacrmApp(argc, argv);

    try {
        GlobalService::self().initTableBase();
    } catch (const std::exception& exp) {
        qCritical()<<exp.what();
        return EXIT_FAILURE;
    }


    MainWindow w;
    w.show();

    return mpacrmApp.exec();
}
