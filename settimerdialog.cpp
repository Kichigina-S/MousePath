#include "settimerdialog.h"
#include "ui_settimerdialog.h"

setTimerDialog::setTimerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setTimerDialog)
{
    ui->setupUi(this);

}


setTimerDialog::~setTimerDialog()
{
    delete ui;
}

void setTimerDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    emit onSendData(ui->textEdit_setTimer->toPlainText());
}

