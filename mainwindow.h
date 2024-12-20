#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>


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
    QLabel *backgroundLabel;
};

#endif // MAINWINDOW_H
