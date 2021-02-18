#include "../Headers/accont_data_change.h"
#include "ui_accont_data_change.h"


//TODO dodac menu/ustawienia konta -> zmiana maila ze sprawdzeniem, zmiana hasla ze sprawdzeniem (generowanie nowego klucza),

Accont_Data_Change::Accont_Data_Change(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Accont_Data_Change)
{
    qDebug("Accont_Data_Change Tworze");

    this->setAttribute( Qt::WA_DeleteOnClose );
    ui->setupUi(this);
}

Accont_Data_Change::~Accont_Data_Change()
{
    qDebug("Accont_Data_Change Niszcze");
    delete ui;
}


