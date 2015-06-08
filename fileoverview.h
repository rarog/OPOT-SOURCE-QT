#ifndef FILEOVERVIEW_H
#define FILEOVERVIEW_H

#include <QDialog>

namespace Ui {
class FileOverview;
}

class FileOverview : public QDialog
{
    Q_OBJECT

public:
    explicit FileOverview(QWidget *parent = 0);
    ~FileOverview();

private:
    Ui::FileOverview *ui;
};

#endif // FILEOVERVIEW_H
