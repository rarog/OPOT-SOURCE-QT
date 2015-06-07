#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QProcess>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Try to translate the GUI to the current system locale
    loadLanguage(QLocale::system().name());
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_fastboot_clicked()
{
    QStringList commands;
    commands << QString("adb reboot fastboot");
    executeCommands(commands);
}

void MainWindow::on_reboot_clicked()
{
    QStringList commands;
    commands << QString("adb reboot");
    executeCommands(commands);
}

void MainWindow::on_recovery_clicked()
{
    QStringList commands;
    commands << QString("adb reboot recovery");
    executeCommands(commands);
}

void MainWindow::on_rebootfastboot_clicked()
{
    QStringList commands;
    commands << QString("fastboot reboot");
    executeCommands(commands);
}

void MainWindow::on_devices_clicked()
{
    QStringList commands;
    commands << QString("adb devices");
    executeCommands(commands);
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
    QStringList commands;
    if (QMessageBox::Yes == QMessageBox(QMessageBox::Information, tr("Attention"), tr("Do you want to make a file-only backup? This will copy all files from your device to the computer. By pressing 'NO' the tool will make a normal backup."), QMessageBox::Yes|QMessageBox::No).exec())
    {
        commands << QString("adb pull /sdcard/0 /backup");
        executeCommands(commands);
    }

    QString filename = QFileDialog::getSaveFileName(
                this,
                tr("Save file"),
                QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
                tr("Backup file (*.ab)")
                );

    commands.clear();
    commands << QString("adb backup -all -apk -shared -f ") + filename;
    executeCommands(commands);
}
void MainWindow::on_actionGerman_triggered()
{
    loadLanguage("de_DE");
}

void MainWindow::on_actionSearch_for_updates_triggered()
{
    // TODO: current code isn't updating, it just tries to download a plattform indifferent file to desktop
    //  windows style. Following questions should be resolved:
    //  - should there be a differentiation between packages for different plattforms?
    //  - will there be a server script which would deliver an URL depending on submittet current version?
    //  - is an automatic download needed at all or would it be enough to just open the download page?
    //  If a download will still be necessary, something like this could be used: https://wiki.qt.io/Download_Data_from_URL
    #pragma message("TODO: MainWindow::on_actionSearch_for_updates_triggered needs reconception and rewrite")
    system("start powershell.exe Invoke-WebRequest 'http://p-devs.info/OPO/OPOT.zip' -OutFile $pwd'\\Desktop\\OPOT.zip'");
}

void MainWindow::on_root_clicked()
{    
    QStringList commands;
    // TODO: this should be determined dynamically via path search. Else a recompilation is needed for every new version.
    commands << QString("adb sideload SuperSUv2.46.zip");
    executeCommands(commands);
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

void MainWindow::on_actionEnglish_triggered()
{
    loadLanguage("en_EN");
}

/**
 * \brief Language loader
 * \param newLanguage Language string, usually in POSIX locale format
 *
 */
void MainWindow::loadLanguage(const QString &newLanguage)
{
    if(currentLanguage != newLanguage)
    {
        currentLanguage = newLanguage;
        QLocale locale = QLocale(currentLanguage);
        QLocale::setDefault(locale);

        // Remove old translator
        qApp->removeTranslator(&translator);

        // Load only, if translation does exist
        if(translator.load(QString(":/translations/OPOT_%1.qm").arg(currentLanguage)))
            qApp->installTranslator(&translator);
    }
}

/**
 * \brief Overwritten event handler
 * \param event QEvent
 *
 */
void MainWindow::changeEvent(QEvent* event)
{
    if(0 != event)
    {
        switch(event->type())
        {
        // Triggered, if a translator is loaded
        case QEvent::LanguageChange:
            ui->retranslateUi(this);
            break;
        default:
            break;
        }
    }

    QMainWindow::changeEvent(event);
}

/**
 * \brief Executes list of commands via QProcess. Stops on first error.
 * \param commands List of commands
 * \return Indicator if all commands were executed.
 */
bool MainWindow::executeCommands(const QStringList &commands)
{
    QProcess singleProcess;

    for (QString command : commands)
    {
        singleProcess.start(command);

        if (!singleProcess.waitForStarted())
            return false;

        while(singleProcess.state() != QProcess::NotRunning){
            singleProcess.waitForReadyRead();
            ui->plainTextEditConsoleOutput->setPlainText(ui->plainTextEditConsoleOutput->toPlainText() + QString(singleProcess.readAll()));
        }
    }
    return true;
}
