#include "../Headers/loginphase.h"
#include "../Headers/logs.h"
#include "../Headers/fragile.h"
#include "../Headers/hash.h"
#include <QMessageBox>
#include <QFile>
#include <QtSql>

LoginPhase::LoginPhase()
{
    qDebug("LoginPhase Tworze");
    ptr_login_phase_logwin = new LogWin;
    ptr_login_phase_regwin = new RegWin;
    ptr_login_phase_pswdrmd = new PswdRmdWin;
    get_pointers();
}

LoginPhase::~LoginPhase()
{
    qDebug("LoginPhase Niszcze");
}

void LoginPhase::get_pointers()
{
    ptr_login_phase_logwin->get_pointers(ptr_login_phase_regwin, ptr_login_phase_pswdrmd);
    ptr_login_phase_regwin->get_pointers(ptr_login_phase_logwin, ptr_login_phase_pswdrmd);
    ptr_login_phase_pswdrmd->get_pointers(ptr_login_phase_logwin, ptr_login_phase_regwin);
}

void LoginPhase::logwin_show()
{
    ptr_login_phase_logwin->show();
}
