/*

#include "../Headers/config.h"
#include "../Headers/hash.h"
#include <QMessageBox>
#include <QFile>
#include <QRandomGenerator>
#include <QTextStream>
#include <QDir>

void creating_config (int log_data, int autolog,int key_int, QString login_text, QString pswd_text)
{
    QDir root=QDir::current();
    root.mkdir("data");

    QFile configFile("data/config.wip");
    if(configFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream inConfig(&configFile);
        for(int i=1;i<=10;i++)
        {
            switch (i)
            {
            case 1:
            {
                inConfig <<"<wip.config.user.set>"<<"\n";
                break;
            }
            case 2:
            {
                inConfig <<random_QString(10) << log_data <<"\n";
                break;
            }
            case 3:
            {
                inConfig << random_QString(10) << autolog <<"\n";
                break;
            }
            case 4:
            {
                inConfig << random_QString(10) << key_int <<"\n";
                break;
            }
            case 5:
            {
                inConfig<< random_QString(5)<<pswd_to_hash(login_text,key_int) <<"\n";
                break;
            }
            case 6:
            {
                 inConfig<<random_QString(5) << pswd_to_hash(pswd_text,key_int)  <<"\n";
                 break;
            }
            default:
            {
                inConfig <<random_QString(random_int(10,40))<<"\n";
                break;
            }
            }
        }
     }

    else
    {
        QMessageBox msgWarning;
        msgWarning.setText("Program, nie może zapisać odpowiednich plików w swoim środowisku.\nSprawdź możliwość zapisu danych w folderze program.");
        msgWarning.setIcon(QMessageBox::Warning);
        msgWarning.setWindowTitle("Uwaga");
        msgWarning.exec();
    }
}

QString random_QString (int char_num)
{
    QString out;
    for(int i=0; i<char_num;i++)
    {
        QChar new_randow_QCHar = random_QChar();
        out.append( new_randow_QCHar);
    }
    return out;
}

QChar random_QChar ()
{
    int QChar_Decimal_Values=random_int(32,255);
    QChar out((short) QChar_Decimal_Values);
    return out;
}

int random_int (int min, int max)
{
    std::uniform_int_distribution<int> random(min,max);
    int random_value=random(*QRandomGenerator::global());
    return random_value;
}

std::vector<QString> log_data_from_config()
{
    std::vector<QString> out={"","","","",""};
    QFile configFile("data/config.wip");
    if(configFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        int i=2;
        QTextStream outConfig(&configFile);
        QString line = outConfig.readLine();
        QString config_log_data;
        QString config_autolog;
        QString config_user_key;
        QString config_login_hash;
        QString config_pswd_hash;

            while (!line.isNull()) {
               // process_line(line);
                line = outConfig.readLine();
                switch (i)
                {
                case 2:
                {
                   config_log_data = line.right(1);
                    break;
                }
                case 3:
                {
                    config_autolog = line.right(1);
                    break;
                }
                case 4:
                {
                    config_user_key = line.right(2);
                    break;
                }
                case 5:
                {
                    for (int i=5;i<line.size();i++)
                    {
                        config_login_hash.append( line[i] );
                    }
                    break;
                }
                case 6:
                {
                    for (int i=5;i<line.size();i++)
                    {
                        config_pswd_hash.append( line[i] );
                    }
                    break;
                }
                default:
                {
                    break;
                }
                }

                i++;
            }
            out[0]=config_log_data;
            out[1]=config_autolog;
            out[2]=config_user_key;
            out[3]=config_login_hash;
            out[4]=config_pswd_hash;
     }
    return out;
}


*/

