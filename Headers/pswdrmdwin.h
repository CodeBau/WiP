#ifndef PSWDRMDWIN_H
#define PSWDRMDWIN_H

#include <QMainWindow>
#include "logwin.h"
#include "regwin.h"
#include "window_init.h"

QT_BEGIN_NAMESPACE
namespace Ui { class PswdRmdWin; }
QT_END_NAMESPACE

class PswdRmdWin : public QMainWindow
{
    Q_OBJECT
public:
    PswdRmdWin(QWidget *parent = nullptr);
    ~PswdRmdWin();
    void get_pointers(LogWin* PswdRmdWin_LogWin,RegWin* PswdRmdWin_RegWin);

private slots:
    void on_PswdRmdWin_Button_log_clicked();
    void on_PswdRmdWin_Button_reg_clicked();

private:
    LogWin* ptr_PswdRmdWin_LogWin;
    RegWin* ptr_PswdRmdWin_RegWin;
    Ui::PswdRmdWin *ui;

};

#endif // PSWDRMDWIN_H

