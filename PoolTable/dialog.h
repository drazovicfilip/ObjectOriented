#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QWidget>
#include <QPaintEvent>
#include <QTimer>

#include "poolgame.h"

/**
 * @brief The Dialog class starts up and displays a poolgame
 */
class Dialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Dialog constructor
     * @param game is a pointer to a PoolGame, this takes ownership of that pointer
     * @param parent is the parent widget
     */
    explicit Dialog(PoolGame * game, QWidget *parent = 0);

    /**
     * @brief starts the simulation
     */
    void start();

    /**
     * @brief draws the simulation
     */
    void paintEvent(QPaintEvent *);

    /**
     * @brief keyPressEvent detects if the spacebar has been pressed, and toggles the children visibility
     * @param event
     */
    void keyPressEvent(QKeyEvent* event);
    ~Dialog();

public slots:
    void runSimulationStep();
private:
    PoolGame * m_game;
    QTimer * m_framerateTimer;
    QTimer * m_timestepTimer;
};

#endif // DIALOG_H
