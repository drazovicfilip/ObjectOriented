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
#include "pool.h"
#include "director.h"

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
    void isCollisionBallTable(Ball* currentball, Table* table);
    void isCollisionBallBall(Ball * currentball1, std::vector<Ball *> balls);

private:
    Ui::Dialog *ui;
    //std::vector<Ball *> balls;
    //Table table;
    Pool pool;
    int m_counter;
};

#endif // DIALOG_H
