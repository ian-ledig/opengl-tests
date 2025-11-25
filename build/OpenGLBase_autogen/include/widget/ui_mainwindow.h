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
    QSpacerItem *horizontalSpacer;
    QLabel *labelReload;

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

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        labelReload = new QLabel(widget);
        labelReload->setObjectName("labelReload");
        labelReload->setStyleSheet(QString::fromUtf8("color: gray;"));

        horizontalLayout->addWidget(labelReload);


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
        labelReload->setText(QCoreApplication::translate("MainWindow", "Reload: F5", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
