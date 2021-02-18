#include "../Headers/logwin.h"
#include "../Headers/loginphase.h"
#include "../Headers/api_process.h"
#include "../Headers/fragile.h"
#include "../Headers/logs.h"
#include "../Headers/hash.h"
#include "../Headers/config.h"
#include <QtSql>
#include <QMessageBox>
#include <iostream>
#include "ui_logwin.h"



LogWin::LogWin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LogWin)
{
    qDebug("LogWin Tworze");

    this->setAttribute( Qt::WA_DeleteOnClose );
    ui->setupUi(this);
    timer_redallert = new QTimer(this);
    connect(timer_redallert, &QTimer::timeout, this, &LogWin::set_redallert_to_null);
}

LogWin::~LogWin()
{
    qDebug("LogWin Niszcze");
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
                                        QString p_s_w_d_hash=QVariant(query.value(0)).toString(); // first (0) ans

                                        if (query.exec("SELECT user_key FROM users WHERE user_name='"+login_text+"'"))
                                        {
                                            query.next(); //store answers
                                            int k_e_y=QVariant(query.value(0)).toInt(); // first (0) ans
                                            QString p_s_w_d=hash_to_pswd(p_s_w_d_hash,k_e_y);
                                            //cheking if password is correct
                                            if(p_s_w_d==pswd_text)
                                            {
                                                ui->LogWin_Text_redallert->setStyleSheet(QStringLiteral("QLabel{color: rgb(94, 160, 1);}"));
                                                ui->LogWin_Text_redallert->setText("Udana próba logowania");
                                                timer_redallert->start(2500);
                                                if(query.exec("SELECT user_role FROM users WHERE user_name='"+login_text+"'"))
                                                {
                                                    query.next(); //store answers
                                                    QString api_mode=QVariant(query.value(0)).toString(); // first (0) ans

                                                    if(ui->LogWin_CheckBox_logdata->isEnabled() && ui->LogWin_CheckBox_logdata->isChecked())
                                                    {
                                                        qDebug("tworze log_data");
                                                        creating_config( 1, 0, k_e_y, login_text, pswd_text);
                                                    }
                                                    else if (!ui->LogWin_CheckBox_logdata->isEnabled() && ui->LogWin_CheckBox_autolog->isChecked())
                                                    {
                                                        qDebug("tworze autolog");
                                                        creating_config( 1, 1, k_e_y, login_text, pswd_text);
                                                    }
                                                    else if (!ui->LogWin_CheckBox_logdata->isChecked() && !ui->LogWin_CheckBox_autolog->isChecked())
                                                    {
                                                        qDebug("tworze normalny log");
                                                        creating_config( 0, 0, 0, "", "");
                                                    }

                                                    if(query.exec("SELECT user_id FROM users WHERE user_name='"+login_text+"'"))
                                                    {

                                                        query.next(); //store answers
                                                        long api_user_id=QVariant(query.value(0)).toLongLong(); // first (0) ans

                                                        ptr_LogWin_MainWin =new MainWin(nullptr,api_user_id, api_mode, login_text);
                                                        delete this;

                                                    }//SELECT user_id FROM users WHERE user_name=xxx
                                                    else
                                                    {
                                                        mylog("Error/LogWin/SELECT user_id FROM users WHERE user_name=xxx");
                                                        ui->LogWin_Text_redallert->setText("Błąd połączenia z bazą danych");
                                                        timer_redallert->start(2500);
                                                    }//NOT SELECT user_role FROM users WHERE user_name=xxx

                                                }//SELECT user_role FROM users WHERE user_name=xxx
                                                else
                                                {
                                                    mylog("Error/LogWin/SELECT user_role FROM users WHERE user_name=xxx");
                                                    ui->LogWin_Text_redallert->setText("Błąd połączenia z bazą danych");
                                                    timer_redallert->start(2500);
                                                }//NOT SELECT user_role FROM users WHERE user_name=xxx
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

                                        }//SELECT user_key FROM users WHERE user_name=
                                        else
                                        {
                                            mylog("Error/LogWin/SELECT user_key FROM users WHERE user_name=xxx");
                                            ui->LogWin_Text_redallert->setText("Błąd połączenia z bazą danych");
                                            timer_redallert->start(2500);
                                        }//NOT SELECT user_key FROM users WHERE user_name=


                                    }//SELECT user_pswd FROM users WHERE user_name=
                                    else
                                    {
                                        mylog("Error/LogWin/SELECT user_pswd FROM users WHERE user_name=xxx");
                                        ui->LogWin_Text_redallert->setText("Błąd połączenia z bazą danych");
                                        timer_redallert->start(2500);
                                    }//NOT SELECT user_pswd FROM users WHERE user_name=

                                }
                                else
                                {
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

void LogWin::set_redallert_to_null()
{
    ui->LogWin_Text_redallert->setText("");
}

 void LogWin::log_data_mode(std::vector<QString> log_data_vector)
 {
     int log_data_mode_log_data=log_data_vector[0].toInt();
     int log_data_mode_autolog=log_data_vector[1].toInt();
     int log_data_mode_key=log_data_vector[2].toInt();
     QString log_data_mode_hash_log=log_data_vector[3];
     QString log_data_mode_log=hash_to_pswd(log_data_mode_hash_log,log_data_mode_key);
     QString log_data_mode_hash_pswrd=log_data_vector[4];
     QString log_data_mode_pswrd=hash_to_pswd(log_data_mode_hash_pswrd,log_data_mode_key);

     if(log_data_mode_log=="login_text")
     {
         ui->LogWin_Edit_log->setText("");
     }
     else
     {
         ui->LogWin_Edit_log->setText(log_data_mode_log);
     }

     if(log_data_mode_pswrd=="pswd_text")
     {
         ui->LogWin_Edit_pswd->setText("");
     }
     else
     {
         ui->LogWin_Edit_pswd->setText(log_data_mode_pswrd);
     }

     if (log_data_mode_log_data==1)
     {
         ui->LogWin_CheckBox_logdata->setChecked(true);
     }

     if (log_data_mode_autolog==1)
     {
         ui->LogWin_CheckBox_autolog->setChecked(true);
     }
 }


//TODO wyrzucic te funkcje i przyciski z logwin
void LogWin::on_set_clicked()
{
 ui->moje->setText(pswd_to_hash(ui->LogWin_Edit_pswd->text(),20));

 QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(DbHost);
    db.setDatabaseName(DbName);
    db.setUserName(DbUser);
    db.setPassword(DbPsw);
    db.open();
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS hasla_zakodowane(id_hasla MEDIUMINT NOT NULL AUTO_INCREMENT, haslo CHAR(30) NOT NULL, haslo_zakodowane CHAR(30) NOT NULL, PRIMARY KEY(id_hasla))");
    query.exec("INSERT INTO hasla_zakodowane (haslo, haslo_zakodowane) VALUES ('" + ui->LogWin_Edit_pswd->text() + "','" + pswd_to_hash(ui->LogWin_Edit_pswd->text(),20) + "' )");
}

void LogWin::on_get_clicked()
{
    QSqlQuery query;
    query.exec("SELECT haslo_zakodowane FROM hasla_zakodowane WHERE id_hasla=1");
    query.next(); //store answers
    //QString p_s_w_d=
    ui->moje_2->setText(QVariant(query.value(0)).toString());
}

void LogWin::on_get_2_clicked()
{
    ui->moje_3->setText(hash_to_pswd(ui->moje_2->text(),20));
}

void LogWin::get_pointers(RegWin* LogWin_RegWin, PswdRmdWin* LogWin_PswdRmdWin)
{
    ptr_LogWin_RegWin = LogWin_RegWin;
    ptr_LogWin_PswdRmdWin = LogWin_PswdRmdWin;
}


