#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMediaPlayer>
#include <QAudioOutput>
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
    QMediaPlayer *player;
    QAudioOutput *audioOutput;

private slots:
    void openToDoList();
    void openSchedule();
    void closeEvent(QCloseEvent *event);


private:
    Ui::MainWindow *ui;
    QLabel *backgroundLabel;
};

#endif // MAINWINDOW_H
