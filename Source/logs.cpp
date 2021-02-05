#include "../Headers/logs.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QStringView>
#include <QMessageBox>
#include <QMessageBox>


void mylog(QString log_text)
{
    QString current_date= QDateTime::currentDateTime().toString("yyyy.MM.dd HH:mm:ss");
    QFile logFile("log.wip");
    if(logFile.open(QIODevice::Append|QIODevice::Text))
    {
        QTextStream outLog(&logFile);
        outLog <<current_date <<" "<< log_text<<"\n";
    }
    else
    {
        QMessageBox msgWarning;
            msgWarning.setText("Program, nie może zapisać odpowiednich plików w swoim środowisku.\nSprawdź możliwość zapisu danych w folderze program.");
            msgWarning.setIcon(QMessageBox::Warning);
            msgWarning.setWindowTitle("Uwaga");
            msgWarning.exec();
    }
    logFile.close();
}
