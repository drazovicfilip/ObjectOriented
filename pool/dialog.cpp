#include "dialog.h"
#include "ui_dialog.h"
#include <QRect>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
    , m_ball(Ball(Coordinate(20, 20, 600, 1000)))
{
    ui->setupUi(this);
    this->resize(1000,600);
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
    pen.setWidth(20);
    pen.setColor("#643D1A");
    QBrush brush("#33641A");

    painter.setPen (pen);
    painter.setBrush(brush);

    QRect rect(50,50,900,500);
    painter.drawRect(rect);

    m_ball.render(painter, m_counter);
}

void Dialog::nextFrame(){
    update();
}
