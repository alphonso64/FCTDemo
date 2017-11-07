#ifndef ROTATESETTINGDIALOG_H
#define ROTATESETTINGDIALOG_H

#include <QDialog>
#include <QButtonGroup>
namespace Ui {
class RotateSettingDialog;
}

class RotateSettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RotateSettingDialog(QWidget *parent = 0);
    ~RotateSettingDialog();
    QButtonGroup group;
    int key;
    int value;
private slots:
    void camSelect(int id);

    void on_pushButton_clicked();

private:
    Ui::RotateSettingDialog *ui;
};

#endif // ROTATESETTINGDIALOG_H
