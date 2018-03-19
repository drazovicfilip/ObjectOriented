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
    painter.drawEllipse(30, 30, 100, 100);
}
