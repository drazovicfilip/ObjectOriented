#include "dialog.h"
#include "ui_dialog.h"
#include <QRect>

#define fwidth 1000
#define fheight 600
#define outsidedist 50
#define tablethickness 20

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
    , m_ball(Ball(Coordinate(outsidedist+tablethickness, fheight/2, fheight, fwidth)))
{
    ui->setupUi(this);
    this->resize(fwidth,fheight);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer->start(16);
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

    m_ball.render(painter, m_counter);
}

void Dialog::nextFrame(){
    update();
}
