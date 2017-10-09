/********************************************************************************
** Form generated from reading UI file 'thsettingdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_THSETTINGDIALOG_H
#define UI_THSETTINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>

QT_BEGIN_NAMESPACE

class Ui_ThSettingDialog
{
public:
    QSlider *horizontalSlider;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pushButton;
    QLabel *label_4;

    void setupUi(QDialog *ThSettingDialog)
    {
        if (ThSettingDialog->objectName().isEmpty())
            ThSettingDialog->setObjectName(QStringLiteral("ThSettingDialog"));
        ThSettingDialog->resize(640, 370);
        horizontalSlider = new QSlider(ThSettingDialog);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(80, 150, 471, 61));
        horizontalSlider->setOrientation(Qt::Horizontal);
        label = new QLabel(ThSettingDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(290, 40, 131, 61));
        QFont font;
        font.setFamily(QStringLiteral("Adobe Arabic"));
        font.setPointSize(36);
        label->setFont(font);
        label->setStyleSheet(QStringLiteral(""));
        label_2 = new QLabel(ThSettingDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 150, 51, 61));
        label_2->setFont(font);
        label_2->setStyleSheet(QStringLiteral(""));
        label_3 = new QLabel(ThSettingDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(570, 150, 61, 61));
        label_3->setFont(font);
        label_3->setStyleSheet(QStringLiteral(""));
        pushButton = new QPushButton(ThSettingDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(510, 300, 121, 61));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(12);
        pushButton->setFont(font1);
        label_4 = new QLabel(ThSettingDialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(170, 40, 121, 61));
        label_4->setFont(font);
        label_4->setStyleSheet(QStringLiteral(""));

        retranslateUi(ThSettingDialog);

        QMetaObject::connectSlotsByName(ThSettingDialog);
    } // setupUi

    void retranslateUi(QDialog *ThSettingDialog)
    {
        ThSettingDialog->setWindowTitle(QApplication::translate("ThSettingDialog", "Dialog", Q_NULLPTR));
        label->setText(QString());
        label_2->setText(QApplication::translate("ThSettingDialog", "0", Q_NULLPTR));
        label_3->setText(QApplication::translate("ThSettingDialog", "255", Q_NULLPTR));
        pushButton->setText(QApplication::translate("ThSettingDialog", "\347\241\256\345\256\232", Q_NULLPTR));
        label_4->setText(QApplication::translate("ThSettingDialog", "\351\230\210\345\200\274\357\274\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ThSettingDialog: public Ui_ThSettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_THSETTINGDIALOG_H
