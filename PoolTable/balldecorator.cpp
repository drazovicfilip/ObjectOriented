#include "balldecorator.h"
#include <math.h>

BallDecorator::BallDecorator(Ball* ball)
    : m_ball(ball)
    , mousePressed(false)
    , mousePosition(-1, -1)
{}

void BallDecorator::draw(QPainter &p){

    // If the cue ball we're drawing has stopped, draw a cue (two lines) on top of it
    if (mousePressed && m_ball->velocity().x() == 0 && m_ball->velocity().y() == 0){
        const double mouseX = mousePosition.x();
        const double mouseY = mousePosition.y();

        // Draw the cue
        p.setPen(QPen(Qt::black, 4));
        p.drawLine(m_ball->position().x(), m_ball->position().y(), mouseX, mouseY);
        p.setPen(QPen(Qt::black, 2, Qt::DotLine));
        p.drawLine(m_ball->position().x(), m_ball->position().y(), m_ball->position().x() - ((mouseX) - m_ball->position().x()), m_ball->position().y() - ((mouseY) - m_ball->position().y()));
    }

    // Draw the ball itself
    m_ball->draw(p);
}

void BallDecorator::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){

        // Update the current mouse position, for use in drawing the cue in draw()
        mousePosition = QVector2D(event->x(), event->y());
        mousePressed = true;
    }
}

void BallDecorator::mouseMoveEvent(QMouseEvent *event){
    if ((event->buttons() & Qt::LeftButton) && mousePressed){

        // Update the current mouse position, for use in drawing the cue in draw()
        mousePosition = QVector2D(event->x(), event->y());
    }
}

void BallDecorator::mouseReleaseEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton && mousePressed){

        // Reset the mouse position
        mousePosition = QVector2D(-1, -1);
        mousePressed = false;

        // Fling the ball depending on how long the cue was when it was let go
        if (m_ball->velocity().x() == 0 && m_ball->velocity().y() == 0){
             m_ball->setVelocity(QVector2D(-3*(event->x()-m_ball->position().x()), -3*(event->y()-m_ball->position().y())));
        }
    }

}

