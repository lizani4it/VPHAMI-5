#include "schedulewindow.h"
#include "ui_schedulewindow.h"
#include <QTableWidgetItem>
#include "RectangleWidget.h"
#include <QPixmap>
#include <QHeaderView>  // Для изменения заголовков и прокрутки
#include <QLabel>       // Для использования QLabel
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
// Добавьте этот заголовочный файл
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
    setMinimumSize(1200, 900);
    setMaximumSize(1200, 900);

    qDebug() << "UI setup completed";  // Отладочное сообщение

    loadDataFromJson();
    qDebug() << "Data loaded";  // Отладочное сообщение

    connect(ui->backButton, &QPushButton::clicked, this, &ScheduleWindow::onBackButtonClicked);
    qDebug() << "Connected back button";  // Отладочное сообщение

    QPixmap backgroundPixmap(":/images/menu.png");
    qDebug() << "Background image loaded";  // Отладочное сообщение

    backgroundPixmap = backgroundPixmap.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(backgroundPixmap));
    this->setPalette(palette);
    qDebug() << "Background image applied";  // Отладочное сообщение



    qDebug() << "Window resized";  // Отладочное сообщение

    // Настройка таблицы: 7 строк и 6 столбцов
    ui->tableWidget->setRowCount(6);
    ui->tableWidget->setColumnCount(7);
    qDebug() << "Table widget setup completed";  // Отладочное сообщение

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    qDebug() << "Table widget settings applied";  // Отладочное сообщение

    // Установка ширины и высоты столбцов
    for (int i = 0; i < 7; ++i) {
        ui->tableWidget->setColumnWidth(i, 118);  // Установить ширину каждой колонки
    }

    for (int i = 0; i < 6; ++i) {
        ui->tableWidget->setRowHeight(i, 133);  // Установить высоту каждой строки
    }
    qDebug() << "Table column and row sizes set";  // Отладочное сообщение

    ui->tableWidget->setFixedSize(830, 800);  // Установить общий размер таблицы
    qDebug() << "Table widget fixed size set";  // Отладочное сообщение

    // Обработчик нажатий на ячейки
    connect(ui->tableWidget, &QTableWidget::cellPressed, this, &ScheduleWindow::onCellPressed);
    connect(ui->actionCloseMen, &QAction::triggered, this, &ScheduleWindow::onMenuCloseTriggered);
    qDebug() << "Connections for table widget and menu action completed";  // Отладочное сообщение

    // Создание и добавление прямоугольников
    QVBoxLayout *leftLayout = new QVBoxLayout();  // Вертикальный layout для прямоугольников
    int rectWidth = 180;  // Фиксированная ширина прямоугольников
    int rectHeight = 100;


    // Добавляем 6 прямоугольников с разными картинками
    leftLayout->addWidget(new RectangleWidget(this, ":/images/bed.png", QColor("#FF6347"), rectWidth, rectHeight, "Убраться"));
    leftLayout->addWidget(new RectangleWidget(this, ":/images/dish.png", QColor("pink"), rectWidth, rectHeight, "Помыть посуду"));
    leftLayout->addWidget(new RectangleWidget(this, ":/images/dog.png", QColor("#4682B4"), rectWidth, rectHeight, "Прогулка"));
    leftLayout->addWidget(new RectangleWidget(this, ":/images/flowers.png", QColor(34, 139, 34), rectWidth, rectHeight, "Полить цветы"));
    leftLayout->addWidget(new RectangleWidget(this, ":/images/read.png", QColor("#FFD700"), rectWidth, rectHeight, "Почитать книгу"));
    leftLayout->addWidget(new RectangleWidget(this, ":/images/homework.png", QColor(255, 165, 0), rectWidth, rectHeight, "Сделать д/з"));// Цвет "Orange"

    QHBoxLayout *mainLayout = new QHBoxLayout();  // Горизонтальный layout для размещения таблицы и прямоугольников
    mainLayout->addLayout(leftLayout);  // Добавляем вертикальный layout с прямоугольниками
    mainLayout->addWidget(ui->tableWidget);  // Добавляем таблицу в основной layout

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

}


ScheduleWindow::~ScheduleWindow()
{
    delete ui;
}


void ScheduleWindow::closeEvent(QCloseEvent *event)
{
    saveDataToJson();  // Сохраняем данные перед закрытием
    event->accept();  // Закрываем окно
}



void ScheduleWindow::onMenuCloseTriggered() {
    this->close(); // Закрыть окно
}

#include "mainwindow.h"  // Для доступа к главному окну

void ScheduleWindow::onBackButtonClicked()
{
    // Создаём объект главного окна
    MainWindow *mainWindow = new MainWindow();

    // Показываем главное окно
    mainWindow->show();

    // Закрываем текущее окно
    this->close();
}


void ScheduleWindow::onCellPressed(int row, int column) {
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
    qDebug() << "Cell pressed at row:" << row << ", column:" << column;

    // Циклически меняем состояние ячейки
    if (state == 0) {
        // Устанавливаем изображение звездочки
        item->setData(Qt::UserRole, 1);  // Устанавливаем состояние как "грустный смайлик"
        QLabel *label = new QLabel();
        label->setPixmap(starScaled);  // Устанавливаем изображение
        ui->tableWidget->setCellWidget(row, column, label);
    } else if (state == 1) {
        // Устанавливаем изображение грустного смайлика
        item->setData(Qt::UserRole, 2);  // Устанавливаем состояние как "пусто"
        QLabel *label = new QLabel();
        label->setPixmap(sadScaled);  // Устанавливаем изображение
        ui->tableWidget->setCellWidget(row, column, label);
    } else {
        // Очищаем ячейку
        item->setData(Qt::UserRole, 0);  // Устанавливаем состояние как "звезда"
        ui->tableWidget->removeCellWidget(row, column);  // Удаляем виджет из ячейки
    }
}
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>

void ScheduleWindow::saveDataToJson()
{
    QString filePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/data.json";
    QFile saveFile(filePath);

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qDebug() << "Couldn't open save file.";
        return;
    }

    QJsonArray jsonArray;

    // Сохраняем данные из таблицы
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        QJsonObject rowObject;

        for (int column = 0; column < ui->tableWidget->columnCount(); ++column) {
            QTableWidgetItem *item = ui->tableWidget->item(row, column);
            if (item) {
                rowObject[QString("column_%1").arg(column)] = item->data(Qt::UserRole).toInt();  // Исправлено на Qt::User Role
                qDebug() << "Saving data from cell (" << row << ", " << column << "): " << item->data(Qt::UserRole).toInt();  // Отладочное сообщение
            }
        }

        jsonArray.append(rowObject);
    }

    QJsonDocument saveDoc(jsonArray);
    saveFile.write(saveDoc.toJson());

    qDebug() << "Saved JSON data: " << saveDoc.toJson();
    saveFile.close();
    qDebug() << "Data saved to JSON successfully!";
}

void ScheduleWindow::loadDataFromJson() {
    QString filePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/data.json";
    QFile loadFile(filePath);

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qDebug() << "Couldn't open load file.";
        return;
    }

    QByteArray jsonData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(jsonData));
    QJsonArray jsonArray = loadDoc.array();
    loadFile.close();

    // Очищаем таблицу перед загрузкой новых данных
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(3);  // Убедитесь, что количество столбцов соответствует вашим данным

    for (int i = 0; i < jsonArray.size(); ++i) {
        QJsonObject rowObject = jsonArray[i].toObject();
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);  // Добавляем новую строку

        for (int column = 0; column < ui->tableWidget->columnCount(); ++column) {
            int state = rowObject[QString("column_%1").arg(column)].toInt();
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setData(Qt::UserRole, state);  // Устанавливаем состояние
            ui->tableWidget->setItem(row, column, item);

            // Устанавливаем виджет в ячейку в зависимости от состояния
            QLabel *label = new QLabel();  // Создаем QLabel
            if (state == 1) {
                label->setPixmap(QPixmap(":/images/star.png").scaled(60, 60, Qt::KeepAspectRatio));
            } else if (state == 2) {
                label->setPixmap(QPixmap(":/images/sad.png").scaled(60, 60, Qt::KeepAspectRatio));
            } else {
                ui->tableWidget->removeCellWidget(row, column);  // Удаляем виджет, если состояние "пусто"
                continue;  // Переходим к следующей ячейке
            }
            ui->tableWidget->setCellWidget(row, column, label);  // Устанавливаем QLabel в ячейку
        }
    }
    qDebug() << "Data loaded from JSON successfully!";
}
