#include "RectangleWidget.h"
#include <QVBoxLayout>
#include <QInputDialog>
#include <QFileDialog>
#include <QPixmap>
#include <QLabel>
#include <QPushButton>
#include <QPainter>
#include <QColor>
#include <QMessageBox>
#include <QSpacerItem>
#include <QMenu>
#include <QAction>

RectangleWidget::RectangleWidget(QWidget *parent, const QString &defaultImage, const QColor &color, int rectWidth, int rectHeight, const QString &text)
    : QWidget(parent), rectColor(color), width_(rectWidth), height_(rectHeight), defaultImagePath(defaultImage), currentImagePath(defaultImage)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);  // Фиксированная ширина, расширение по вертикали
    setFixedSize(width_, height_);

    QVBoxLayout *layout = new QVBoxLayout(this);

    imageLabel = new QLabel(this);
    imageLabel->setAlignment(Qt::AlignCenter);  // Центрируем картинку
    imageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);  // Разрешаем картинке заполнять пространство по вертикали, фиксируем высоту
    layout->addWidget(imageLabel);

    layout->addItem(new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Expanding));  // Отступ по вертикали

    QHBoxLayout *textAndButtonLayout = new QHBoxLayout();

    textLabel = new QLabel(text, this);  // Use the passed text
    textLabel->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    textLabel->setFont(QFont("Arial", 12, QFont::Bold));
    textAndButtonLayout->addWidget(textLabel);

    gearButton = new QPushButton("⚙", this);
    gearButton->setFixedSize(30, 30);
    gearButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    textAndButtonLayout->addWidget(gearButton);

    layout->addLayout(textAndButtonLayout);

    setLayout(layout);

    // Устанавливаем изображение по умолчанию
    setImage(QPixmap(defaultImagePath));  // Устанавливаем изображение по умолчанию

    connect(gearButton, &QPushButton::clicked, this, &RectangleWidget::showContextMenu);
}

void RectangleWidget::setText(const QString &text)
{
    textLabel->setText(text);  // Обновляем текст
}

void RectangleWidget::setImage(const QPixmap &image)
{
    if (!image.isNull()) {
        imageLabel->setPixmap(image.scaled(80, 80, Qt::KeepAspectRatio));
        currentImagePath = defaultImagePath;  // Устанавливаем путь к текущему изображению
    } else {
        qDebug() << "Не удалось установить изображение.";
    }
}


void RectangleWidget::showContextMenu()
{
    QMenu contextMenu(this);

    QAction *editTextAction = new QAction("Изменить текст", this);
    QAction *editImageAction = new QAction("Изменить картинку", this);
    QAction *resetImageAction = new QAction("Вернуть картинку", this);  // Новое действие для сброса картинки

    contextMenu.addAction(editTextAction);
    contextMenu.addAction(editImageAction);
    contextMenu.addAction(resetImageAction);  // Добавляем действие для сброса картинки

    connect(editTextAction, &QAction::triggered, this, &RectangleWidget::changeText);  // Выбор изменения текста
    connect(editImageAction, &QAction::triggered, this, &RectangleWidget::changeImage);  // Выбор изменения картинки
    connect(resetImageAction, &QAction::triggered, this, &RectangleWidget::resetImage);  // Сброс картинки

    contextMenu.exec(QCursor::pos());  // Показываем контекстное меню в текущей позиции курсора
}

void RectangleWidget::changeText()
{
    bool ok;
    QString newText = QInputDialog::getText(this, "Изменить задачу", "Введите новый текст:", QLineEdit::Normal, textLabel->text(), &ok);

    if (ok && !newText.isEmpty()) {
        textLabel->setText(newText);
    }
}

void RectangleWidget::changeImage()
{
    bool ok;
    QString text = QInputDialog::getItem(this, "Выбор действия", "Оставить текущую картинку или выбрать новую?",
                                         {"Оставить", "Выбрать"}, 0, false, &ok);

    if (ok && text == "Оставить") {
        qDebug() << "User  chose to keep the current image.";
        return;  // Завершаем функцию, не меняя ничего
    }
    else if (ok && text == "Выбрать") {
        QString imagePath = QFileDialog::getOpenFileName(this, "Выберите картинку", "", "Image Files (*.png *.jpg *.bmp)");

        if (!imagePath.isEmpty()) {
            QPixmap newImage(imagePath);
            if (!newImage.isNull()) {
                imageLabel->setPixmap(newImage.scaled(80, 80, Qt::KeepAspectRatio));
                currentImagePath = imagePath;  // Обновляем путь к изображению
            } else {
                qDebug() << "Не удалось загрузить новое изображение из пути:" << imagePath;
            }
        }
    }
}

void RectangleWidget::resetImage()
{
    QPixmap defaultImage(defaultImagePath);
    if (!defaultImage.isNull()) {
        imageLabel->setPixmap(defaultImage.scaled(80, 80, Qt::KeepAspectRatio));  // Сброс картинки на дефолтную
        currentImagePath = defaultImagePath;  // Сброс пути к картинке
        qDebug() << "Изображение сброшено на дефолтное.";
    } else {
        qDebug() << "Не удалось загрузить дефолтное изображение из пути:" << defaultImagePath;
    }
}


void RectangleWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QColor transparentColor = rectColor;
    transparentColor.setAlpha(100);

    painter.setBrush(QBrush(transparentColor));
    painter.setPen(Qt::NoPen);
    painter.drawRect(0, 0, width_, height_);

    QWidget::paintEvent(event);
}

QString RectangleWidget::getImagePath() const {
    return currentImagePath.isEmpty() ? defaultImagePath : currentImagePath;
}
