#include "../Headers/startwin.h"
#include "ui_startwin.h"

StartWin::StartWin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartWin)
{
    qDebug("StartWin Tworze");
    this->setAttribute( Qt::WA_DeleteOnClose );
    ui->setupUi(this);
}

StartWin::~StartWin()
{
    qDebug("StartWin Tworze");
    delete ui;
}

void StartWin::on_LogWin_Button_pswdrmd_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void StartWin::on_LogWin_Button_reg_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void StartWin::on_PswdRmdWin_Button_reg_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void StartWin::on_PswdRmdWin_Button_log_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void StartWin::on_RegWin_Button_pswdrmd_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void StartWin::on_RegWin_Button_log_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
