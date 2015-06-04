#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include "mainwindowger.h"
#include <QMainWindow>
#include <QTranslator>

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

    void on_actionEnglish_triggered();

private:
    Ui::MainWindow *ui;
    QString currentLanguage;
    QTranslator translator;

    void loadLanguage(const QString &newLanguage);

protected:
    void changeEvent(QEvent*);
};

#endif // MAINWINDOW_H
