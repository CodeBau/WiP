#ifndef MAINWIN_H
#define MAINWIN_H

#include <QMainWindow>
#include <QDebug>
#include "logwin.h"
#include "loginphase.h"
#include "accont_data_change.h"
#include "window_init.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWin; }
QT_END_NAMESPACE

class MainWin : public QMainWindow
{
    Q_OBJECT

public:
    QString api_mode;
    int api_user_id;

    MainWin(QWidget *parent = nullptr, int user_id=0, QString mode="", QString name_to_title="");
    ~MainWin();
    void setmenu();

private slots:
    void on_pushButton_clicked();
    void on_action_logwin_triggered();
    void on_action_accont_data_change_triggered();

private:
    LoginPhase * ptr_mainwin_login_phase;
    LogWin* MainWin_LogWin;
    Accont_Data_Change* ptr_mainwin_accont_data_change;
    Ui::MainWin *ui;
};


#endif // MAINWIN_H
