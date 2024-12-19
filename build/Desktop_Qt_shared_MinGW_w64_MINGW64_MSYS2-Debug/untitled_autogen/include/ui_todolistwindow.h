/********************************************************************************
** Form generated from reading UI file 'todolistwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TODOLISTWINDOW_H
#define UI_TODOLISTWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_todolistwindow
{
public:
    QAction *actionclose;
    QWidget *centralwidget;
    QTableWidget *tableWidget;
    QPushButton *backButton;
    QLabel *editModeLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *todolistwindow)
    {
        if (todolistwindow->objectName().isEmpty())
            todolistwindow->setObjectName("todolistwindow");
        todolistwindow->resize(1356, 910);
        actionclose = new QAction(todolistwindow);
        actionclose->setObjectName("actionclose");
        centralwidget = new QWidget(todolistwindow);
        centralwidget->setObjectName("centralwidget");
        tableWidget = new QTableWidget(centralwidget);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        if (tableWidget->rowCount() < 15)
            tableWidget->setRowCount(15);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(260, -10, 321, 571));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setHintingPreference(QFont::PreferDefaultHinting);
        tableWidget->setFont(font);
        tableWidget->setRowCount(15);
        tableWidget->setColumnCount(2);
        tableWidget->horizontalHeader()->setVisible(false);
        tableWidget->horizontalHeader()->setHighlightSections(true);
        tableWidget->verticalHeader()->setVisible(false);
        backButton = new QPushButton(centralwidget);
        backButton->setObjectName("backButton");
        backButton->setGeometry(QRect(990, 720, 141, 71));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(74, 95, 235, 200));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(178, 188, 255, 200));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(126, 141, 245, 200));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(37, 48, 117, 200));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(49, 63, 157, 200));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush6(QColor(255, 255, 255, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush6);
        palette.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        QBrush brush7(QColor(164, 175, 245, 227));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush7);
        QBrush brush8(QColor(255, 255, 220, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        QBrush brush9(QColor(0, 0, 0, 127));
        brush9.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush9);
#endif
        palette.setBrush(QPalette::Active, QPalette::Accent, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush9);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::Accent, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        QBrush brush10(QColor(37, 48, 117, 100));
        brush10.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush10);
#endif
        QBrush brush11(QColor(131, 147, 255, 200));
        brush11.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Accent, brush11);
        backButton->setPalette(palette);
        QFont font1;
        font1.setPointSize(16);
        font1.setBold(true);
        backButton->setFont(font1);
        editModeLabel = new QLabel(centralwidget);
        editModeLabel->setObjectName("editModeLabel");
        editModeLabel->setGeometry(QRect(110, 40, 271, 20));
        QFont font2;
        font2.setBold(true);
        editModeLabel->setFont(font2);
        todolistwindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(todolistwindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1356, 26));
        todolistwindow->setMenuBar(menubar);
        statusbar = new QStatusBar(todolistwindow);
        statusbar->setObjectName("statusbar");
        todolistwindow->setStatusBar(statusbar);

        retranslateUi(todolistwindow);
        QObject::connect(actionclose, &QAction::triggered, todolistwindow, qOverload<>(&QMainWindow::close));

        QMetaObject::connectSlotsByName(todolistwindow);
    } // setupUi

    void retranslateUi(QMainWindow *todolistwindow)
    {
        todolistwindow->setWindowTitle(QCoreApplication::translate("todolistwindow", "MainWindow", nullptr));
        actionclose->setText(QCoreApplication::translate("todolistwindow", "close", nullptr));
        backButton->setText(QCoreApplication::translate("todolistwindow", "\320\222 \320\234\320\265\320\275\321\216", nullptr));
        editModeLabel->setText(QCoreApplication::translate("todolistwindow", "\320\240\320\225\320\226\320\230\320\234 \320\240\320\225\320\224\320\220\320\232\320\242\320\230\320\240\320\236\320\222\320\220\320\235\320\230\320\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class todolistwindow: public Ui_todolistwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TODOLISTWINDOW_H
