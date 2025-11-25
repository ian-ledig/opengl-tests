/********************************************************************************
** Form generated from reading UI file 'widgetColor.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETCOLOR_H
#define UI_WIDGETCOLOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QSpinBox *spinBoxR;
    QSpinBox *spinBoxG;
    QSpinBox *spinBoxB;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonOk;
    QPushButton *pushButtonCancel;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName("Form");
        Form->resize(250, 100);
        Form->setMinimumSize(QSize(200, 80));
        verticalLayout = new QVBoxLayout(Form);
        verticalLayout->setObjectName("verticalLayout");
        widget = new QWidget(Form);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(0, 0));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        spinBoxR = new QSpinBox(widget);
        spinBoxR->setObjectName("spinBoxR");
        spinBoxR->setMaximum(255);

        horizontalLayout_2->addWidget(spinBoxR, 0, Qt::AlignmentFlag::AlignLeft);

        spinBoxG = new QSpinBox(widget);
        spinBoxG->setObjectName("spinBoxG");
        spinBoxG->setMaximum(255);

        horizontalLayout_2->addWidget(spinBoxG, 0, Qt::AlignmentFlag::AlignLeft);

        spinBoxB = new QSpinBox(widget);
        spinBoxB->setObjectName("spinBoxB");
        spinBoxB->setMaximum(255);

        horizontalLayout_2->addWidget(spinBoxB, 0, Qt::AlignmentFlag::AlignLeft);


        verticalLayout->addWidget(widget, 0, Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);

        widget_2 = new QWidget(Form);
        widget_2->setObjectName("widget_2");
        widget_2->setMinimumSize(QSize(0, 0));
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setObjectName("horizontalLayout");
        pushButtonOk = new QPushButton(widget_2);
        pushButtonOk->setObjectName("pushButtonOk");

        horizontalLayout->addWidget(pushButtonOk);

        pushButtonCancel = new QPushButton(widget_2);
        pushButtonCancel->setObjectName("pushButtonCancel");

        horizontalLayout->addWidget(pushButtonCancel, 0, Qt::AlignmentFlag::AlignLeft);


        verticalLayout->addWidget(widget_2, 0, Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTop);


        retranslateUi(Form);
        QObject::connect(pushButtonCancel, &QPushButton::clicked, Form, qOverload<>(&QWidget::close));

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        pushButtonOk->setText(QCoreApplication::translate("Form", "Ok", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("Form", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETCOLOR_H
