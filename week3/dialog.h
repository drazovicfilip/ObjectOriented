#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QPolygon>
#include <QTimer>

#include "ball.h"

namespace Ui {
class dialog;
}

class dialog : public QDialog
{
    Q_OBJECT

public slots:
    void nextFrame();

public:
    explicit dialog(QWidget *parent = 0);
    ~dialog();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::dialog *ui;
    Ball m_ball;
    int m_counter;
};

#endif // DIALOG_H
