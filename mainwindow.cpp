#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "schedulewindow.h"
#include "todolistwindow.h"
#include <QLabel>
#include <QPixmap>

#include <QPalette>
#include <QBrush>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QPixmap backgroundPixmap(":/images/menu.png");
    backgroundPixmap = backgroundPixmap.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(backgroundPixmap));
    this->setPalette(palette);


    QString originalText = ui->label->text();

    QString coloredText;
    for (int i = 0; i < originalText.length(); ++i) {
        QString color;
        switch (i % 4) {
        case 0: color = "blue"; break;
        case 1: color = "red"; break;
        case 2: color = "green"; break;
        case 3: color = "orange"; break;
        }
        coloredText += QString("<span style='color: %1;'>%2</span>").arg(color).arg(originalText[i]);
    }



    ui->label->setText(coloredText);

    ui->btnToDoList->setStyleSheet("QPushButton {"
                              "border: 2px solid rgba(2, 198, 2, 200);"
                              "border-radius: 30px;"
                              "background-color: rgba(2, 198, 2, 200);"
                              "color: white;"
                              "padding: 10px;"
                              "}");

    ui->btnSchedule->setStyleSheet("QPushButton {"
                                   "border: 2px solid rgba(255,0,0,200);"
                                   "border-radius: 30px;"
                                   "background-color: rgba(255,0,0,200);"
                                   "color: white;"
                                   "padding: 10px;"
                                   "}");


    setMinimumSize(1200, 900);
    setMaximumSize(1200, 900);

    connect(ui->btnToDoList, &QPushButton::clicked, this, &MainWindow::openToDoList);
    connect(ui->btnSchedule, &QPushButton::clicked, this, &MainWindow::openSchedule);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::openToDoList() {
    todolistwindow *todoWindow = new todolistwindow(this);
    todoWindow->show();
    this->hide();
}

void MainWindow::openSchedule() {
    ScheduleWindow *scheduleWindow = new ScheduleWindow(this);
    scheduleWindow->show();
    this->hide();
}
