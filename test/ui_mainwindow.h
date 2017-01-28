/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
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
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbout;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *cmbDevicesComboBox;
    QPushButton *btnRefresh;
    QLabel *label_2;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnRefreshData;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QDateTimeEdit *dateTimeEditLocal;
    QLabel *label_5;
    QDateTimeEdit *dateTimeEditUtc;
    QPushButton *btnGetDataAndTime;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_7;
    QDateTimeEdit *dateTimeEditSet;
    QPushButton *btsSetDateAndTime;
    QLabel *label_9;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_8;
    QLineEdit *txtUserName;
    QLabel *label_10;
    QLineEdit *txtPassword;
    QPushButton *setUsernamePass;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuFile;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(616, 547);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        cmbDevicesComboBox = new QComboBox(centralWidget);
        cmbDevicesComboBox->setObjectName(QStringLiteral("cmbDevicesComboBox"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cmbDevicesComboBox->sizePolicy().hasHeightForWidth());
        cmbDevicesComboBox->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(cmbDevicesComboBox);

        btnRefresh = new QPushButton(centralWidget);
        btnRefresh->setObjectName(QStringLiteral("btnRefresh"));

        horizontalLayout->addWidget(btnRefresh);


        gridLayout->addLayout(horizontalLayout, 3, 0, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 7, 0, 1, 1);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 12, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        btnRefreshData = new QPushButton(centralWidget);
        btnRefreshData->setObjectName(QStringLiteral("btnRefreshData"));

        horizontalLayout_3->addWidget(btnRefreshData);


        gridLayout->addLayout(horizontalLayout_3, 13, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_2->addWidget(label_4);

        dateTimeEditLocal = new QDateTimeEdit(centralWidget);
        dateTimeEditLocal->setObjectName(QStringLiteral("dateTimeEditLocal"));
        dateTimeEditLocal->setEnabled(true);
        sizePolicy.setHeightForWidth(dateTimeEditLocal->sizePolicy().hasHeightForWidth());
        dateTimeEditLocal->setSizePolicy(sizePolicy);
        dateTimeEditLocal->setReadOnly(true);

        horizontalLayout_2->addWidget(dateTimeEditLocal);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_2->addWidget(label_5);

        dateTimeEditUtc = new QDateTimeEdit(centralWidget);
        dateTimeEditUtc->setObjectName(QStringLiteral("dateTimeEditUtc"));
        dateTimeEditUtc->setEnabled(true);
        sizePolicy.setHeightForWidth(dateTimeEditUtc->sizePolicy().hasHeightForWidth());
        dateTimeEditUtc->setSizePolicy(sizePolicy);
        dateTimeEditUtc->setReadOnly(true);
        dateTimeEditUtc->setCalendarPopup(false);
        dateTimeEditUtc->setTimeSpec(Qt::UTC);

        horizontalLayout_2->addWidget(dateTimeEditUtc);

        btnGetDataAndTime = new QPushButton(centralWidget);
        btnGetDataAndTime->setObjectName(QStringLiteral("btnGetDataAndTime"));

        horizontalLayout_2->addWidget(btnGetDataAndTime);


        gridLayout->addLayout(horizontalLayout_2, 8, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_4->addWidget(label_7);

        dateTimeEditSet = new QDateTimeEdit(centralWidget);
        dateTimeEditSet->setObjectName(QStringLiteral("dateTimeEditSet"));
        sizePolicy.setHeightForWidth(dateTimeEditSet->sizePolicy().hasHeightForWidth());
        dateTimeEditSet->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(dateTimeEditSet);

        btsSetDateAndTime = new QPushButton(centralWidget);
        btsSetDateAndTime->setObjectName(QStringLiteral("btsSetDateAndTime"));

        horizontalLayout_4->addWidget(btsSetDateAndTime);


        gridLayout->addLayout(horizontalLayout_4, 9, 0, 1, 1);

        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 5, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_5->addWidget(label_8);

        txtUserName = new QLineEdit(centralWidget);
        txtUserName->setObjectName(QStringLiteral("txtUserName"));

        horizontalLayout_5->addWidget(txtUserName);

        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_5->addWidget(label_10);

        txtPassword = new QLineEdit(centralWidget);
        txtPassword->setObjectName(QStringLiteral("txtPassword"));

        horizontalLayout_5->addWidget(txtPassword);

        setUsernamePass = new QPushButton(centralWidget);
        setUsernamePass->setObjectName(QStringLiteral("setUsernamePass"));

        horizontalLayout_5->addWidget(setUsernamePass);


        gridLayout->addLayout(horizontalLayout_5, 6, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 616, 19));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionAbout);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0));
        label->setText(QApplication::translate("MainWindow", "Devices List:", 0));
        btnRefresh->setText(QApplication::translate("MainWindow", "Refresh", 0));
        label_2->setText(QApplication::translate("MainWindow", "Date and Time:", 0));
        label_6->setText(QApplication::translate("MainWindow", "Control:", 0));
        label_3->setText(QApplication::translate("MainWindow", "Put a break point in pointed place in btn  \"on refresh data\" slot to see device data.", 0));
        btnRefreshData->setText(QApplication::translate("MainWindow", "Refresh Data", 0));
        label_4->setText(QApplication::translate("MainWindow", "Local:", 0));
        label_5->setText(QApplication::translate("MainWindow", "Utc:", 0));
        btnGetDataAndTime->setText(QApplication::translate("MainWindow", "Get data and time", 0));
        label_7->setText(QApplication::translate("MainWindow", "Local:", 0));
        btsSetDateAndTime->setText(QApplication::translate("MainWindow", "Set date and time", 0));
        label_9->setText(QApplication::translate("MainWindow", "Login:", 0));
        label_8->setText(QApplication::translate("MainWindow", "Username:", 0));
        txtUserName->setText(QApplication::translate("MainWindow", "admin", 0));
        label_10->setText(QApplication::translate("MainWindow", "Password:", 0));
        setUsernamePass->setText(QApplication::translate("MainWindow", "Set", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
