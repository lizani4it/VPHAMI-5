#ifndef TODOLISTWINDOW_H
#define TODOLISTWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QTimer>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QSqlDatabase>

namespace Ui {
class todolistwindow;
}

class todolistwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit todolistwindow(QWidget *parent = nullptr);
    ~todolistwindow();

private:
    Ui::todolistwindow *ui;
    bool editMode;
    QSystemTrayIcon *trayIcon;
    QTimer *timer;
    QPushButton *gearButton;
    QPushButton *checkButton;

    void initializeDatabase(); // Добавьте это объявление
    void saveData();
    void loadData();
    bool isValidTime(const QString &time);
    void updateEditModeLabel();
    void checkTimeAndNotify();

protected:
    void closeEvent(QCloseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void toggleEditMode();
    void showContextMenu(const QPoint &pos);
    void addRow();
    void removeRows();
    void saveChanges();
    void onBackButtonClicked();
    void onTimeEdited(int row, int column);
};

#endif // TODOLISTWINDOW_H
