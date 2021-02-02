#ifndef PSWDRMDWIN_H
#define PSWDRMDWIN_H

#include <QMainWindow>
#include "logwin.h"
#include "regwin.h"

class LogWin;
class RegWin;

QT_BEGIN_NAMESPACE
namespace Ui { class PswdRmdWin; }
QT_END_NAMESPACE

class PswdRmdWin : public QMainWindow
{
    Q_OBJECT
public:
    LogWin* ptr_PswdRmdWin_LogWin;
    RegWin* ptr_PswdRmdWin_RegWin;

    void makereferances(LogWin& PswdRmdWin_LogWin, RegWin& PswdRmdWin_RegWin);

    PswdRmdWin(QWidget *parent = nullptr);
    ~PswdRmdWin();

private slots:
    void on_PswdRmdWin_Button_log_clicked();

    void on_PswdRmdWin_Button_reg_clicked();

private:
    Ui::PswdRmdWin *ui;

};

#endif // PSWDRMDWIN_H

