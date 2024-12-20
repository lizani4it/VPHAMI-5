#include "todolistwindow.h"
#include "ui_todolistwindow.h"
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QInputDialog>
#include <QRegularExpression>
#include <QSystemTrayIcon>
#include <QTime>
#include <QTimer>
#include <QCloseEvent>
#include "mainwindow.h"
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include <QDateTime>
#include <QVBoxLayout>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QStandardPaths>

todolistwindow::todolistwindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::todolistwindow),
    editMode(false)
{
    ui->setupUi(this);
    setMinimumSize(1200, 900);
    setMaximumSize(1200, 900);

    initializeDatabase(); // Инициализация базы данных
    loadData(); // Загрузка данных из базы данных

    QPixmap backgroundPixmap(":/images/menu1.jpg");
    backgroundPixmap = backgroundPixmap.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(backgroundPixmap));
    this->setPalette(palette);

    ui->tableWidget->setRowCount(15);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setShowGrid(false);
    ui->tableWidget->setFixedHeight(550); // Установите желаемую ширину
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setStyleSheet("QTableWidget {background-color: rgba(255,255,255,0.5);}");
    ui->tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    gearButton = new QPushButton("⚙", this);
    gearButton->setGeometry(10, 30, 40, 40);
    gearButton->setStyleSheet("font-size: 20px;");
    connect(gearButton, &QPushButton::clicked, this, &todolistwindow::toggleEditMode);

    checkButton = new QPushButton("✔", this);
    checkButton->setGeometry(60, 30, 40, 40);
    checkButton->setStyleSheet("font-size: 20px;");
    checkButton->setEnabled(false);
    connect(checkButton, &QPushButton::clicked, this, &todolistwindow::saveChanges);

    connect(ui->backButton, &QPushButton::clicked, this, &todolistwindow::onBackButtonClicked);
    connect(ui->tableWidget, &QTableWidget::cellChanged, this, &todolistwindow::onTimeEdited);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/images/menu22.png"));
    trayIcon->setVisible(true);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &todolistwindow::checkTimeAndNotify);
    timer->start(60000);

    ui->editModeLabel->setVisible(false);
    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableWidget, &QWidget::customContextMenuRequested, this, &todolistwindow::showContextMenu);
}

void todolistwindow::initializeDatabase() {
    qDebug() << "Инициализация базы данных...";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/todolist.db";
    db.setDatabaseName(dbPath);

    qDebug() << "Путь к базе данных:" << dbPath;

    if (!db.open()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть базу данных: " + db.lastError().text());
        return;
    }

    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS tasks (id INTEGER PRIMARY KEY AUTOINCREMENT, time TEXT, note TEXT)")) {
        QMessageBox::critical(this, "Ошибка", "Не удалось создать таблицу: " + query.lastError().text());
    } else {
        qDebug() << "Таблица успешно создана или уже существует.";
    }
}

void todolistwindow::resizeEvent(QResizeEvent *event)
{
    int halfWidth = this->width() / 2;
    int firstColumnWidth = halfWidth * 0.45;
    int secondColumnWidth = halfWidth * 0.55;

    ui->tableWidget->setColumnWidth(0, firstColumnWidth);
    ui->tableWidget->setColumnWidth(1, secondColumnWidth);

    int tableWidth = firstColumnWidth + secondColumnWidth;
    int tableHeight = this->height() * 0.8;

    int tableX = (this->width() - tableWidth) / 2;
    int tableY = (this-> height() - tableHeight) / 2;

    ui->tableWidget->setGeometry(tableX, tableY, tableWidth, tableHeight);
    ui->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QMainWindow::resizeEvent(event);
}

todolistwindow::~todolistwindow()
{
    saveData(); // Сохраняем данные перед уничтожением
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection); // Закрываем соединение с базой данных
    delete ui;
}

void todolistwindow::closeEvent(QCloseEvent *event) {
    qDebug() << "Закрытие окна...";
    saveData(); // Сохраняем данные перед закрытием

    // Убедитесь, что база данных закрыта корректно
    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen()) {
        db.close();
        qDebug() << "База данных закрыта.";
    }

    event->accept(); // Принять событие закрытия
}

void todolistwindow::toggleEditMode()
{
    editMode = !editMode;
    ui->tableWidget->setEditTriggers(editMode ? QAbstractItemView::AllEditTriggers : QAbstractItemView::NoEditTriggers);
    checkButton->setEnabled(editMode);
    updateEditModeLabel();
    checkButton->setVisible(editMode);
}

void todolistwindow::updateEditModeLabel()
{
    if (editMode) {
        ui->editModeLabel->setText("<font color='red'><b>РЕЖИМ РЕДАКТИРОВАНИЯ ВКЛЮЧЕН</b></font>");
        ui->editModeLabel->setVisible(true);
    } else {
        ui->editModeLabel->setVisible(false);
    }
}

void todolistwindow::showContextMenu(const QPoint &pos)
{
    QMenu contextMenu(this);
    QAction *addRowAction = new QAction("Добавить строку", this);
    QAction *removeRowsAction = new QAction("Удалить строки", this);
    contextMenu.addAction(addRowAction);
    contextMenu.addAction(removeRowsAction);
    connect(addRowAction, &QAction::triggered, this, &todolistwindow::addRow);
    connect(removeRowsAction, &QAction::triggered, this, &todolistwindow::removeRows);
    contextMenu.exec(ui->tableWidget->mapToGlobal(pos));
}

void todolistwindow::addRow()
{
    if (ui->tableWidget->rowCount() < 15) {
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        // Устанавливаем элементы в таблицу
        QTableWidgetItem *timeItem = new QTableWidgetItem("07:00");
        QTableWidgetItem *noteItem = new QTableWidgetItem("Заметка");

        ui->tableWidget->setItem(row, 0, timeItem);
        ui->tableWidget->setItem(row, 1, noteItem);

        // Центрируем текст в первом столбце
        timeItem->setTextAlignment(Qt::AlignCenter);
    } else {
        QMessageBox::information(this, "Ошибка", "Невозможно добавить больше строк. Максимум 15.");
    }
}

void todolistwindow::removeRows()
{
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow != -1) {
        ui->tableWidget->removeRow(currentRow);
    } else {
        QMessageBox::information(this, "Ошибка", "Пожалуйста, выберите строку для удаления.");
    }
}

void todolistwindow::saveChanges()
{
    QString currentTime = ui->tableWidget->item(0, 0)->text();
    if (!isValidTime(currentTime)) {
        QMessageBox::warning(this, "Ошибка", "Время введено некорректно.");
        ui->tableWidget->item(0, 0)->setText("07:00");
        return;
    }
    QString newText = ui->tableWidget->item(0, 1)->text();
    editMode = false;
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    checkButton->setEnabled(false);
    ui->editModeLabel->setVisible(false);
}

bool todolistwindow::isValidTime(const QString &time)
{
    QRegularExpression regex("^(?:([01]?[0-9]|2[0-3]):([0-5]?[0-9]))$");
    QRegularExpressionMatch match = regex.match(time);
    if (!match.hasMatch()) {
        return false;
    }
    QStringList timeParts = time.split(":");
    int hours = timeParts[0].toInt();
    int minutes = timeParts[1].toInt();
    if (hours < 0 || hours > 23) {
        return false;
    }
    if (minutes < 0 || minutes > 59) {
        return false;
    }
    return true;
}

void todolistwindow::onBackButtonClicked()
{
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
    this->close();
}

void todolistwindow::checkTimeAndNotify() {
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentTimeString = currentDateTime.toString("hh:mm");
    qDebug() << "Текущее время:" << currentTimeString;

    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        if (ui->tableWidget->item(row, 0) != nullptr) {
            QString timeString = ui->tableWidget->item(row, 0)->text();
            QString note = ui->tableWidget->item(row, 1) ? ui->tableWidget->item(row, 1 )->text() : "";
            qDebug() << "Проверка времени для строки" << row << ": " << timeString;

            if (currentTimeString == timeString) {
                trayIcon->showMessage("Время " + timeString, "Задача: " + note, QSystemTrayIcon::Information, 10000);
                qDebug() << "Уведомление отправлено для задачи:" << note;
            }
        } else {
            qDebug() << "Элемент времени не найден в строке" << row;
        }
    }
}

void todolistwindow::saveData() {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "База данных не открыта. Невозможно сохранить данные.";
        return;
    }

    QSqlQuery query;

    // Удаляем старые данные
    if (!query.exec("DELETE FROM tasks")) {
        qDebug() << "Ошибка при удалении данных:" << query.lastError().text();
    }

    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        if (ui->tableWidget->item(row, 0) != nullptr && ui->tableWidget->item(row, 1) != nullptr) {
            QString time = ui->tableWidget->item(row, 0)->text();
            QString note = ui->tableWidget->item(row, 1)->text();

            query.prepare("INSERT INTO tasks (time, note) VALUES (?, ?)");
            query.addBindValue(time);
            query.addBindValue(note);
            if (!query.exec()) {
                qDebug() << "Ошибка при вставке данных:" << query.lastError().text();
            }
        }
    }
}

void todolistwindow::loadData() {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "База данных не открыта. Невозможно загрузить данные.";
        return;
    }

    QSqlQuery query("SELECT * FROM tasks");
    ui->tableWidget->setRowCount(0); // Очистите таблицу перед загрузкой данных

    while (query.next()) {
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);

        QString time = query.value("time").toString();
        QString note = query.value("note").toString();

        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(time));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(note));

        QTableWidgetItem *timeItem = ui->tableWidget->item(row, 0);
        if (timeItem) {
            timeItem->setTextAlignment(Qt::AlignCenter); // Устанавливаем выравнивание по центру
        }
    }
}

void todolistwindow::onTimeEdited(int row, int column) {
    if (column == 0) {
        if (ui->tableWidget->item(row, column) != nullptr) {
            QString currentTime = ui->tableWidget->item(row, column)->text();
            if (!isValidTime(currentTime)) {
                ui->tableWidget->item(row, column)->setText("07:00");
                QMessageBox::warning(this, "Ошибка", "Время введено некорректно. Используйте формат ЧЧ:ММ.");
            }
        } else {
            qDebug() << "Элемент не существует в строке" << row << "и столбце" << column;
        }
    }
}
