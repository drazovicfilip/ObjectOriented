#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QPolygon>
#include <QTimer>
#include <vector>

#include "ball.h"

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

private:
    Ui::Dialog *ui;
    std::vector<Ball *> balls;
    int m_counter;
};

#endif // DIALOG_H
