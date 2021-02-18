#include "../Headers/mainwin.h"
#include "../Headers/accont_data_change.h"
#include "../Headers/loginphase.h"
#include "../Headers/api_process.h"
#include "../Headers/config.h"
#include <iostream>
#include <QDebug>
#include <QString>
#include <QMenuBar>
#include <QtWidgets>
#include "ui_mainwin.h"

//TODO w trybie moderatora dac zarzadzanie organizacja, dodawanie uzytkownika, zmiana uzytkownika
//TODO damy jeszcze moderatora ktory moze dodawac projekty i kontrahentow
//uzytkownik moze tylko dodawac zadania
//gosc moze tylko uczestniczyc w zadaniach
//admin,moder,user,guest
//dministrator,moderator,użytkownik,gość

MainWin::MainWin(QWidget *parent, int user_id, QString mode, QString name_to_title)
    : QMainWindow(parent)
    , ui(new Ui::MainWin)
{
    this->setAttribute( Qt::WA_DeleteOnClose );
    ui->setupUi(this);
    qDebug("MainWin Tworze");
    ui->lol->setText(QString::number(user_id));
    api_user_id=user_id;
    this->api_mode=mode;
    this->setWindowTitle("WiP - "+name_to_title);
    this->setWindowState(Qt::WindowMaximized);
    this->setmenu();
    this->show();
}

MainWin::~MainWin()
{

    qDebug("MainWin Niszcze");
    delete ui;
}

void MainWin::setmenu()
{
    qDebug("Ustawienie menu");

    QMenuBar *menuBar = new QMenuBar(this);
    menuBar->setObjectName(QString::fromUtf8("menuBar"));
    menuBar->setGeometry(QRect(0, 0, 800, 20));

    QMenu *menuaccontdata = new QMenu(menuBar);
    menuaccontdata->setObjectName(QString::fromUtf8("menuaccontdata"));
    menuaccontdata->setTitle(QCoreApplication::translate("MainWin", "ustawienia konta", nullptr));
    menuBar->addAction(menuaccontdata->menuAction());

    QAction *action_accont_data_change = new QAction(this);
    action_accont_data_change->setObjectName(QString::fromUtf8("action_accont_data_change"));
    action_accont_data_change->setText(QCoreApplication::translate("MainWin", "zmień dane", nullptr));
    connect(action_accont_data_change,SIGNAL(triggered()),this,SLOT(on_action_accont_data_change_triggered()));
    menuaccontdata->addAction(action_accont_data_change);

    QAction *action_logwin = new QAction(this);
    action_logwin->setObjectName(QString::fromUtf8("action_logwin"));
    action_logwin->setText(QCoreApplication::translate("MainWin", "okno logowania", nullptr));
    connect(action_logwin,SIGNAL(triggered()),this,SLOT(on_action_logwin_triggered()));
    menuaccontdata->addAction(action_logwin);
    if (api_mode=="admin")
    {
        QMenu *menuorg = new QMenu(menuBar);
        menuorg->setObjectName(QString::fromUtf8("menuorg"));
        menuorg->setTitle(QCoreApplication::translate("MainWin", "organizacja", nullptr));
        menuBar->addAction(menuorg->menuAction());

        QAction * actionuser = new QAction(this);
        actionuser->setObjectName(QString::fromUtf8("actionuser"));
        actionuser->setText(QCoreApplication::translate("MainWin", "użytkownicy", nullptr));
        menuorg->addAction(actionuser);
    }

    this->setMenuBar(menuBar);
}

void MainWin::on_pushButton_clicked()
{

}

void MainWin::on_action_logwin_triggered()
{
    ptr_mainwin_login_phase= new LoginPhase;
    ptr_mainwin_login_phase->ptr_login_phase_logwin->log_data_mode(log_data_from_config());
    ptr_mainwin_login_phase->logwin_show();
    this->destroy();
}

void MainWin::on_action_accont_data_change_triggered()
{
    ptr_mainwin_accont_data_change=new Accont_Data_Change;
    //ptr_mainwin_accont_data_change->setParent(this);
    //QWidget::setEnabled(false);
    ptr_mainwin_accont_data_change->show();
}
