#ifndef CLOCKWINDOW_H
#define CLOCKWINDOW_H

#include <QMainWindow>

namespace Ui {
class ClockWindow;
}

class ClockWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClockWindow(QWidget *parent = 0);
    ~ClockWindow();
private slots:
    void showTime();

private:
    Ui::ClockWindow *ui;
};

#endif // CLOCKWINDOW_H
