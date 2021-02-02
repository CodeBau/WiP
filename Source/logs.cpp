#include "../Headers/logs.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QStringView>


void mylog(QString log_text)
{
    QString current_date= QDateTime::currentDateTime().toString("yyyy.MM.dd HH:mm:ss");
    QFile logFile("log.wip");
    if(logFile.open(QIODevice::Append|QIODevice::Text)){
        QTextStream outLog(&logFile);
        outLog <<current_date <<" "<< log_text<<"\n";
    }
    else
    {
        //TODO message: problem with files
    }
    logFile.close();
}
