#include "../Headers/pswdrmdwin.h"
#include "ui_pswdrmdwin.h"

PswdRmdWin::PswdRmdWin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PswdRmdWin)
{
    qDebug("PswdRmdWin Tworze");
    this->setAttribute( Qt::WA_DeleteOnClose );
    ui->setupUi(this);
}

PswdRmdWin::~PswdRmdWin()
{
    qDebug("PswdRmdWin Tworze");
    delete ui;
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


void PswdRmdWin::get_pointers(LogWin* PswdRmdWin_LogWin,RegWin* PswdRmdWin_RegWin)
{
    ptr_PswdRmdWin_LogWin = PswdRmdWin_LogWin;
    ptr_PswdRmdWin_RegWin = PswdRmdWin_RegWin;
}
