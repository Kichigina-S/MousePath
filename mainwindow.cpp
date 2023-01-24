#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    settings = new QSettings("Svetlana", "MouseTimerSettings", this);
    loadSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::saveFile(int lenght)
{
    QDateTime dateTimeToday = QDateTime::currentDateTimeUtc();

    QString fileName = dateTimeToday.toString("dd.MM.yy_hh.mm.ss") + ".txt";
    QFile out ("C:/Users/79511/Documents/MouthPath/" + fileName);
    if (!out.open(QFileDevice::WriteOnly))
    {
        QMessageBox::warning(this, tr("War"),
                             tr("Cannot write file %1")
                             .arg(out.fileName()));
        return false;
    }

    QTextStream stream (&out);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    stream << lenght;
    out.close();

    QApplication::restoreOverrideCursor();
    ui->statusbar->showMessage("Succ");
    return true;
}

void MainWindow::updateFileds()
{
    ui->label_Path->setText("0");
    ui->label_X->setText("0");
    ui->label_Y->setText("0");
    lenght_coursor = 0;
}

void MainWindow::setTimer(QString a)
{
    ui->label_Time->setText(a);
    mSecondsToEnd = ui->label_Time->text().toInt();
    saveSettings(mSecondsToEnd);
}

void MainWindow::slotTimerAlarm()
{
    mSecondsToEnd--;
    if (mSecondsToEnd >= 0)
    {
        QString time = QString::number(mSecondsToEnd);
        ui->label_Time->setText(time);
        centralWidget()->setMouseTracking(true);
        this->setMouseTracking(true);

    }
    else
    {
        timer->stop();
        centralWidget()->setMouseTracking(false);
        this->setMouseTracking(false);
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    if (    event->pos().x() >= 30 &&
            event->pos().x() <= 330 &&
            event->pos().y() >= 30 &&
            event->pos().y() <= 180)
    {
        ui->label_X->setText(QString::number(event->pos().x()));
        ui->label_Y->setText(QString::number(event->pos().y()));
        lenght_coursor++;
        ui->label_Path->setText(QString::number(lenght_coursor));
    }
}

void MainWindow::saveSettings(int a)
{
    settings->setValue("Timer", a);
}

void MainWindow::loadSettings()
{
    ui->label_Time->setText((settings->value("Timer", 30)).toString());
}

void MainWindow::on_action_triggered()
{
    saveFile(ui->label_Path->text().toInt());
}

void MainWindow::on_action_2_triggered()
{
    dialog = new setTimerDialog;
    dialog->show();
    connect(dialog, &setTimerDialog::onSendData, this, &MainWindow::setTimer);
}


void MainWindow::on_action_3_triggered()
{
    if (ui->label_Time->text().toInt() == 0)
    {
        QMessageBox::warning(this, tr("War"),
                             tr("Задайте время > 0"));
        return;
    }

    if (ui->label_Path->text().toInt() > 0)
    {
        saveFile(ui->label_Path->text().toInt());
        updateFileds();
    }

    mSecondsToEnd = ui->label_Time->text().toInt();
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
    timer->start(1000);
}

