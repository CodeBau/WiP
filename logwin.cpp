#include "logwin.h"
#include "ui_logwin.h"
#include "config.h"
#include "logs.h"
#include <QtSql>

#include <iostream>

LogWin::LogWin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LogWin)
{
    ui->setupUi(this);
    timer_redallert = new QTimer(this);
    connect(timer_redallert, &QTimer::timeout, this, &LogWin::set_redallert_to_null);

}

LogWin::~LogWin()
{
    delete ui;
}

void LogWin::on_LogWin_Button_log_clicked()
{
    QString login_text;
    login_text=ui->LogWin_Edit_log->text();
    QString pswd_text;
    pswd_text=ui->LogWin_Edit_pswd->text();
    if(login_text.size()==0 && pswd_text.size()==0)
    {
        ui->LogWin_Text_redallert->setText("Uzupełnij pola");
        timer_redallert->start(2500);
    }
    else if(login_text.size()==0 && pswd_text.size()>0)
    {
        ui->LogWin_Text_redallert->setText("Uzupełnij e-mail");
        timer_redallert->start(2500);
    }
    else if(login_text.size()>0 && pswd_text.size()==0)
    {
        ui->LogWin_Text_redallert->setText("Uzupełnij hasło");
        timer_redallert->start(2500);
    }
    else if(login_text.size()>0 && pswd_text.size()>0)
    {
        bool login_donthave_at =true;
        for (int i = 0; i < login_text.size(); ++i)
        {
            if (login_text.at(i) == QChar('@'))
            login_donthave_at=false;
        }
        if(login_donthave_at)
        {
            ui->LogWin_Text_redallert->setText("Sprawdź poprawność adresu e-mail");
            timer_redallert->start(2500);
        }
        else
        {
            QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
               db.setHostName(DbHost);
               db.setDatabaseName(DbName);
               db.setUserName(DbUser);
               db.setPassword(DbPsw);

               if (db.open())
               {
                   QSqlQuery query;
                   if (query.exec("SELECT user_name FROM users WHERE user_name='"+login_text+"'"))
                   {
                       if (query.next())
                       {
                            if(query.exec("SELECT user_tries FROM users WHERE user_name='"+login_text+"'"))
                            {
                                query.next(); //store answers
                                int user_actual_tries=QVariant(query.value(0)).toInt(); // first (0) ans

                                if(user_actual_tries<3)
                                {
                                    if (query.exec("SELECT user_pswd FROM users WHERE user_name='"+login_text+"'"))
                                    {

                                        query.next(); //store answers
                                        QString p_s_w_d=QVariant(query.value(0)).toString(); // first (0) ans

                                       if(p_s_w_d==pswd_text)
                                       {

                                           ui->LogWin_Text_redallert->setStyleSheet(QStringLiteral("QLabel{color: rgb(94, 160, 1);}"));
                                           ui->LogWin_Text_redallert->setText("Udana próba logowania");
                                           timer_redallert->start(2500);

                                       qDebug("Dobre hasło");

                                       if(ui->LogWin_CheckBox_logdata->isEnabled() && ui->LogWin_CheckBox_logdata->isChecked())
                                       {
                                            qDebug("dane logowania zapamiętaj");
                                            QFile logFile("config.wip");
                                            if(logFile.open(QIODevice::Text)){
                                                QTextStream outLog(&logFile);
                                                outLog <<"wip.config.user.set"
                                                       <<"1\n"
                                                       <<"0\n"
                                                       << login_text <<"\n"
                                                       << pswd_text <<"\n";
                                            }
                                            else
                                            {
                                                //TODO message: problem with files
                                            }

                                            //TODO open mainwin
                                       }
                                       else if (!ui->LogWin_CheckBox_logdata->isEnabled() && ui->LogWin_CheckBox_autolog->isChecked())
                                       {
                                            qDebug("autologowanie");

                                       }

                                       else if (!ui->LogWin_CheckBox_logdata->isChecked() && !ui->LogWin_CheckBox_autolog->isChecked())
                                       {
                                            qDebug("poprostu logowanie");

                                            //TODO deleting info from file

                                       }

                                       //TODO autologowanie

                                       //TODO danelogowania

                                       }//Good Passward
                                       else
                                       {
                                           user_actual_tries++;
                                           query.prepare("UPDATE users SET user_tries = :W_tries WHERE user_name='"+login_text+"'");
                                           query.bindValue(":W_tries",user_actual_tries);

                                           if (query.exec())
                                           {
                                               ui->LogWin_Text_redallert->setText("Błędne hasło");
                                               timer_redallert->start(2500);
                                           }
                                           else
                                           {
                                               mylog("Error/LogWin/UPDATE users SET user_tries = :W_tries WHERE user_name=xxx");
                                               ui->LogWin_Text_redallert->setText("Błąd połączenia z bazą danych");
                                               timer_redallert->start(2500);
                                           }

                                       }//Bad password
                                    }//SELECT user_pswd FROM users WHERE user_name=
                                    else
                                    {
                                        mylog("Error/LogWin/SELECT user_pswd FROM users WHERE user_name=");
                                        ui->LogWin_Text_redallert->setText("Błąd połączenia z bazą danych");
                                        timer_redallert->start(2500);
                                    }//NOT SELECT user_pswd FROM users WHERE user_name=

                                }
                                else
                                {
                                    qDebug("więcej niż 3 próby");
                                    mylog("Error/LogWin/Account blocked");
                                    ui->LogWin_Text_redallert->setText("Konto zablokowane");
                                    timer_redallert->start(2500);
                                }
                            }//SELECT user_tries FROM users
                            else
                            {
                                mylog("Error/LogWin/SELECT user_tries FROM users WHERE user_name=xxx");
                                ui->LogWin_Text_redallert->setText("Błąd połączenia z bazą danych");
                                timer_redallert->start(2500);
                            }//NOT SELECT user_tries FROM users

                       }//User exist
                       else
                       {
                           ui->LogWin_Text_redallert->setText("Adres e-mail nie jest powiązany z żadnym z istniejących kont");
                           timer_redallert->start(2500);
                       }//User NOT exist
                   }//SELECT user_name FROM users WHERE user_name=
                   else
                   {
                       mylog("Error/LogWin/SELECT user_name FROM users WHERE user_name=xxx");
                       ui->LogWin_Text_redallert->setText("Błąd połączenia z bazą danych");
                       timer_redallert->start(2500);
                   }

               }//db.open()
               else
               {
                   mylog("Error/LogWin/db.open()");
                   ui->LogWin_Text_redallert->setText("Błąd połączenia z bazą danych");
                   timer_redallert->start(2500);
               }// NOT db.open()
        }
    }
}

void LogWin::on_LogWin_Button_reg_clicked()
{
   //ptr_LogWin_RegWin->move(this->mapToGlobal(this->pos()));
   ptr_LogWin_RegWin->move(this->pos());
   ptr_LogWin_RegWin->show();
   this->hide();
}

void LogWin::on_LogWin_Button_pswdrmd_clicked()
{
   ptr_LogWin_PswdRmdWin->move(this->pos());
   ptr_LogWin_PswdRmdWin->show();
   this->hide();
}

void LogWin::on_LogWin_CheckBox_autolog_toggled(bool checked)
{
    if (checked)
    {
    ui->LogWin_CheckBox_logdata->setChecked(true);
    ui->LogWin_CheckBox_logdata->setEnabled(false);
    }
    else
    {
    ui->LogWin_CheckBox_logdata->setChecked(false);
    ui->LogWin_CheckBox_logdata->setEnabled(true);
    }
}

void LogWin::makereferances(RegWin & LogWin_RegWin, PswdRmdWin & LogWin_PswdRmdWin)
{
    ptr_LogWin_RegWin = &LogWin_RegWin;
    ptr_LogWin_PswdRmdWin = &LogWin_PswdRmdWin;
}

void LogWin::set_redallert_to_null()
{
    ui->LogWin_Text_redallert->setText("");
}

