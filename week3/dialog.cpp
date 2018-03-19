#include "dialog.h"
#include "ui_dialog.h"

dialog::dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::dialog)
{
    ui->setupUi(this);
    this->update();
}

dialog::~dialog()
{
    delete ui;
}

void dialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QPen pen;
    pen.setWidth(3);
    pen.setColor(Qt::black);
    QBrush brush(Qt::yellow);

    painter.setPen (pen);
    painter.setBrush(brush);


    // x, y, sizeX, sizeY
    painter.drawEllipse(30, 30, 100, 100);
}
