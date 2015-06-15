#include "fileoverview.h"
#include "ui_fileoverview.h"

FileOverview::FileOverview(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileOverview)
{
    ui->setupUi(this);
}

FileOverview::~FileOverview()
{
    delete ui;
}
