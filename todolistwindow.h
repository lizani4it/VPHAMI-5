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
    void showContextMenu(const QPoint &pos);
    void addRow();
    void removeRows();


protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::todolistwindow *ui;

    bool editMode;
    QPushButton *gearButton;
    QPushButton *checkButton;

    QSystemTrayIcon *trayIcon;
    QTimer *timer;
    bool isValidTime(const QString &time);
    void loadData();
    void saveData();
};

#endif // TODOLISTWINDOW_H
