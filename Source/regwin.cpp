#include "../Headers/regwin.h"
#include "ui_regwin.h"
#include "../Headers/config.h"
//#include "../Headers/config_example.h"
#include "../Headers/fragile.h"
//#include "../Headers/fragile_example.h"
#include "../Headers/logs.h"
#include "../Headers/hash.h"
#include  <QtSql>

RegWin::RegWin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RegWin)
{
    qDebug("RegWin Tworze");
    this->setAttribute( Qt::WA_DeleteOnClose );
    ui->setupUi(this);
    timer_redallert = new QTimer(this);
    connect(timer_redallert, &QTimer::timeout, this, &RegWin::set_redallert_to_null);
}

RegWin::~RegWin()
{
    qDebug("RegWin Niszcze");
    delete ui;
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
                   //creating an organization table
                    QSqlQuery query;
                    if(query.exec("CREATE TABLE IF NOT EXISTS organizations(org_id INT NOT NULL AUTO_INCREMENT, org_name CHAR(30) NOT NULL, PRIMARY KEY(org_id))"))
                    {
                        //checking if an organization with the given name exists
                        if (query.exec("SELECT org_name FROM organizations WHERE org_name='"+org_text+"'"))
                        {
                            if (query.next())
                            {
                                ui->RegWin_Text_redallert->setText("Organizacja o tej nazwie już istnieje");
                                timer_redallert->start(2500);
                            }//Organization exist

                            //the organization does not exist, we continue to create a new one
                            else
                            {
                                //enter the organization name  into the organizations table
                                if (query.exec("INSERT INTO organizations (org_name) VALUES ('" + org_text + "')"))
                                {
                                    if(query.exec("CREATE TABLE IF NOT EXISTS users(user_id INT NOT NULL AUTO_INCREMENT, user_name CHAR(50) NOT NULL, user_pswd CHAR(25) NOT NULL, user_key TINYINT NOT NULL, user_org CHAR(30) NOT NULL, user_role CHAR(30) NOT NULL, user_active_task CHAR(30) NOT NULL, user_status CHAR(10) NOT NULL, user_tries TINYINT NOT NULL, PRIMARY KEY(user_id))"))
                                    {
                                        //generating user_key
                                        std::uniform_int_distribution<int> random(10,35);
                                        int user_key=random(*QRandomGenerator::global());

                                        //adding user data to users table
                                        query.prepare("INSERT INTO users (user_name, user_pswd, user_key, user_org, user_role, user_active_task, user_status, user_tries) VALUES ('" + login_text + "', '" + pswd_to_hash(pswd_text,user_key) + "', :W_user_key, '" + org_text + "', 'admin', 'no', 'active', 0)" );
                                        query.bindValue(":W_user_key",user_key);
                                        if(query.exec())
                                        {
                                            if(query.exec("SELECT user_id FROM users WHERE user_name='" +login_text+"'"))
                                            {
                                                query.next(); //store answers
                                                QString id_adding_user=QVariant(query.value(0)).toString(); // first (0) ans
                                                if (query.exec("CREATE TABLE IF NOT EXISTS user_"+id_adding_user+"_ (id_task INT NOT NULL AUTO_INCREMENT, start CHAR(50) NOT NULL, stop CHAR(50) NOT NULL, project CHAR(50) NOT NULL, quest CHAR(50) NOT NULL, PRIMARY KEY(id_task))"))
                                                {
                                                    ui->RegWin_Text_redallert->setStyleSheet(QStringLiteral("QLabel{color: rgb(94, 160, 1);}"));
                                                    ui->RegWin_Text_redallert->setText("Organizacja " + org_text +" została zarejestrowana");
                                                    timer_redallert->start(2500);
                                                    db.close();

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

void RegWin::get_pointers(LogWin* RegWin_LogWin, PswdRmdWin* RegWin_PswdRmdWin)
{
    ptr_RegWin_LogWin = RegWin_LogWin;
    ptr_RegWin_PswdRmdWin = RegWin_PswdRmdWin;
}
