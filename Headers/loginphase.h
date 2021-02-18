#ifndef LOGINPHASE_H
#define LOGINPHASE_H
#include "logwin.h"
#include "regwin.h"
#include "pswdrmdwin.h"
#include "mainwin.h"

#include "window_init.h"
#include <QDebug>

class LoginPhase
{
public:
    LoginPhase();
    ~LoginPhase();
    void get_pointers();
    void logwin_show();
    /*
    static void creating_config (int log_data, int autolog,int key_int, QString login_text, QString pswd_text);
    static QString random_QString (int char_num);
    static QChar random_QChar ();
    static int random_int (int min, int max);
    static std::vector<QString> log_data_from_config();
*/
private:
    LogWin *ptr_login_phase_logwin;
    RegWin *ptr_login_phase_regwin;
    PswdRmdWin *ptr_login_phase_pswdrmd;
    MainWin *ptr_login_phase_mainwin;

    friend class Api_Process;
    friend class MainWin;
};

#endif // LOGINPHASE_H
