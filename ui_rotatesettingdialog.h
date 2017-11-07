/********************************************************************************
** Form generated from reading UI file 'rotatesettingdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROTATESETTINGDIALOG_H
#define UI_ROTATESETTINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RotateSettingDialog
{
public:
    QPushButton *pushButton;
    QLabel *label;
    QLabel *label_5;
    QPushButton *pushButton_1;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_0;

    void setupUi(QWidget *RotateSettingDialog)
    {
        if (RotateSettingDialog->objectName().isEmpty())
            RotateSettingDialog->setObjectName(QStringLiteral("RotateSettingDialog"));
        RotateSettingDialog->resize(640, 370);
        pushButton = new QPushButton(RotateSettingDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(510, 300, 121, 61));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(12);
        pushButton->setFont(font);
        label = new QLabel(RotateSettingDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(270, 40, 131, 61));
        QFont font1;
        font1.setFamily(QStringLiteral("Adobe Arabic"));
        font1.setPointSize(36);
        label->setFont(font1);
        label->setStyleSheet(QStringLiteral(""));
        label_5 = new QLabel(RotateSettingDialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 40, 261, 61));
        label_5->setFont(font1);
        label_5->setStyleSheet(QStringLiteral(""));
        pushButton_1 = new QPushButton(RotateSettingDialog);
        pushButton_1->setObjectName(QStringLiteral("pushButton_1"));
        pushButton_1->setGeometry(QRect(200, 160, 91, 51));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font2.setPointSize(14);
        pushButton_1->setFont(font2);
        pushButton_1->setStyleSheet(QLatin1String("QPushButton:checked{background-color: rgba(38, 166, 154,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton{background-color: rgba(84, 110, 122,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton:pressed{background-color: rgba(0, 77, 64,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton:disabled{background-color: rgba(0, 77, 64,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}"));
        pushButton_2 = new QPushButton(RotateSettingDialog);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(340, 160, 91, 51));
        pushButton_2->setFont(font2);
        pushButton_2->setStyleSheet(QLatin1String("QPushButton:checked{background-color: rgba(38, 166, 154,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton{background-color: rgba(84, 110, 122,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton:pressed{background-color: rgba(0, 77, 64,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton:disabled{background-color: rgba(0, 77, 64,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}"));
        pushButton_3 = new QPushButton(RotateSettingDialog);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(480, 160, 91, 51));
        pushButton_3->setFont(font2);
        pushButton_3->setStyleSheet(QLatin1String("QPushButton:checked{background-color: rgba(38, 166, 154,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton{background-color: rgba(84, 110, 122,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton:pressed{background-color: rgba(0, 77, 64,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton:disabled{background-color: rgba(0, 77, 64,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}"));
        pushButton_0 = new QPushButton(RotateSettingDialog);
        pushButton_0->setObjectName(QStringLiteral("pushButton_0"));
        pushButton_0->setGeometry(QRect(60, 160, 91, 51));
        pushButton_0->setFont(font2);
        pushButton_0->setStyleSheet(QLatin1String("QPushButton:checked{background-color: rgba(38, 166, 154,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton{background-color: rgba(84, 110, 122,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton:pressed{background-color: rgba(0, 77, 64,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton:disabled{background-color: rgba(0, 77, 64,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}"));

        retranslateUi(RotateSettingDialog);

        QMetaObject::connectSlotsByName(RotateSettingDialog);
    } // setupUi

    void retranslateUi(QWidget *RotateSettingDialog)
    {
        RotateSettingDialog->setWindowTitle(QApplication::translate("RotateSettingDialog", "Form", Q_NULLPTR));
        pushButton->setText(QApplication::translate("RotateSettingDialog", "\347\241\256\345\256\232", Q_NULLPTR));
        label->setText(QString());
        label_5->setText(QApplication::translate("RotateSettingDialog", "\351\241\272\346\227\266\351\222\210\346\227\213\350\275\254\357\274\232", Q_NULLPTR));
        pushButton_1->setText(QApplication::translate("RotateSettingDialog", "90", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("RotateSettingDialog", "180", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("RotateSettingDialog", "270", Q_NULLPTR));
        pushButton_0->setText(QApplication::translate("RotateSettingDialog", "0", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RotateSettingDialog: public Ui_RotateSettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROTATESETTINGDIALOG_H
