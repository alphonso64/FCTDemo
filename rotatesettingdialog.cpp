#include "rotatesettingdialog.h"
#include "ui_rotatesettingdialog.h"
#include <QDebug>
RotateSettingDialog::RotateSettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RotateSettingDialog)
{
    ui->setupUi(this);


    ui->pushButton_0->setCheckable(true);
    ui->pushButton_1->setCheckable(true);
    ui->pushButton_2->setCheckable(true);
    ui->pushButton_3->setCheckable(true);

    group.addButton(ui->pushButton_0,0);
    group.addButton(ui->pushButton_1,1);
    group.addButton(ui->pushButton_2,2);
    group.addButton(ui->pushButton_3,3);

    ui->pushButton_0->setEnabled(true);
    ui->pushButton_1->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);

    ui->pushButton_0->setChecked(true);
    value = 0;
    ui->label->setText(QString::number(value));
    connect(&group,SIGNAL(buttonClicked(int)),this,SLOT(camSelect(int)));
}

RotateSettingDialog::~RotateSettingDialog()
{
    delete ui;
}


void RotateSettingDialog::camSelect(int value)
{
    this->value = value*90;
    qDebug()<<this->value;
    ui->label->setText(QString::number(this->value));
}

void RotateSettingDialog::on_pushButton_clicked()
{
    this->done(value);
}
