#include "todolistwindow.h"
#include "ui_todolistwindow.h"
#include <QMessageBox>
#include <QFileDialog>

ToDoListWindow::ToDoListWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToDoListWindow)
{
    ui->setupUi(this);
    connect(ui->btnBackToMenu, &QPushButton::clicked, this, &ToDoListWindow::backToMenu);
    // Заполнение таблицы 7x6
    ui->taskTable->setRowCount(7);
    ui->taskTable->setColumnCount(6);
}

ToDoListWindow::~ToDoListWindow()
{
    delete ui;
}

void ToDoListWindow::backToMenu() {
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
    this->close();
}

void ToDoListWindow::on_btnTaskSettings_clicked() {
    // Открыть диалог для изменения задачи
    QString taskText = QInputDialog::getText(this, "Изменить задачу", "Введите новый текст задачи:");
    if (!taskText.isEmpty()) {
        // Логика для изменения текста задачи
    }
}
