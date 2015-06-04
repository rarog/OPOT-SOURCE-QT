#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include "mainwindowger.h"
#include <QMainWindow>

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
    void on_fastboot_clicked();

    void on_reboot_clicked();

    void on_recovery_clicked();

    void on_rebootfastboot_clicked();

    void on_devices_clicked();

    void on_oemunlock_clicked();

    void on_backup_clicked();

    void on_actionGerman_triggered();

    void on_actionSearch_for_updates_triggered();

    void on_root_clicked();

    void on_flashrom_clicked();

private:
    Ui::MainWindow *ui;
   // MainWindowGer mainwindowger;

};

#endif // MAINWINDOW_H
