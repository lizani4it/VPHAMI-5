#include "todolistwindow.h"
#include "ui_todolistwindow.h"
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QInputDialog>
#include <QRegularExpression>
#include <QSystemTrayIcon>
#include <QTime>
#include <QSettings>
#include <QTimer>
#include <QCloseEvent>
#include "mainwindow.h"
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include <QDateTime>
#include <QSystemTrayIcon>
#include <QVBoxLayout>

todolistwindow::todolistwindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::todolistwindow),
    editMode(false)
{
    ui->setupUi(this);
    setMinimumSize(1200, 900);
    setMaximumSize(1200, 900);

    loadData();


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

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/images/menu22.png"));
    trayIcon->setVisible(true);
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
    int tableY = (this->height() - tableHeight) / 2;

    ui->tableWidget->setGeometry(tableX, tableY, tableWidth, tableHeight);
    ui->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QMainWindow::resizeEvent(event);
}

todolistwindow::~todolistwindow()
{
    delete ui;
}

void todolistwindow::closeEvent(QCloseEvent *event)
{
    saveData();
    event->accept();
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
    QAction *removeRowsAction = new QAction ("Удалить строки", this);
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

void todolistwindow::checkTimeAndNotify()
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentTimeString = currentDateTime.toString("hh:mm");
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        QString timeString = ui->tableWidget->item(row, 0)->text();
        QString note = ui->tableWidget->item(row, 1)->text();
        if (currentTimeString == timeString) {
            trayIcon->showMessage("Время " + timeString, "Задача: " + note, QSystemTrayIcon::Information, 10000);
        }
    }
}

void todolistwindow::saveData()
{
    QSettings settings("MyCompany", "ToDoListApp");
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        settings.setValue(QString("row%1_time").arg(row), ui->tableWidget->item(row, 0)->text());
        settings.setValue(QString("row%1_note").arg(row), ui->tableWidget->item(row, 1)->text());
    }
}

void todolistwindow::loadData()
{
    QSettings settings("MyCompany", "ToDoListApp");
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        QString time = settings.value(QString("row%1_time").arg(row), "7:00").toString();
        QString note = settings.value(QString("row%1_note").arg(row), "Завтрак").toString();
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(time));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem (note));

        QTableWidgetItem *timeItem = ui->tableWidget->item(row, 0);
        if (timeItem) {
            timeItem->setTextAlignment(Qt::AlignCenter); // Устанавливаем выравнивание по центру
        }
    }
}

void todolistwindow::onTimeEdited(int row, int column)
{
    if (column == 0) {
        QString currentTime = ui->tableWidget->item(row, column)->text();
        if (!isValidTime(currentTime)) {
            ui->tableWidget->item(row, column)->setText("07:00");
            QMessageBox::warning(this, "Ошибка", "Время введено некорректно. Используйте формат ЧЧ:ММ.");
        }
    }
}
