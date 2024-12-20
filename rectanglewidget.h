#ifndef RECTANGLEWIDGET_H
#define RECTANGLEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QColor>

class RectangleWidget : public QWidget
{
    Q_OBJECT

public:

 RectangleWidget(QWidget *parent, const QString &defaultImage, const QColor &color, int rectWidth, int rectHeight, const QString &text);
    void setText(const QString &text);
    void setImage(const QPixmap &image);
    QString getText() const { return textLabel->text(); }
    QString getImagePath() const;

    QString defaultImagePath;
    QString currentImagePath;

    QLabel *imageLabel;
    QLabel *textLabel;
    void resetImage();


public slots:
    void changeText();
    void changeImage();
    void showContextMenu();
    void paintEvent(QPaintEvent *event);

private:

    QPushButton *gearButton;

    QColor rectColor;
    int width_;
    int height_;

};

#endif // RECTANGLEWIDGET_H
