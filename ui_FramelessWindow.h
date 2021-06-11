/********************************************************************************
** Form generated from reading UI file 'FramelessWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRAMELESSWINDOW_H
#define UI_FRAMELESSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <WindowDragger.h>

QT_BEGIN_NAMESPACE

class Ui_FramelessWindow
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *windowFrame;
    QVBoxLayout *verticalLayout_3;
    WindowDragger *windowTitleBar;
    QHBoxLayout *horizontalLayout;
    QLabel *spacerLabel1;
    QLabel *windowIcon;
    QLabel *spacerLabel2;
    QLabel *windowTitleText;
    QToolButton *minimizeBtn;
    QToolButton *restoreBtn;
    QToolButton *maximizeBtn;
    QToolButton *closeBtn;
    QWidget *windowContent;
    QVBoxLayout *verticalLayout_2;

    void setupUi(QWidget *FramelessWindow)
    {
        if (FramelessWindow->objectName().isEmpty())
            FramelessWindow->setObjectName(QString::fromUtf8("FramelessWindow"));
        FramelessWindow->resize(500, 500);
        FramelessWindow->setMinimumSize(QSize(500, 500));
        FramelessWindow->setBaseSize(QSize(0, 0));
        verticalLayout = new QVBoxLayout(FramelessWindow);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        windowFrame = new QWidget(FramelessWindow);
        windowFrame->setObjectName(QString::fromUtf8("windowFrame"));
        windowFrame->setStyleSheet(QString::fromUtf8("#windowFrame{border:1px solid color(0,0,0); border-radius:5px 5px 5px 5px; background-color:color(255,255,255);}"));
        verticalLayout_3 = new QVBoxLayout(windowFrame);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(1, 1, 1, 1);
        windowTitleBar = new WindowDragger(windowFrame);
        windowTitleBar->setObjectName(QString::fromUtf8("windowTitleBar"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(windowTitleBar->sizePolicy().hasHeightForWidth());
        windowTitleBar->setSizePolicy(sizePolicy);
        windowTitleBar->setMinimumSize(QSize(0, 40));
        windowTitleBar->setStyleSheet(QString::fromUtf8("#windowTitleBar{\n"
"border: 0px none; \n"
"border-top-left-radius:5px; \n"
"border-top-right-radius:5px; \n"
"background-color:rgb(255,255,255);\n"
"\n"
"}"));
        horizontalLayout = new QHBoxLayout(windowTitleBar);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        spacerLabel1 = new QLabel(windowTitleBar);
        spacerLabel1->setObjectName(QString::fromUtf8("spacerLabel1"));

        horizontalLayout->addWidget(spacerLabel1);

        windowIcon = new QLabel(windowTitleBar);
        windowIcon->setObjectName(QString::fromUtf8("windowIcon"));
        windowIcon->setMinimumSize(QSize(16, 16));
        windowIcon->setMaximumSize(QSize(16, 16));

        horizontalLayout->addWidget(windowIcon, 0, Qt::AlignHCenter|Qt::AlignVCenter);

        spacerLabel2 = new QLabel(windowTitleBar);
        spacerLabel2->setObjectName(QString::fromUtf8("spacerLabel2"));

        horizontalLayout->addWidget(spacerLabel2);

        windowTitleText = new QLabel(windowTitleBar);
        windowTitleText->setObjectName(QString::fromUtf8("windowTitleText"));
        windowTitleText->setMinimumSize(QSize(0, 40));
        windowTitleText->setScaledContents(true);

        horizontalLayout->addWidget(windowTitleText);

        minimizeBtn = new QToolButton(windowTitleBar);
        minimizeBtn->setObjectName(QString::fromUtf8("minimizeBtn"));
        minimizeBtn->setMinimumSize(QSize(40, 40));
        minimizeBtn->setStyleSheet(QString::fromUtf8("#minimizeBtn{\n"
"    background-color:none;\n"
"    border:none;\n"
"    width:16px;\n"
"    height:16px;\n"
"    padding:4px;\n"
"    border-radius: 5px;\n"
"	\n"
"	image: url(:/img/images/min.png);\n"
"  \n"
"}\n"
"#minimizeBtn:hover{\n"
"	background-color:palette(alternate-base);\n"
"}\n"
"##minimizeBtn:pressed{\n"
"	background-color:palette(highlight);\n"
"}"));

        horizontalLayout->addWidget(minimizeBtn);

        restoreBtn = new QToolButton(windowTitleBar);
        restoreBtn->setObjectName(QString::fromUtf8("restoreBtn"));
        restoreBtn->setMinimumSize(QSize(40, 40));
        restoreBtn->setStyleSheet(QString::fromUtf8("#restoreBtn{\n"
"    background-color:none;\n"
"    border:none;\n"
"    width:16px;\n"
"    height:16px;\n"
"    padding:4px;\n"
"    border-radius: 5px;\n"
"\n"
"  \n"
"	image: url(:/img/images/restoreBtnIcon.png);\n"
"}\n"
"#restoreBtn:hover{\n"
"	background-color:palette(alternate-base);\n"
"}\n"
"##restoreBtn:pressed{\n"
"	background-color:palette(highlight);\n"
"}"));

        horizontalLayout->addWidget(restoreBtn);

        maximizeBtn = new QToolButton(windowTitleBar);
        maximizeBtn->setObjectName(QString::fromUtf8("maximizeBtn"));
        maximizeBtn->setMinimumSize(QSize(40, 40));
        maximizeBtn->setStyleSheet(QString::fromUtf8("#maximizeBtn{\n"
"    background-color:none;\n"
"    border:none;\n"
"    width:16px;\n"
"    height:16px;\n"
"    padding:4px;\n"
"    border-radius: 5px;\n"
"	\n"
"	image: url(:/img/images/max.png);\n"
"  \n"
"}\n"
"#maximizeBtn:hover{\n"
"	background-color:palette(alternate-base);\n"
"}\n"
"##maximizeBtn:pressed{\n"
"	background-color:palette(highlight);\n"
"}"));

        horizontalLayout->addWidget(maximizeBtn);

        closeBtn = new QToolButton(windowTitleBar);
        closeBtn->setObjectName(QString::fromUtf8("closeBtn"));
        closeBtn->setMinimumSize(QSize(40, 40));
        closeBtn->setLayoutDirection(Qt::LeftToRight);
        closeBtn->setStyleSheet(QString::fromUtf8("#closeBtn{\n"
"    background-color:none;\n"
"    border:none;\n"
"    width:16px;\n"
"    height:16px;\n"
"    padding:4px;\n"
"	margin:0px;\n"
"   \n"
"	image: url(:/img/images/close.png);\n"
"  \n"
"}\n"
"#closeBtn:hover{\n"
"	background-color:rgb(235,18,18);\n"
"}\n"
"##closeBtn:pressed{\n"
"	background-color:palette(highlight);\n"
"}"));

        horizontalLayout->addWidget(closeBtn, 0, Qt::AlignHCenter|Qt::AlignVCenter);

        horizontalLayout->setStretch(3, 1);

        verticalLayout_3->addWidget(windowTitleBar);

        windowContent = new QWidget(windowFrame);
        windowContent->setObjectName(QString::fromUtf8("windowContent"));
        windowContent->setStyleSheet(QString::fromUtf8("#windowContent{\n"
"  border: 0px none color(255,255,255);\n"
"  border-bottom-left-radius:5px;\n"
"border-bottom-right-radius:5px;\n"
"	background-color:qlineargradient(spread: pad, x1:0, y1:1, x2:1, y2:1, stop:0 rgb(255,255,255), stop:1 rgb(255,255,255))\n"
"\n"
"}"));
        verticalLayout_2 = new QVBoxLayout(windowContent);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);

        verticalLayout_3->addWidget(windowContent);


        verticalLayout->addWidget(windowFrame);


        retranslateUi(FramelessWindow);

        QMetaObject::connectSlotsByName(FramelessWindow);
    } // setupUi

    void retranslateUi(QWidget *FramelessWindow)
    {
        FramelessWindow->setWindowTitle(QApplication::translate("FramelessWindow", "FramelessWindow", nullptr));
        spacerLabel1->setText(QString());
        windowIcon->setText(QString());
        spacerLabel2->setText(QString());
        windowTitleText->setText(QApplication::translate("FramelessWindow", "WindowTitle", nullptr));
        minimizeBtn->setText(QString());
        restoreBtn->setText(QString());
        maximizeBtn->setText(QString());
        closeBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FramelessWindow: public Ui_FramelessWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRAMELESSWINDOW_H
