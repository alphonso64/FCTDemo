#ifndef THSETTINGDIALOG_H
#define THSETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class ThSettingDialog;
}

class ThSettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ThSettingDialog(QWidget *parent = 0);
    ~ThSettingDialog();

    int key;
    QString filePath;

private slots:
    void setValue(int value);
    void on_pushButton_clicked();

private:
    Ui::ThSettingDialog *ui;
};

#endif // THSETTINGDIALOG_H
