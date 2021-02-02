#ifndef LOGWIN_H
#define LOGWIN_H

#include <QMainWindow>
#include <QTimer>
#include "regwin.h"
#include "pswdrmdwin.h"

class RegWin;
class PswdRmdWin;

QT_BEGIN_NAMESPACE
namespace Ui { class LogWin; }
QT_END_NAMESPACE

class LogWin : public QMainWindow
{
    Q_OBJECT

public:
    RegWin* ptr_LogWin_RegWin;
    PswdRmdWin* ptr_LogWin_PswdRmdWin;
    void makereferances(RegWin & LogWin_RegWin, PswdRmdWin & LogWin_PswdRmdWin);
    LogWin(QWidget *parent = nullptr);
    ~LogWin();

private slots:
    void on_LogWin_Button_log_clicked();
    void on_LogWin_Button_reg_clicked();
    void on_LogWin_Button_pswdrmd_clicked();
    void on_LogWin_CheckBox_autolog_toggled(bool checked);
    void set_redallert_to_null();

private:
    QTimer *timer_redallert;
    Ui::LogWin *ui;
};
#endif // LOGWIN_H
