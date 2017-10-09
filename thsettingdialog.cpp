#include "thsettingdialog.h"
#include "ui_thsettingdialog.h"

ThSettingDialog::ThSettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThSettingDialog)
{
    ui->setupUi(this);
    ui->label->setText(QString::number(60));
    ui->horizontalSlider->setMaximum(255);
    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setValue(60);

    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));
}

void ThSettingDialog::setValue(int value)
{
    ui->label->setText(QString::number(value));
}

ThSettingDialog::~ThSettingDialog()
{
    delete ui;
}

void ThSettingDialog::on_pushButton_clicked()
{
    this->done(ui->horizontalSlider->value());
}
