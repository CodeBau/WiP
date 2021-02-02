#include "logwin.h"
#include "regwin.h"
#include "pswdrmdwin.h"
#include "mainwin.h"
#include "logs.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    mylog("App.Start");

    LogWin mylogwin;
    RegWin myregwin;
    PswdRmdWin mypswdrmdwin;
    QString myqstring;
    //MainWin mymainwin;

    MainWin mymainwin;

    mylogwin.makereferances(myregwin,mypswdrmdwin);
    myregwin.makereferances(mylogwin,mypswdrmdwin);
    mypswdrmdwin.makereferances(mylogwin,myregwin);

    mylogwin.show();
    mymainwin.show();

   // myregwin.show();
   // mypswdrmdwin.show();

    return a.exec();
}
