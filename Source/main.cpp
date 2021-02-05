#include "../Headers/logwin.h"
#include "../Headers/regwin.h"
#include "../Headers/pswdrmdwin.h"
#include "../Headers/mainwin.h"
#include "../Headers/logs.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("://Media/ico/wipicon.ico"));

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
