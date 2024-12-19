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
    // Метод для сброса картинки на дефолтную
    void resetImage();


public slots:
   // void toggleEditMode();  // Переключить режим редактирования
    void changeText();  // Изменить текст
    void changeImage();  // Изменить картинку
    void showContextMenu();
void paintEvent(QPaintEvent *event);    // Показать контекстное меню

private:

    QPushButton *gearButton;

      // Путь к дефолтной картинке
    QColor rectColor;
    int width_;
    int height_;

     // Состояние изображения (например, "star", "sad", etc.)
};

#endif // RECTANGLEWIDGET_H
