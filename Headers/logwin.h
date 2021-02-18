#ifndef LOGWIN_H
#define LOGWIN_H

#include <QMainWindow>
#include <QTimer>
#include "regwin.h"
#include "pswdrmdwin.h"
#include "mainwin.h"
#include "window_init.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LogWin; }
QT_END_NAMESPACE

class LogWin : public QMainWindow
{
    Q_OBJECT

public:
    LogWin(QWidget *parent = nullptr);
    ~LogWin();
    void log_data_mode(std::vector<QString> log_data_vector);
    void get_pointers(RegWin* LogWin_RegWin, PswdRmdWin* LogWin_PswdRmdWin);

private slots:
    void on_LogWin_Button_log_clicked();
    void on_LogWin_Button_reg_clicked();
    void on_LogWin_Button_pswdrmd_clicked();
    void on_LogWin_CheckBox_autolog_toggled(bool checked);
    void set_redallert_to_null();

    void on_set_clicked();

    void on_get_clicked();

    void on_get_2_clicked();

private:
    RegWin* ptr_LogWin_RegWin;
    PswdRmdWin* ptr_LogWin_PswdRmdWin;
    MainWin* ptr_LogWin_MainWin;
    QTimer *timer_redallert;
    Ui::LogWin *ui;
};
#endif // LOGWIN_H
