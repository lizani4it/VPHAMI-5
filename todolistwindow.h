#ifndef TODOLISTWINDOW_H
#define TODOLISTWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QSystemTrayIcon>
#include <QTimer>
#include <QTime>
#include <QWidget>
#include <QCloseEvent>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>

namespace Ui {
class todolistwindow;
}

class todolistwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit todolistwindow(QWidget *parent = nullptr);
    ~todolistwindow();

private slots:
    void toggleEditMode();
    void saveChanges();
    void checkTimeAndNotify();
    void onTimeEdited(int row, int column);
    void onBackButtonClicked();
    void updateEditModeLabel();
    void resizeEvent(QResizeEvent *event);
    void showContextMenu(const QPoint &pos);  // Добавляем слот для контекстного меню
    void addRow();  // Слот для добавления строки
    void removeRows();


protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::todolistwindow *ui;

    bool editMode;  // Переменная для отслеживания режима редактирования
    QPushButton *gearButton;  // Кнопка шестерёнки
    QPushButton *checkButton;  // Кнопка галочки

    QSystemTrayIcon *trayIcon;  // Иконка в системном трее
    QTimer *timer;
    bool isValidTime(const QString &time);
    void loadData();
    void saveData();
};

#endif // TODOLISTWINDOW_H
