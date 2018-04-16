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

// Variables in milliseconds
#define simtime 16
#define frametime 32

/**
 * @brief The dialog class is the coordinator of the whole program.
 *
 * @author Filip Drazovic
 * @date April 2018
 *
 * It will perform all physics calculations and call upon objects to render themselves.
 * It will also initialise the pool table using the director/builder design method.
 */

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

// Simulation and framerate are decoupled - these two methods will update independently with their own timers.
public slots:

    /**
     * @brief nextFrame will render the next frame using each object's render method
     *
     * This will call the pool class' render method, which will use the render method of each ball and table.
     * The rendering rate (framerate) can be changed by altering the frametime variable
     */
    void nextFrame();

    /**
     * @brief simulate will calculate all physics and update positions/velocities of balls
     *
     * This involves calculating friction, checking to see if a ball has collided with the table and checking
     * to see if a ball has collided with another ball
     * The simulation rate can be changed by altering the simtime variable
     */
    void simulate();

protected:

    /**
     * @brief paintEvent will render the game, and is called every time nextFrame() is called
     * @param event
     */
    void paintEvent(QPaintEvent *event);

    /**
     * @brief isCollisionBallTable will check whether a given ball has collided with the table. If it has, it will reverse its velocity
     * @param currentball
     * @param table
     */
    void isCollisionBallTable(Ball* currentball, Table* table);

    /**
     * @brief isCollisionBallBall will check if a ball is colliding with any other ball. If it has, it'll calculate the updated velocities for each ball.
     * @param currentball1
     * @param balls
     */
    void isCollisionBallBall(Ball * currentball1, std::vector<Ball *> balls);

private:
    Ui::Dialog *ui;
    Pool pool;
};

#endif // DIALOG_H
