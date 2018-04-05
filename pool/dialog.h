#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QString>
#include <QPolygon>
#include <QTimer>
#include <QVector2D>
#include <vector>

#include <cmath>

#include "ball.h"
#include "table.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

public slots:
    void nextFrame();

protected:
    void paintEvent(QPaintEvent *event);
    void isCollisionBallTable(Ball* currentball);
    void isCollisionBallBall(Ball * currentball1, std::vector<Ball *> balls);

private:
    Ui::Dialog *ui;
    std::vector<Ball *> balls;
    Table table;
    int m_counter;
};

#endif // DIALOG_H
