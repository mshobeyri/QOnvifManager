/********************************************************************************
** Form generated from reading UI file 'videodata.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEODATA_H
#define UI_VIDEODATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VideoData
{
public:
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QListView *lstvEncodingOptions;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QListView *lstvEncoddingConfig;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QListView *lstvSourceConfig;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnRefreshVideoData;
    QPushButton *btnSetVideoData;

    void setupUi(QWidget *VideoData)
    {
        if (VideoData->objectName().isEmpty())
            VideoData->setObjectName(QStringLiteral("VideoData"));
        VideoData->resize(679, 579);
        verticalLayout_4 = new QVBoxLayout(VideoData);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(VideoData);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        lstvEncodingOptions = new QListView(VideoData);
        lstvEncodingOptions->setObjectName(QStringLiteral("lstvEncodingOptions"));

        verticalLayout->addWidget(lstvEncodingOptions);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_2 = new QLabel(VideoData);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_2->addWidget(label_2);

        lstvEncoddingConfig = new QListView(VideoData);
        lstvEncoddingConfig->setObjectName(QStringLiteral("lstvEncoddingConfig"));

        verticalLayout_2->addWidget(lstvEncoddingConfig);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_3 = new QLabel(VideoData);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_3->addWidget(label_3);

        lstvSourceConfig = new QListView(VideoData);
        lstvSourceConfig->setObjectName(QStringLiteral("lstvSourceConfig"));

        verticalLayout_3->addWidget(lstvSourceConfig);


        horizontalLayout_2->addLayout(verticalLayout_3);


        verticalLayout_4->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnRefreshVideoData = new QPushButton(VideoData);
        btnRefreshVideoData->setObjectName(QStringLiteral("btnRefreshVideoData"));

        horizontalLayout->addWidget(btnRefreshVideoData);

        btnSetVideoData = new QPushButton(VideoData);
        btnSetVideoData->setObjectName(QStringLiteral("btnSetVideoData"));

        horizontalLayout->addWidget(btnSetVideoData);


        verticalLayout_4->addLayout(horizontalLayout);


        retranslateUi(VideoData);

        QMetaObject::connectSlotsByName(VideoData);
    } // setupUi

    void retranslateUi(QWidget *VideoData)
    {
        VideoData->setWindowTitle(QApplication::translate("VideoData", "Form", 0));
        label->setText(QApplication::translate("VideoData", "encoding options:", 0));
        label_2->setText(QApplication::translate("VideoData", "encoding config:", 0));
        label_3->setText(QApplication::translate("VideoData", "source config:", 0));
        btnRefreshVideoData->setText(QApplication::translate("VideoData", "Refresh video data", 0));
        btnSetVideoData->setText(QApplication::translate("VideoData", "Set Video Data", 0));
    } // retranslateUi

};

namespace Ui {
    class VideoData: public Ui_VideoData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEODATA_H
