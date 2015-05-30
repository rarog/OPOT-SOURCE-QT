#ifndef MAINWINDOWGER_H
#define MAINWINDOWGER_H

#include <QMainWindow>

namespace Ui {
class MainWindowGer;
}

class MainWindowGer : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowGer(QWidget *parent = 0);
    ~MainWindowGer();

private:
    Ui::MainWindowGer *ui;
};

#endif // MAINWINDOWGER_H
