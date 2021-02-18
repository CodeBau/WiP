#ifndef ACCONT_DATA_CHANGE_H
#define ACCONT_DATA_CHANGE_H

#include <QMainWindow>
#include "logwin.h"
#include "regwin.h"
#include "window_init.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Accont_Data_Change; }
QT_END_NAMESPACE

class Accont_Data_Change : public QMainWindow
{
    Q_OBJECT
public:
    Accont_Data_Change(QWidget *parent = nullptr);
    ~Accont_Data_Change();

private slots:

private:
    Ui::Accont_Data_Change *ui;
};

#endif // ACCONT_DATA_CHANGE_H

