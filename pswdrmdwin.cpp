#include "pswdrmdwin.h"
#include "ui_pswdrmdwin.h"

PswdRmdWin::PswdRmdWin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PswdRmdWin)
{
    ui->setupUi(this);
}

PswdRmdWin::~PswdRmdWin()
{
    delete ui;
}

void PswdRmdWin::makereferances(LogWin& PswdRmdWin_LogWin, RegWin& PswdRmdWin_RegWin)
{
    ptr_PswdRmdWin_LogWin = &PswdRmdWin_LogWin;
    ptr_PswdRmdWin_RegWin = &PswdRmdWin_RegWin;
}

void PswdRmdWin::on_PswdRmdWin_Button_log_clicked()
{
    ptr_PswdRmdWin_LogWin->move(this->pos());
    ptr_PswdRmdWin_LogWin->show();
    this->hide();
}

void PswdRmdWin::on_PswdRmdWin_Button_reg_clicked()
{
    ptr_PswdRmdWin_RegWin->move(this->pos());
    ptr_PswdRmdWin_RegWin->show();
    this->hide();
}
