#include "dialog.h"
#include "ui_dialog.h"
#include <QRect>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{

    // Create 4 balls
    balls.push_back(new Ball(Coordinate(fwidth/2, fheight/2, fheight, fwidth), "blue", 1, 20, 1, 1));
    balls.push_back(new Ball(Coordinate(fwidth/3, fheight/3, fheight, fwidth), "green", 1, 20, -2, 3));
    balls.push_back(new Ball(Coordinate(fwidth/4, fheight/4, fheight, fwidth), "#ff1234", 1, 20, 3, 4));
    balls.push_back(new Ball(Coordinate(fwidth/5, fheight/5, fheight, fwidth), "#yellow", 1, 20, -4, 5));

    ui->setupUi(this);
    this->resize(fwidth,fheight);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer->start(8);
}

Dialog::~Dialog(){
    delete ui;
}

void Dialog::paintEvent(QPaintEvent *event){

    // Draw a simple table
    QPainter painter(this);

    QPen pen;
    pen.setWidth(tablethickness);
    pen.setColor("#643D1A");
    QBrush brush("#33641A");

    painter.setPen (pen);
    painter.setBrush(brush);

    QRect rect(outsidedist,outsidedist,(fwidth-2*outsidedist),(fheight-2*outsidedist));
    painter.drawRect(rect);

    for(Ball * currentball : balls){
        currentball->render(painter,m_counter);
        //delete currentball;
    }
}

void Dialog::nextFrame(){
    update();
}
