/********************************************************************************
** Form generated from reading UI file 'ScheduleWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCHEDULEWINDOW_H
#define UI_SCHEDULEWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScheduleWindow
{
public:
    QAction *actionCloseMen;
    QAction *switchToMainAction;
    QWidget *centralwidget;
    QTableWidget *tableWidget;
    QLabel *MD;
    QLabel *MD_2;
    QLabel *MD_3;
    QLabel *MD_4;
    QLabel *MD_5;
    QLabel *MD_6;
    QLabel *MD_7;
    QPushButton *backButton;
    QFrame *frame;
    QFrame *line;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ScheduleWindow)
    {
        if (ScheduleWindow->objectName().isEmpty())
            ScheduleWindow->setObjectName("ScheduleWindow");
        ScheduleWindow->resize(1455, 908);
        actionCloseMen = new QAction(ScheduleWindow);
        actionCloseMen->setObjectName("actionCloseMen");
        switchToMainAction = new QAction(ScheduleWindow);
        switchToMainAction->setObjectName("switchToMainAction");
        centralwidget = new QWidget(ScheduleWindow);
        centralwidget->setObjectName("centralwidget");
        tableWidget = new QTableWidget(centralwidget);
        if (tableWidget->columnCount() < 7)
            tableWidget->setColumnCount(7);
        if (tableWidget->rowCount() < 6)
            tableWidget->setRowCount(6);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(240, 370, 641, 141));
        tableWidget->setRowCount(6);
        tableWidget->setColumnCount(7);
        tableWidget->horizontalHeader()->setVisible(false);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget->horizontalHeader()->setHighlightSections(false);
        tableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableWidget->horizontalHeader()->setStretchLastSection(false);
        tableWidget->verticalHeader()->setVisible(false);
        MD = new QLabel(centralwidget);
        MD->setObjectName("MD");
        MD->setGeometry(QRect(290, 0, 63, 20));
        QFont font;
        font.setBold(true);
        MD->setFont(font);
        MD_2 = new QLabel(centralwidget);
        MD_2->setObjectName("MD_2");
        MD_2->setGeometry(QRect(540, 400, 63, 20));
        MD_3 = new QLabel(centralwidget);
        MD_3->setObjectName("MD_3");
        MD_3->setGeometry(QRect(490, 40, 63, 20));
        MD_4 = new QLabel(centralwidget);
        MD_4->setObjectName("MD_4");
        MD_4->setGeometry(QRect(580, 40, 63, 20));
        MD_5 = new QLabel(centralwidget);
        MD_5->setObjectName("MD_5");
        MD_5->setGeometry(QRect(680, 40, 63, 20));
        MD_6 = new QLabel(centralwidget);
        MD_6->setObjectName("MD_6");
        MD_6->setGeometry(QRect(790, 40, 63, 20));
        MD_7 = new QLabel(centralwidget);
        MD_7->setObjectName("MD_7");
        MD_7->setGeometry(QRect(880, 40, 63, 20));
        backButton = new QPushButton(centralwidget);
        backButton->setObjectName("backButton");
        backButton->setGeometry(QRect(160, 170, 931, 481));
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(620, 450, 120, 80));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setGeometry(QRect(750, 480, 118, 3));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        ScheduleWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ScheduleWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1455, 26));
        ScheduleWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ScheduleWindow);
        statusbar->setObjectName("statusbar");
        ScheduleWindow->setStatusBar(statusbar);

        retranslateUi(ScheduleWindow);

        QMetaObject::connectSlotsByName(ScheduleWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ScheduleWindow)
    {
        ScheduleWindow->setWindowTitle(QCoreApplication::translate("ScheduleWindow", "MainWindow", nullptr));
        actionCloseMen->setText(QCoreApplication::translate("ScheduleWindow", "CloseMen", nullptr));
        switchToMainAction->setText(QCoreApplication::translate("ScheduleWindow", "\320\234\320\265\320\275\321\216", nullptr));
        MD->setText(QCoreApplication::translate("ScheduleWindow", "\320\237\320\235", nullptr));
        MD_2->setText(QCoreApplication::translate("ScheduleWindow", "\320\222\320\242", nullptr));
        MD_3->setText(QCoreApplication::translate("ScheduleWindow", "\320\241\320\240", nullptr));
        MD_4->setText(QCoreApplication::translate("ScheduleWindow", "\320\247\320\242", nullptr));
        MD_5->setText(QCoreApplication::translate("ScheduleWindow", "\320\237\320\242", nullptr));
        MD_6->setText(QCoreApplication::translate("ScheduleWindow", "\320\241\320\221", nullptr));
        MD_7->setText(QCoreApplication::translate("ScheduleWindow", "\320\222\320\241", nullptr));
        backButton->setText(QCoreApplication::translate("ScheduleWindow", "\320\235\320\260\320\267\320\260\320\264 \320\262 \320\234\320\265\320\275\321\216", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ScheduleWindow: public Ui_ScheduleWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCHEDULEWINDOW_H
