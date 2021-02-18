#ifndef REGWIN_H
#define REGWIN_H

#include <QMainWindow>
#include <QTimer>
#include "logwin.h"
#include "pswdrmdwin.h"
#include "window_init.h"

QT_BEGIN_NAMESPACE
namespace Ui { class RegWin; }
QT_END_NAMESPACE

class RegWin : public QMainWindow
{
    Q_OBJECT
public:
    RegWin(QWidget *parent = nullptr);
    ~RegWin();
    void get_pointers(LogWin* RegWin_LogWin, PswdRmdWin* RegWin_PswdRmdWin);

private slots:
    void set_redallert_to_null();
    void on_RegWin_Button_reg_clicked();
    void on_RegWin_Button_log_clicked();
    void on_RegWin_Button_pswdrmd_clicked();

private:
    LogWin* ptr_RegWin_LogWin;
    PswdRmdWin* ptr_RegWin_PswdRmdWin;
    QTimer *timer_redallert;
    Ui::RegWin *ui;
};

#endif // REGWIN_H

