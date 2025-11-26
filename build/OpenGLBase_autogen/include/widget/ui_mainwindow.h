/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *labelMsInfo;
    QLabel *labelMs;
    QSpacerItem *horizontalSpacer_3;
    QLabel *labelLightPosInfo;
    QLabel *labelLightPos;
    QSpacerItem *horizontalSpacer;
    QLabel *labelReload;
    QSpacerItem *horizontalSpacer_2;
    QLabel *labelDirection;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        labelMsInfo = new QLabel(widget);
        labelMsInfo->setObjectName("labelMsInfo");

        horizontalLayout->addWidget(labelMsInfo, 0, Qt::AlignmentFlag::AlignLeft);

        labelMs = new QLabel(widget);
        labelMs->setObjectName("labelMs");
        labelMs->setStyleSheet(QString::fromUtf8("color: green;"));

        horizontalLayout->addWidget(labelMs);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        labelLightPosInfo = new QLabel(widget);
        labelLightPosInfo->setObjectName("labelLightPosInfo");

        horizontalLayout->addWidget(labelLightPosInfo);

        labelLightPos = new QLabel(widget);
        labelLightPos->setObjectName("labelLightPos");
        labelLightPos->setStyleSheet(QString::fromUtf8("color: green;"));

        horizontalLayout->addWidget(labelLightPos);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        labelReload = new QLabel(widget);
        labelReload->setObjectName("labelReload");
        labelReload->setStyleSheet(QString::fromUtf8("color: gray;"));

        horizontalLayout->addWidget(labelReload);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        labelDirection = new QLabel(widget);
        labelDirection->setObjectName("labelDirection");
        labelDirection->setStyleSheet(QString::fromUtf8("color: grey;"));

        horizontalLayout->addWidget(labelDirection);


        verticalLayout->addWidget(widget, 0, Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        labelMsInfo->setText(QCoreApplication::translate("MainWindow", "Loading time: ", nullptr));
        labelMs->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        labelLightPosInfo->setText(QCoreApplication::translate("MainWindow", "Light position:", nullptr));
        labelLightPos->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        labelReload->setText(QCoreApplication::translate("MainWindow", "Reload: F5", nullptr));
        labelDirection->setText(QCoreApplication::translate("MainWindow", "Move light: \342\206\220, \342\206\222", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
