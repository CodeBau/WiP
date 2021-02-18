#ifndef API_PROCESS_H
#define API_PROCESS_H

#include <QTextStream>
#include <QFile>
#include <QMessageBox>
#include "window_init.h"

class Api_Process
{
public:
    enum InitMode {mode_normal=1,mode_log_data=2,mode_autolog=3};
    InitMode my_init_mode;

    Api_Process();
    ~Api_Process();
    void start();
    void init();
    void autolog_from_config();
    void autolog_fail_LogWin_show();
    void warning_msg(QString text, QString title);
    InitMode checking_config();

private:
    //TODO 6 ptrs name ptr_xxx i male litery same
    LoginPhase *init_login_phase;
    MainWin *init_mainwin;
};

#endif // API_PROCESS_H
