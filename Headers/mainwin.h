#ifndef MAINWIN_H
#define MAINWIN_H

#include <QMainWindow>
#include "logwin.h"

//for commit
class LogWin;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWin; }
QT_END_NAMESPACE

class MainWin : public QMainWindow
{
    Q_OBJECT

public:
    LogWin* ptr_MainWin_LogWin;
    MainWin(QWidget *parent = nullptr);
    ~MainWin();

private slots:

private:
    Ui::MainWin *ui;
};


#endif // MAINWIN_H
