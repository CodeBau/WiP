#ifndef STARTWIN_H
#define STARTWIN_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class StartWin; }
QT_END_NAMESPACE

class StartWin : public QMainWindow
{
    Q_OBJECT
public:
    StartWin(QWidget *parent = nullptr);
    ~StartWin();

private slots:
    void on_LogWin_Button_pswdrmd_clicked();
    void on_LogWin_Button_reg_clicked();

    void on_PswdRmdWin_Button_reg_clicked();

    void on_PswdRmdWin_Button_log_clicked();

    void on_RegWin_Button_pswdrmd_clicked();

    void on_RegWin_Button_log_clicked();

private:
    Ui::StartWin *ui;

};

#endif // STARTWIN_H

