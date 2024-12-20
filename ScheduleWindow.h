#ifndef SCHEDULEWINDOW_H
#define SCHEDULEWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "RectangleWidget.h"
#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QTableWidget>



namespace Ui {
class ScheduleWindow;
}

class ScheduleWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ScheduleWindow(QWidget *parent = nullptr);
    ~ScheduleWindow();
    QVBoxLayout *leftLayout;


private slots:
    void onCellPressed(int row, int column);
    void onMenuCloseTriggered();
    void onBackButtonClicked();
    void saveDataToJson();
    void loadDataFromJson();
    void closeEvent(QCloseEvent *event);


private:
    Ui::ScheduleWindow *ui;
    QList<RectangleWidget*> rectangleWidgets;


};

#endif // SCHEDULEWINDOW_H
