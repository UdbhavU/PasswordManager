#ifndef MAKEENTRYDIALOG_H
#define MAKEENTRYDIALOG_H

#include <QDialog>

namespace Ui {
class makeEntryDialog;
}

class makeEntryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit makeEntryDialog(QWidget *parent = nullptr);
    ~makeEntryDialog();

private slots:
    void on_commandLinkButton_clicked();

private:
    Ui::makeEntryDialog *ui;
};

#endif // MAKEENTRYDIALOG_H
