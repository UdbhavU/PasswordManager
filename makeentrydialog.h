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
    explicit makeEntryDialog(QWidget *parent = nullptr, QString tkey="");
    ~makeEntryDialog();

private slots:
    void on_commandLinkButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::makeEntryDialog *ui;
    QString key;
};

#endif // MAKEENTRYDIALOG_H
