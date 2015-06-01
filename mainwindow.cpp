#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>
#include <windows.h>
#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_fastboot_clicked()
{
    system("adb reboot fastboot");
}

void MainWindow::on_reboot_clicked()
{
    system("adb reboot");
}

void MainWindow::on_recovery_clicked()
{
    system("adb reboot recovery");
}

void MainWindow::on_rebootfastboot_clicked()
{
    system("fastboot reboot");
}

void MainWindow::on_devices_clicked()
{
    system("start cmd.exe /k adb devices");
}

void MainWindow::on_forumlink_linkActivated(const QString &link)
{
    system("explorer.exe https://forums.oneplus.net/threads/oneplus-one-toolkit-new.311774/");
}

void MainWindow::on_websitelink_linkActivated(const QString &link)
{
    system("explorer.exe http://p-devs.info/");
}

void MainWindow::on_oemunlock_clicked()
{
      if (QMessageBox::Yes == QMessageBox(QMessageBox::Information, "Warning", "This will delete all files on your device. Are you sure you want to continue?", QMessageBox::Yes|QMessageBox::No).exec())
      {
      system("fastboot oem unlock");
      }
}
const char *QString2char(QString str)
{
    QByteArray byteArray;
    const char *cstr;

    byteArray = str.toUtf8();
    cstr = byteArray.constData();

    return(cstr);
}
void MainWindow::on_backup_clicked()
{
    if (QMessageBox::Yes == QMessageBox(QMessageBox::Information, "Attention", "Do you want to make a file-only backup? This will copy all files from your device to the computer. By pressing 'NO' the tool will make a normal backup.", QMessageBox::Yes|QMessageBox::No).exec())
          {
          system("adb pull /sdcard/0 /backup");
          }

    QString filename = QFileDialog::getSaveFileName(
                this,
                tr("Save file"),
                "C://",
                "Backup file (*.ab)"
                );

    const char *char_data;
    char_data = QString2char(filename);

    system("start cmd.exe /k adb backup -all -apk -shared -f "+ *char_data);

}
void MainWindow::on_actionGerman_triggered()
{
    //mainwindowger.show();

}


void MainWindow::on_actionSearch_for_updates_triggered()
{
    system("start powershell.exe Invoke-WebRequest 'http://p-devs.info/OPO/OPOT.zip' -OutFile $pwd'\\Desktop\\OPOT.zip'");
}

void MainWindow::on_root_clicked()
{
    system("adb reboot fastboot");
    system("fastboot flash recovery SuperSUv2.46.zip");
    system("fastboot reboot");
}

void MainWindow::on_flashrom_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open .ZIP"),
                "C://",
                "ROM (*.zip)"
                );

    const char *char_data;
    char_data = QString2char(filename);

    system("fastboot flash recovery "+*char_data);
    system("fastboot reboot");
}
