#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qmenubar.h"
#include "settimerdialog.h"
#include <QLabel>
#include <QMainWindow>
#include <QWidget>
#include <QMouseEvent>
#include <QTime>
#include <QTimer>
#include <QFile>
#include <QMessageBox>
#include <QDateTime>
#include <QSettings>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void saveSettings(int);
    void loadSettings();

private:
    Ui::MainWindow *ui;

    int lenght_coursor = 0;
    QMenuBar save;
    QTimer *timer;
    int mSecondsToEnd;
    QSettings* settings;
    setTimerDialog *dialog;

protected:
    virtual void mouseMoveEvent(QMouseEvent* event);
    bool saveFile(int lenght);
    void updateFileds();

private slots:
    void slotTimerAlarm();
    void on_action_triggered();
    void on_action_2_triggered();

    void on_action_3_triggered();

public slots:
    void setTimer(QString);
};
#endif // MAINWINDOW_H
