#include "regwin.h"
#include "ui_regwin.h"
#include "config.h"
//#include "config_example.h"
#include "logs.h"
#include <QtSql>

RegWin::RegWin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RegWin)
{
    ui->setupUi(this);
    timer_redallert = new QTimer(this);
    connect(timer_redallert, &QTimer::timeout, this, &RegWin::set_redallert_to_null);
}

RegWin::~RegWin()
{
    delete ui;
}


void RegWin::makereferances(LogWin& RegWin_LogWin, PswdRmdWin& RegWin_PswdRmdWin)
{
    ptr_RegWin_LogWin = &RegWin_LogWin;
    ptr_RegWin_PswdRmdWin = &RegWin_PswdRmdWin;
}

void RegWin::on_RegWin_Button_reg_clicked()
{
    QString login_text="";
    login_text=ui->RegWin_Edit_log->text();
    QString pswd_text="";
    pswd_text=ui->RegWin_Edit_pswd->text();
    QString org_text="";
    org_text=ui->RegWin_Edit_org->text();
    if(login_text.size()>0 && pswd_text.size()>0 && org_text.size()>0)
    {
        bool login_donthave_at =true;
        for (int i = 0; i < login_text.size(); ++i)
        {
            if (login_text.at(i) == QChar('@'))
            login_donthave_at=false;
        }
        if(login_donthave_at)
        {
            ui->RegWin_Text_redallert->setText("Sprawdź poprawność adresu e-mail");
            timer_redallert->start(2500);
        }
        else if (pswd_text.size()<6)
        {
            ui->RegWin_Text_redallert->setText("Hasło musi mieć minimum 6 znaków");
            timer_redallert->start(2500);
        }
        else if (org_text.size()<3)
        {
            ui->RegWin_Text_redallert->setText("Nazwa organizacji musi mieć minimum 3 znaki");
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
                    if(query.exec("CREATE TABLE IF NOT EXISTS organizations(id_org MEDIUMINT NOT NULL AUTO_INCREMENT, organization_name CHAR(30) NOT NULL, PRIMARY KEY(id_org))"))
                    {
                        if (query.exec("SELECT organization_name FROM organizations WHERE organization_name='"+org_text+"'"))
                        {
                            if (query.next())
                            {
                                ui->RegWin_Text_redallert->setText("Organizacja o tej nazwie już istnieje");
                                timer_redallert->start(2500);
                            }//Organization exist
                            else
                            {
                                if (query.exec("INSERT INTO organizations (organization_name) VALUES ('" + org_text + "')"))
                                {
                                    if(query.exec("CREATE TABLE IF NOT EXISTS users(id_user MEDIUMINT NOT NULL AUTO_INCREMENT, user_name CHAR(50) NOT NULL, user_pswd CHAR(25) NOT NULL, user_org CHAR(30) NOT NULL, user_role CHAR(30) NOT NULL,user_status CHAR(10) NOT NULL, user_tries SMALLINT NOT NULL, PRIMARY KEY(id_user))"))
                                    {
                                        if(query.exec("INSERT INTO users (user_name, user_pswd, user_org, user_role,user_status, user_tries) VALUES ('" + login_text + "', '" + pswd_text + "', '" + org_text + "', 'admin', 'active', 0)" ))
                                        {
                                            if(query.exec("SELECT id_user FROM users WHERE user_name='" +login_text+"'"))
                                            {
                                                query.next(); //store answers
                                                QString id_adding_user=QVariant(query.value(0)).toString(); // first (0) ans
                                                if (query.exec("CREATE TABLE IF NOT EXISTS user_"+id_adding_user+"_ (id_task MEDIUMINT NOT NULL AUTO_INCREMENT, start CHAR(50) NOT NULL, stop CHAR(50) NOT NULL, project CHAR(50) NOT NULL, quest CHAR(50) NOT NULL, PRIMARY KEY(id_task))"))
                                                {
                                                    ui->RegWin_Text_redallert->setStyleSheet(QStringLiteral("QLabel{color: rgb(94, 160, 1);}"));
                                                    ui->RegWin_Text_redallert->setText("Organizacja " + org_text +" została zarejestrowana");
                                                    timer_redallert->start(2500);

                                                    qDebug()<<db.isOpen();
                                                    db.close();
                                                    qDebug()<<db.isOpen();

                                                    //TODO close db

                                                 }//CREATE TABLE user_+id
                                                else
                                                {
                                                    mylog("Error/RegWin/CREATE TABLE IF NOT EXISTS user_'+id_adding_user");
                                                    ui->RegWin_Text_redallert->setText("Błąd bazy danych");
                                                    timer_redallert->start(2500);
                                                }//NOT CREATE TABLE user_+id

                                            }//SELECT id_user FROM users
                                            else
                                            {
                                                mylog("Error/RegWin/SELECT id_user FROM users WHERE user_name='xxx'");
                                                ui->RegWin_Text_redallert->setText("Błąd bazy danych");
                                                timer_redallert->start(2500);

                                            }//NOT SELECT id_user FROM users

                                        }//INSERT INTO users
                                        else
                                        {
                                            mylog("Error/RegWin/INSERT INTO users");
                                            ui->RegWin_Text_redallert->setText("Błąd bazy danych");
                                            timer_redallert->start(2500);
                                        }//NOT INSERT INTO users

                                    }//CREATE TABLE users
                                    else
                                    {
                                        mylog("Error/RegWin/CREATE TABLE users");
                                        ui->RegWin_Text_redallert->setText("Błąd bazy danych");
                                        timer_redallert->start(2500);
                                    }//NOT CREATE TABLE IF NOT EXISTS users
                                }//INSERT INTO organizations
                                else
                                {
                                    mylog("Error/RegWin/INSERT INTO organizations");
                                    ui->RegWin_Text_redallert->setText("Błąd bazy danych");
                                    timer_redallert->start(2500);
                                }//NOT INSERT INTO organizations

                            }//Organization NOT exist
                        }//SELECT organization_name FROM organizations
                        else
                        {
                            mylog("Error/RegWin/SELECT organization_name FROM organizations");
                            ui->RegWin_Text_redallert->setText("Błąd bazy danych");
                            timer_redallert->start(2500);
                        }//NOT INSERT INTO organizations


                    }//CREATE TABLE organizations
                    else
                    {
                        mylog("Error/RegWin/CREATE TABLE organizations");
                        ui->RegWin_Text_redallert->setText("Błąd bazy danych");
                        timer_redallert->start(2500);
                    }//NOT CREATE TABLE organizations



               }//db.open()
               else
               {
                   mylog("Error/RegWin/db.open()");
                   ui->RegWin_Text_redallert->setText("Błąd połączenia z bazą danych");
                   timer_redallert->start(2500);
               }// NOT db.open()

        }
    }
    else if(login_text.size()==0 && pswd_text.size()>0 && org_text.size()>0)
    {
        ui->RegWin_Text_redallert->setText("Uzupełnij e-mail");
        timer_redallert->start(2500);
    }
    else if(login_text.size()>0 && pswd_text.size()==0 && org_text.size()>0)
    {
        ui->RegWin_Text_redallert->setText("Uzupełnij hasło");
        timer_redallert->start(2500);
    }
    else if(login_text.size()>0 && pswd_text.size()>0 && org_text.size()==0)
    {
        ui->RegWin_Text_redallert->setText("Uzupełnij nazwę organizacji");
        timer_redallert->start(2500);
    }
    else if(login_text.size()==0 && pswd_text.size()==0&& org_text.size()==0)
    {
        ui->RegWin_Text_redallert->setText("Uzupełnij pola");
        timer_redallert->start(2500);
    }
    else if((login_text.size()==0 && pswd_text.size()==0&& org_text.size()>0)||(login_text.size()==0 && pswd_text.size()>0&& org_text.size()==0)||(login_text.size()>0 && pswd_text.size()==0&& org_text.size()==0))
    {
        ui->RegWin_Text_redallert->setText("Uzupełnij brakujące pola");
        timer_redallert->start(2500);
    }

}

void RegWin::on_RegWin_Button_log_clicked()
{
    ptr_RegWin_LogWin->move(this->pos());
    ptr_RegWin_LogWin->show();
    this->hide();
}

void RegWin::on_RegWin_Button_pswdrmd_clicked()
{
    ptr_RegWin_PswdRmdWin->move(this->pos());
    ptr_RegWin_PswdRmdWin->show();
    this->hide();
}

void RegWin::set_redallert_to_null()
{
    ui->RegWin_Text_redallert->setText("");
    ui->RegWin_Text_redallert->setStyleSheet(QStringLiteral("QLabel{color: rgb(227, 6,19);}"));

}
