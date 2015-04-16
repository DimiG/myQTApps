#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QByteArray>
#include <QTextBrowser>
#include <QDebug>
#include <QFileDialog>
#include <QComboBox>
#include <QMessageBox>
#include <QStandardPaths>
#include <QMovie>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void executeCommand();
    void setSource();
    void setDestination();
    void outputCommand();
    void on_processCancel();
    void on_processExit(int exitCode, QProcess::ExitStatus exitStatus);
    void setMP4();
    void setDV();
    void setMOV();
    void setMP3();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    QProcess commandProcess;
    QString videoFolder;
    QMovie *indicator;

};

#endif // MAINWINDOW_H
