#ifndef SETTIMERDIALOG_H
#define SETTIMERDIALOG_H

#include "qabstractbutton.h"
#include <QDialog>

namespace Ui {
class setTimerDialog;
}

class setTimerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit setTimerDialog(QWidget *parent = nullptr);
    ~setTimerDialog();

private:
    Ui::setTimerDialog *ui;

signals:
    void onSendData(QString);

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);
};

#endif // SETTIMERDIALOG_H
