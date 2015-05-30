#include "mainwindowger.h"
#include "ui_mainwindowger.h"

MainWindowGer::MainWindowGer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowGer)
{
    ui->setupUi(this);
}

MainWindowGer::~MainWindowGer()
{
    delete ui;
}
