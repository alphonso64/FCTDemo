/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "cuslabel.h"
#include "paintlabel.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *viewfinderLayout_;
    QVBoxLayout *viewfinderLayout;
    CusLabel *label_2;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_7;
    PaintLabel *label;
    QHBoxLayout *horizontalLayout_8;
    QTableWidget *tableWidget;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QWidget *widget_2;
    QGroupBox *groupBox;
    QPushButton *camButton;
    QPushButton *picButton;
    QPushButton *calibrationButton;
    QPushButton *camButton_2;
    QGroupBox *groupBox_2;
    QPushButton *loadFileButton;
    QPushButton *saveFileButton;
    QGroupBox *groupBox_3;
    QPushButton *addButton;
    QPushButton *delButton;
    QPushButton *matchButton;
    QPushButton *recButton;
    QPushButton *saveButton;
    QPushButton *savePicButton;
    QPushButton *addTransButton;
    QGroupBox *groupBox_4;
    QPushButton *captureButton;
    QComboBox *comboBox;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1320, 658);
        MainWindow->setMinimumSize(QSize(800, 450));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        viewfinderLayout_ = new QVBoxLayout();
        viewfinderLayout_->setSpacing(6);
        viewfinderLayout_->setObjectName(QStringLiteral("viewfinderLayout_"));
        viewfinderLayout_->setContentsMargins(-1, 0, -1, 0);
        viewfinderLayout = new QVBoxLayout();
        viewfinderLayout->setSpacing(6);
        viewfinderLayout->setObjectName(QStringLiteral("viewfinderLayout"));
        label_2 = new CusLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        viewfinderLayout->addWidget(label_2);


        viewfinderLayout_->addLayout(viewfinderLayout);

        viewfinderLayout_->setStretch(0, 2);

        horizontalLayout_2->addLayout(viewfinderLayout_);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label = new PaintLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));

        horizontalLayout_7->addWidget(label);


        verticalLayout_5->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        tableWidget = new QTableWidget(centralWidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        horizontalLayout_8->addWidget(tableWidget);


        verticalLayout_5->addLayout(horizontalLayout_8);

        verticalLayout_5->setStretch(0, 1);
        verticalLayout_5->setStretch(1, 2);

        horizontalLayout_2->addLayout(verticalLayout_5);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(1);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(3);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, -1, -1, 5);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, -1, 0);
        widget_2 = new QWidget(centralWidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        groupBox = new QGroupBox(widget_2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 0, 121, 131));
        groupBox->setStyleSheet(QStringLiteral(""));
        camButton = new QPushButton(groupBox);
        camButton->setObjectName(QStringLiteral("camButton"));
        camButton->setGeometry(QRect(15, 10, 41, 31));
        camButton->setFocusPolicy(Qt::ClickFocus);
        camButton->setStyleSheet(QLatin1String("QPushButton:checked{background-color: rgba(38, 166, 154,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton{background-color: rgba(84, 110, 122,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton:pressed{background-color: rgba(0, 77, 64,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton:disabled{background-color: rgba(0, 77, 64,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}"));
        picButton = new QPushButton(groupBox);
        picButton->setObjectName(QStringLiteral("picButton"));
        picButton->setGeometry(QRect(15, 50, 91, 31));
        picButton->setStyleSheet(QLatin1String("QPushButton:checked{background-color: rgba(38, 166, 154,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton{background-color: rgba(84, 110, 122,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton:pressed{background-color: rgba(0, 77, 64,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton:disabled{background-color: rgba(0, 77, 64,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}"));
        calibrationButton = new QPushButton(groupBox);
        calibrationButton->setObjectName(QStringLiteral("calibrationButton"));
        calibrationButton->setGeometry(QRect(15, 90, 91, 31));
        calibrationButton->setStyleSheet(QLatin1String("QPushButton:checked{background-color: rgba(38, 166, 154,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton{background-color: rgba(84, 110, 122,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton:pressed{background-color: rgba(0, 77, 64,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton:disabled{background-color: rgba(0, 77, 64,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}"));
        camButton_2 = new QPushButton(groupBox);
        camButton_2->setObjectName(QStringLiteral("camButton_2"));
        camButton_2->setGeometry(QRect(65, 10, 41, 31));
        camButton_2->setFocusPolicy(Qt::ClickFocus);
        camButton_2->setStyleSheet(QLatin1String("QPushButton:checked{background-color: rgba(38, 166, 154,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton{background-color: rgba(84, 110, 122,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton:pressed{background-color: rgba(0, 77, 64,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton:disabled{background-color: rgba(0, 77, 64,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}"));
        groupBox_2 = new QGroupBox(widget_2);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 140, 120, 91));
        loadFileButton = new QPushButton(groupBox_2);
        loadFileButton->setObjectName(QStringLiteral("loadFileButton"));
        loadFileButton->setGeometry(QRect(15, 10, 91, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        loadFileButton->setFont(font);
        saveFileButton = new QPushButton(groupBox_2);
        saveFileButton->setObjectName(QStringLiteral("saveFileButton"));
        saveFileButton->setGeometry(QRect(15, 50, 91, 31));
        saveFileButton->setFont(font);
        groupBox_3 = new QGroupBox(widget_2);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 240, 120, 291));
        addButton = new QPushButton(groupBox_3);
        addButton->setObjectName(QStringLiteral("addButton"));
        addButton->setGeometry(QRect(15, 10, 91, 31));
        addButton->setFont(font);
        addButton->setStyleSheet(QLatin1String("QPushButton:checked{background-color: rgba(38, 166, 154,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton{background-color: rgba(84, 110, 122,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton:pressed{background-color: rgba(0, 77, 64,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}"));
        delButton = new QPushButton(groupBox_3);
        delButton->setObjectName(QStringLiteral("delButton"));
        delButton->setGeometry(QRect(15, 90, 91, 31));
        delButton->setFont(font);
        matchButton = new QPushButton(groupBox_3);
        matchButton->setObjectName(QStringLiteral("matchButton"));
        matchButton->setGeometry(QRect(15, 130, 91, 31));
        matchButton->setFont(font);
        recButton = new QPushButton(groupBox_3);
        recButton->setObjectName(QStringLiteral("recButton"));
        recButton->setGeometry(QRect(15, 170, 91, 31));
        recButton->setFont(font);
        saveButton = new QPushButton(groupBox_3);
        saveButton->setObjectName(QStringLiteral("saveButton"));
        saveButton->setGeometry(QRect(15, 210, 91, 31));
        saveButton->setFont(font);
        savePicButton = new QPushButton(groupBox_3);
        savePicButton->setObjectName(QStringLiteral("savePicButton"));
        savePicButton->setGeometry(QRect(15, 250, 91, 31));
        savePicButton->setFont(font);
        addTransButton = new QPushButton(groupBox_3);
        addTransButton->setObjectName(QStringLiteral("addTransButton"));
        addTransButton->setGeometry(QRect(15, 50, 91, 31));
        addTransButton->setFont(font);
        addTransButton->setStyleSheet(QLatin1String("QPushButton:checked{background-color: rgba(38, 166, 154,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton{background-color: rgba(84, 110, 122,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton:pressed{background-color: rgba(0, 77, 64,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}"));
        groupBox_4 = new QGroupBox(widget_2);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 540, 120, 61));
        captureButton = new QPushButton(groupBox_4);
        captureButton->setObjectName(QStringLiteral("captureButton"));
        captureButton->setGeometry(QRect(10, 10, 101, 41));
        captureButton->setFont(font);
        comboBox = new QComboBox(widget_2);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(30, 530, 81, 20));

        verticalLayout->addWidget(widget_2);


        horizontalLayout_3->addLayout(verticalLayout);

        horizontalLayout_3->setStretch(0, 1);

        verticalLayout_7->addLayout(horizontalLayout_3);

        verticalLayout_7->setStretch(0, 1);

        horizontalLayout_2->addLayout(verticalLayout_7);

        horizontalLayout_2->setStretch(0, 6);
        horizontalLayout_2->setStretch(1, 2);
        horizontalLayout_2->setStretch(2, 1);

        horizontalLayout->addLayout(horizontalLayout_2);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label_2->setText(QString());
        label->setText(QString());
        groupBox->setTitle(QString());
        camButton->setText(QApplication::translate("MainWindow", "CAM1", Q_NULLPTR));
        picButton->setText(QApplication::translate("MainWindow", "\345\233\276\347\211\207", Q_NULLPTR));
        calibrationButton->setText(QApplication::translate("MainWindow", "\346\240\241\345\207\206", Q_NULLPTR));
        camButton_2->setText(QApplication::translate("MainWindow", "CAM2", Q_NULLPTR));
        groupBox_2->setTitle(QString());
        loadFileButton->setText(QApplication::translate("MainWindow", "\350\275\275\345\205\245\346\265\201\347\250\213\346\226\207\344\273\266", Q_NULLPTR));
        saveFileButton->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\346\265\201\347\250\213\346\226\207\344\273\266", Q_NULLPTR));
        groupBox_3->setTitle(QString());
        addButton->setText(QApplication::translate("MainWindow", "\346\241\206\351\200\211\345\214\272\345\237\237", Q_NULLPTR));
        delButton->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244", Q_NULLPTR));
        matchButton->setText(QApplication::translate("MainWindow", "\345\214\271\351\205\215", Q_NULLPTR));
        recButton->setText(QApplication::translate("MainWindow", "\350\257\206\345\210\253", Q_NULLPTR));
        saveButton->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\346\250\241\346\235\277", Q_NULLPTR));
        savePicButton->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\345\233\276\347\211\207", Q_NULLPTR));
        addTransButton->setText(QApplication::translate("MainWindow", "\346\241\206\351\200\211\344\274\240\350\276\223\345\214\272\345\237\237", Q_NULLPTR));
        groupBox_4->setTitle(QString());
        captureButton->setText(QApplication::translate("MainWindow", "\346\243\200\346\265\213", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
