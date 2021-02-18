#include "../Headers/api_process.h"
#include "../Headers/logs.h"
#include "../Headers/hash.h"
#include "../Headers/logwin.h"
#include "../Headers/fragile.h"
#include "../Headers/mainwin.h"
#include "../Headers/loginphase.h"
#include "../Headers/config.h"
#include <QTextStream>
#include <QFile>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QtSql>

Api_Process::Api_Process()
{
    qDebug("Api_Process Tworze");
    my_init_mode = mode_normal;
}

Api_Process::~Api_Process()
{
    qDebug("Api_Process Niszcze");
}

void Api_Process::start()
{
    qDebug("Api_Process::start");
    mylog("App.Start");
    my_init_mode=checking_config();
}

void Api_Process::init()
{
    qDebug("Api_Process::init");

    if(my_init_mode==mode_normal)
    {
      init_login_phase= new LoginPhase();
      init_login_phase->logwin_show();
    }
    else if(my_init_mode==mode_log_data)
    {
      init_login_phase= new LoginPhase();
      init_login_phase->ptr_login_phase_logwin->log_data_mode(log_data_from_config());
      init_login_phase->logwin_show();
    }
    else if(my_init_mode==mode_autolog)
    {
      autolog_from_config();
    }
}

Api_Process::InitMode Api_Process::checking_config()
{
    std::vector<QString> log_data_vector={"","","","",""};
    log_data_vector=log_data_from_config();
    int config_log_data=log_data_vector[0].toInt();
    int config_autolog=log_data_vector[1].toInt();

    if(config_log_data==1 && config_autolog==1)
    {
        return mode_autolog;
    }
    else if (config_log_data==1 && config_autolog==0)
    {
        return mode_log_data;
    }
    else
    {
        return mode_normal;
    }

    return mode_normal;
}


void Api_Process::autolog_from_config()
{
    std::vector<QString> log_data_vector={"","","","",""};
    log_data_vector=log_data_from_config();
    int config_autolog_user_key=log_data_vector[2].toInt();
    QString config_autolog_login=hash_to_pswd(log_data_vector[3],config_autolog_user_key);
    QString config_autolog_pswd=hash_to_pswd(log_data_vector[4],config_autolog_user_key);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(DbHost);
    db.setDatabaseName(DbName);
    db.setUserName(DbUser);
    db.setPassword(DbPsw);

    if (db.open())
    {
        QSqlQuery query;
        if (query.exec("SELECT user_name FROM users WHERE user_name='"+config_autolog_login+"'"))
        {
            if (query.next())
            {
                if(query.exec("SELECT user_tries FROM users WHERE user_name='"+config_autolog_login+"'"))
                {
                    query.next(); //store answers
                    int user_actual_tries=QVariant(query.value(0)).toInt(); // first (0) ans

                    if(user_actual_tries<3)
                    {
                        if (query.exec("SELECT user_pswd FROM users WHERE user_name='"+config_autolog_login+"'"))
                        {
                            query.next(); //store answers
                            QString p_s_w_d_hash=QVariant(query.value(0)).toString(); // first (0) ans

                            if (query.exec("SELECT user_key FROM users WHERE user_name='"+config_autolog_login+"'"))
                            {
                                query.next(); //store answers
                                int k_e_y=QVariant(query.value(0)).toInt(); // first (0) ans
                                QString p_s_w_d=hash_to_pswd(p_s_w_d_hash,k_e_y);
                                //cheking if password is correct
                                if(p_s_w_d==config_autolog_pswd)
                                {
                                    if(query.exec("SELECT user_role FROM users WHERE user_name='"+config_autolog_login+"'"))
                                    {
                                        query.next(); //store answers
                                        QString api_mode=QVariant(query.value(0)).toString(); // first (0) ans
                                        if(query.exec("SELECT user_id FROM users WHERE user_name='"+config_autolog_login+"'"))
                                        {
                                            query.next(); //store answers
                                            long api_user_id=QVariant(query.value(0)).toLongLong(); // first (0) ans
                                            init_mainwin = new MainWin(nullptr,api_user_id,api_mode,config_autolog_login);
                                            // ptr_login_phase_mainwin->set(api_user_id, api_mode, config_autolog_login);

                                        }//SELECT user_id FROM users WHERE user_name=xxx
                                        else
                                        {
                                            mylog("Error/Autolog/SELECT user_id FROM users WHERE user_name=xxx");
                                            autolog_fail_LogWin_show();
                                        }//NOT SELECT user_id FROM users WHERE user_name=xxx

                                    }//SELECT user_role FROM users WHERE user_name=xxx
                                    else
                                    {
                                        mylog("Error/Autolog/SELECT user_role FROM users WHERE user_name=xxx");
                                        autolog_fail_LogWin_show();
                                    }//NOT SELECT user_role FROM users WHERE user_name=xxx
                                }//Good Passward

                                else
                                {
                                    user_actual_tries++;
                                    query.prepare("UPDATE users SET user_tries = :W_tries WHERE user_name='"+config_autolog_login+"'");
                                    query.bindValue(":W_tries",user_actual_tries);

                                    if (query.exec())
                                    {
                                        autolog_fail_LogWin_show();
                                    }
                                    else
                                    {
                                        mylog("Error/Autolog/UPDATE users SET user_tries = :W_tries WHERE user_name=xxx");
                                        autolog_fail_LogWin_show();
                                    }

                                }//Bad password

                            }//SELECT user_key FROM users WHERE user_name=
                            else
                            {
                                mylog("Error/Autolog/SELECT user_key FROM users WHERE user_name=xxx");
                                autolog_fail_LogWin_show();
                            }//NOT SELECT user_key FROM users WHERE user_name=


                        }//SELECT user_pswd FROM users WHERE user_name=
                        else
                        {
                            mylog("Error/Autolog/SELECT user_pswd FROM users WHERE user_name=xxx");
                            autolog_fail_LogWin_show();
                        }//NOT SELECT user_pswd FROM users WHERE user_name=

                    }
                    else
                    {
                        mylog("Error/Autolog/Account blocked");
                        autolog_fail_LogWin_show();
                    }
                }//SELECT user_tries FROM users
                else
                {
                    mylog("Error/Autolog/SELECT user_tries FROM users WHERE user_name=xxx");
                    autolog_fail_LogWin_show();
                }//NOT SELECT user_tries FROM users

            }//User exist
            else
            {
                autolog_fail_LogWin_show();
            }//User NOT exist
        }//SELECT user_name FROM users WHERE user_name=
        else
        {
            mylog("Error/Autolog/SELECT user_name FROM users WHERE user_name=xxx");
            autolog_fail_LogWin_show();
        }//NOT SELECT user_name FROM users WHERE user_name=

    }//db.open()
    else
    {
        mylog("Error/Autolog/db.open()");
        autolog_fail_LogWin_show();
    }// NOT db.open()

}

void Api_Process::autolog_fail_LogWin_show()
{
    warning_msg("Podczas próby autologowania wystąpił błąd./n Proszę dokonać ponownego logowania.", "Błąd Autologowania");
    init_login_phase = new LoginPhase();
    init_login_phase->logwin_show();
}

void Api_Process::warning_msg(QString text, QString title)
{
    QMessageBox msgWarning;
    msgWarning.setText(text);
    msgWarning.setIcon(QMessageBox::Warning);
    msgWarning.setWindowTitle(title);
    msgWarning.exec();
}
