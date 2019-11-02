/********************************************************************************
** Form generated from reading UI file 'window.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDial>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "myglwidget.h"

QT_BEGIN_NAMESPACE

class Ui_Window
{
public:
    QVBoxLayout *verticalLayout;
    MyGLWidget *myGLWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QDial *rotXSlider;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QDial *rotYSlider;
    QDial *rotZDial;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QDial *rotZSlider;

    void setupUi(QWidget *Window)
    {
        if (Window->objectName().isEmpty())
            Window->setObjectName(QString::fromUtf8("Window"));
        Window->resize(369, 515);
        verticalLayout = new QVBoxLayout(Window);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        myGLWidget = new MyGLWidget(Window);
        myGLWidget->setObjectName(QString::fromUtf8("myGLWidget"));
        myGLWidget->setMinimumSize(QSize(200, 200));

        verticalLayout->addWidget(myGLWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(Window);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        rotXSlider = new QDial(Window);
        rotXSlider->setObjectName(QString::fromUtf8("rotXSlider"));
        rotXSlider->setMaximum(360);
        rotXSlider->setSingleStep(16);
        rotXSlider->setPageStep(15);
        rotXSlider->setNotchesVisible(true);
        //rotXSlider->setOrientation(Qt::Horizontal);
        //rotXSlider->setTickPosition(QSlider::TicksAbove);
        //rotXSlider->setTickInterval(15);

        horizontalLayout->addWidget(rotXSlider);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(Window);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        rotYSlider = new QDial(Window);
        rotYSlider->setObjectName(QString::fromUtf8("rotYSlider"));
        rotYSlider->setMaximum(360);
        rotYSlider->setSingleStep(16);
        rotYSlider->setPageStep(15);
        rotYSlider->setNotchesVisible(true);
       // rotYSlider->setOrientation(Qt::Horizontal);
       // rotYSlider->setTickPosition(QSlider::TicksAbove);
       // rotYSlider->setTickInterval(15);

        horizontalLayout_2->addWidget(rotYSlider);


        verticalLayout->addLayout(horizontalLayout_2);

        rotZDial = new QDial(Window);
        rotZDial->setObjectName(QString::fromUtf8("rotZDial"));
        rotZDial->setNotchesVisible(true);
        rotZDial->setMaximum(360);
        rotZDial->setSingleStep(16);
        rotZDial->setPageStep(15);

       // verticalLayout->addWidget(rotZDial);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(Window);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        rotZSlider = new QDial(Window);
        rotZSlider->setObjectName(QString::fromUtf8("rotZSlider"));
        rotZSlider->setMaximum(360);
        rotZSlider->setSingleStep(16);
        rotZSlider->setPageStep(15);
        rotZSlider->setNotchesVisible(true);
        //rotZSlider->setOrientation(Qt::Horizontal);
       // rotZSlider->setTickPosition(QSlider::TicksAbove);
       // rotZSlider->setTickInterval(15);

        horizontalLayout_3->addWidget(rotZSlider);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(Window);
        QObject::connect(rotYSlider, SIGNAL(valueChanged(int)), myGLWidget, SLOT(setYRotation(int)));
        QObject::connect(rotZSlider, SIGNAL(valueChanged(int)), myGLWidget, SLOT(setZRotation(int)));
        QObject::connect(rotXSlider, SIGNAL(valueChanged(int)), myGLWidget, SLOT(setXRotation(int)));
       // QObject::connect(rotZDial, SIGNAL(valueChanged(int)), myGLWidget, SLOT(setZRotation(int)));

        QMetaObject::connectSlotsByName(Window);
    } // setupUi

    void retranslateUi(QWidget *Window)
    {
        Window->setWindowTitle(QCoreApplication::translate("Window", "Window", nullptr));
        label->setText(QCoreApplication::translate("Window", " x", nullptr));
        label_2->setText(QCoreApplication::translate("Window", " y", nullptr));
        label_3->setText(QCoreApplication::translate("Window", " z", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Window: public Ui_Window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_H