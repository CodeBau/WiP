#include "../Headers/logwin.h"
#include "../Headers/regwin.h"
#include "../Headers/pswdrmdwin.h"
#include "../Headers/startwin.h"
#include "../Headers/mainwin.h"
#include "../Headers/logs.h"
#include "../Headers/config.h"
#include "../Headers/api_process.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    //TODO opcje->ustawienia->opcje logoowania
    //TODO opcje->okno logowania
    //TODO 1 zrobic polaczenie startwin->mainwin
    //TODO mode trzeba sprawdzac na biezac oz bazydanych, trzeba zrovic voida ktory bedzie sprawdzac
    //TODO dodać opcję gość bez mysql a z pomocą sqllite na dysku.
    //TODO dodać date_of_create, i date_of_edit
    //TODO 3 refactoring code with nested if statments
    //TODO 5 pelne nazwy zmiennych
    //TODO plki config w folderze

    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("://Media/ico/wipicon.ico"));


    StartWin mynew;
    mynew.show();

    //Api_Process my_api_process;
    //my_api_process.start();
    //my_api_process.init();

    qDebug("EXIT");
    return a.exec();
}
