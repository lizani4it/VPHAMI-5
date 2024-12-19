#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>  // Для использования QLabel


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openToDoList();
    void openSchedule();


private:
    Ui::MainWindow *ui;
    QLabel *backgroundLabel;  // Объявляем переменную для QLabel
};

#endif // MAINWINDOW_H
