#include "schedulewindow.h"
#include "ui_schedulewindow.h"
#include <QTableWidgetItem>
#include "RectangleWidget.h"
#include <QPixmap>
#include <QHeaderView>
#include <QLabel>
#include <QIcon>
#include "mainwindow.h"
#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <QPalette>
#include <QMessageBox>
#include <QBrush>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCloseEvent>
#include <QSettings>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QStandardPaths>
#include <QTextStream>


ScheduleWindow::ScheduleWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ScheduleWindow)
{
    ui->setupUi(this);
    setMinimumSize(1100, 800);
    setMaximumSize(1100, 800);

    loadDataFromJson();

    QPixmap backgroundPixmap(":/images/menu.png");
    backgroundPixmap = backgroundPixmap.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(backgroundPixmap));
    this->setPalette(palette);

    ui->tableWidget->setRowCount(7);
    ui->tableWidget->setColumnCount(7);

    ui->tableWidget->setRowHeight(0, 50);
    for (int i = 1; i < 7; ++i) {
        ui->tableWidget->setRowHeight(i, 133);
    }

    QStringList daysOfWeek = {"Пн", "Вт", "Ср", "Чт", "Пт", "Сб", "Вс"};
    for (int column = 0; column < daysOfWeek.size(); ++column) {
        QTableWidgetItem *item = new QTableWidgetItem(daysOfWeek[column]);
        item->setTextAlignment(Qt::AlignCenter);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        item->setForeground(QBrush(Qt::white));

        QFont font = item->font();
        font.setBold(true);
        item->setFont(font);

        ui->tableWidget->setItem(0, column, item);

    }

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for (int i = 0; i < 7; ++i) {
        ui->tableWidget->setColumnWidth(i, 114);
    }

    for (int i = 1; i < 7; ++i) {
        ui->tableWidget->setRowHeight(i, 113);
    }

    ui->tableWidget->setFixedSize(800, 730);

    connect(ui->tableWidget, &QTableWidget::cellPressed, this, &ScheduleWindow::onCellPressed);
    connect(ui->actionCloseMen, &QAction::triggered, this, &ScheduleWindow::onMenuCloseTriggered);

    QVBoxLayout *leftLayout = new QVBoxLayout();
    leftLayout->setContentsMargins(20, 50, 20, 10);


    int rectWidth = 180;
    int rectHeight = 100;

    ui->tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    leftLayout->addWidget(new RectangleWidget(this, ":/images/bed2.png", QColor("#FF6347"), rectWidth, rectHeight, "Убраться"));
    leftLayout->addWidget(new RectangleWidget(this, ":/images/dish2.png", QColor("#4682B4"), rectWidth, rectHeight, "Помыть посуду"));
    leftLayout->addWidget(new RectangleWidget(this, ":/images/dog2.png", QColor("#32CD32"), rectWidth, rectHeight, "Прогулка"));
    leftLayout->addWidget(new RectangleWidget(this, ":/images/flowers2.png",  QColor ("#FFD700"), rectWidth, rectHeight, "Полить цветы"));
    leftLayout->addWidget(new RectangleWidget(this, ":/images/read2.png", QColor("#FF69B4"), rectWidth, rectHeight, "Почитать книгу"));
    leftLayout->addWidget(new RectangleWidget(this, ":/images/homework2.png", QColor("#FF4500"), rectWidth, rectHeight, "Сделать д/з"));

    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addLayout(leftLayout);
    mainLayout->addWidget(ui->tableWidget);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setFocusPolicy(Qt::NoFocus);
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);


    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    QList<QColor> columnColors = {
        QColor("#FF6347"),
        QColor("#4682B4"),
        QColor("#32CD32"),
        QColor ("#FFD700"),
        QColor("#FF69B4"),
        QColor("#8A2BE2"),
        QColor("#FF4500")
    };

    for (int column = 0; column < ui->tableWidget->columnCount(); ++column) {
        for (int row = 0; row < 1; ++row) {
            QTableWidgetItem *item = ui->tableWidget->item(row, column);
            if (!item) {
                item = new QTableWidgetItem();
                ui->tableWidget->setItem(row, column, item);
            }
            item->setBackground(QBrush(columnColors[column]));
        }
    }
}

ScheduleWindow::~ScheduleWindow()
{
    delete ui;
}

void ScheduleWindow::closeEvent(QCloseEvent *event)
{
    saveDataToJson();
    event->accept();
    QApplication::quit();
}

void ScheduleWindow::onMenuCloseTriggered() {
    this->close();
}

#include "mainwindow.h"

void ScheduleWindow::onBackButtonClicked()
{
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
    this->close();
}

void ScheduleWindow::onCellPressed(int row, int column) {
    if (row == 0) {
        return;
    }

    static QPixmap star(":/images/star.png");
    static QPixmap sad(":/images/sad.png");

    QPixmap starScaled = star.scaled(60, 60, Qt::KeepAspectRatio);
    QPixmap sadScaled = sad.scaled(60, 60, Qt::KeepAspectRatio);

    QTableWidgetItem *item = ui->tableWidget->item(row, column);
    if (!item) {
        item = new QTableWidgetItem();
        ui->tableWidget->setItem(row, column, item);
    }

    int state = item->data(Qt::UserRole).toInt();

    if (state == 0) {
        item->setData(Qt::UserRole, 1);
        QLabel *label = new QLabel();
        label->setPixmap(starScaled);
        ui->tableWidget->setCellWidget(row, column, label);
    } else if (state == 1) {
        item->setData(Qt::UserRole, 2);
        QLabel *label = new QLabel();
        label->setPixmap(sadScaled);
        ui->tableWidget->setCellWidget(row, column, label);
    } else {
        item->setData(Qt::UserRole, 0);
        ui->tableWidget->removeCellWidget(row, column);
    }
}

void ScheduleWindow::saveDataToJson()
{
    QString filePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/data.json";
    QFile saveFile(filePath);

    if (!saveFile.open(QIODevice::WriteOnly)) {
        return;
    }

    QJsonArray jsonArray;

    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        QJsonObject rowObject;

        for (int column = 0; column < ui->tableWidget->columnCount(); ++column) {
            QTableWidgetItem *item = ui->tableWidget->item(row, column);
            if (item) {
                rowObject[QString("column_%1").arg(column)] = item->data(Qt::UserRole).toInt();
            }
        }

        jsonArray.append(rowObject);
    }

    QJsonDocument saveDoc(jsonArray);
    saveFile.write(saveDoc.toJson());
    saveFile.close();
}

void ScheduleWindow::loadDataFromJson() {
    QString filePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/data.json";
    QFile loadFile(filePath);

    if (!loadFile.open(QIODevice::ReadOnly)) {
        return;
    }

    QByteArray jsonData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(jsonData));
    QJsonArray jsonArray = loadDoc.array();
    loadFile.close();

    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(3);

    for (int i = 0; i < jsonArray.size(); ++i) {
        QJsonObject rowObject = jsonArray[i].toObject();
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);

        for (int column = 0; column < ui->tableWidget->columnCount(); ++column) {
            int state = rowObject[QString("column_%1").arg(column)].toInt();
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setData(Qt::UserRole, state);
            ui->tableWidget->setItem(row, column, item);

            QLabel *label = new QLabel();
            if (state == 1) {
                label->setPixmap(QPixmap(":/images/star.png").scaled(60, 60, Qt::KeepAspectRatio));
            } else if (state == 2) {
                label->setPixmap(QPixmap(":/images/sad.png").scaled(60, 60, Qt::KeepAspectRatio));
            } else {
                ui->tableWidget->removeCellWidget(row, column);
                continue;
            }
            ui->tableWidget->setCellWidget(row, column, label);
        }
    }
}
