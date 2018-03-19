#include "dialog.h"
#include "ui_dialog.h"

dialog::dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::dialog)
    , m_ball(Ball(Coordinate(20, 20, 600), 20, -9.8, 2.7, 17))
    , m_counter(0)
{
    ui->setupUi(this);
    this->resize(1000,600);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer->start(32);
}

dialog::~dialog()
{
    delete ui;
}

void dialog::paintEvent(QPaintEvent *event)
{

    bool animation = true;

    // Bouncing ball animation
    if (animation) {
        QPainter painter(this);
        m_ball.render(painter, m_counter);
        m_counter++;
    }

    // The static house and sun drawing
    else{

        QPainter painter(this);

        QPen pen;
        pen.setWidth(3);
        pen.setColor(Qt::black);
        QBrush brush(Qt::yellow);

        painter.setPen (pen);
        painter.setBrush(brush);


        // x, y, sizeX, sizeY
        painter.drawEllipse(30, 30, 100, 100);

        brush.setColor("#C36241");
        painter.setBrush(brush);
        pen.setWidth(1);

        QPolygon roof;
        roof.putPoints(0, 3, 250, 260, 290, 220, 330, 260);
        painter.drawPolygon(roof);

        brush.setColor("#835C3B");
        painter.setBrush(brush);

        QPolygon house;
        house.putPoints(0, 4, 260, 260, 260, 299, 320, 299, 320, 260);
        painter.drawPolygon(house);

    }


}

void dialog::nextFrame(){
    update();
}
