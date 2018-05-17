#ifndef GAMEBUILDER_H
#define GAMEBUILDER_H

#include <QJsonObject>
#include <vector>

#include "poolgame.h"
#include "ball.h"
#include "table.h"
#include "pocket.h"
#include "abstractfactory.h"
#include "balldecorator.h"

/**
 * @brief The GameBuilder class is used to build a PoolGame object, To do this it uses a specific factory to create the components.
 * To change the type of poolgame created simply provide a different factory
 */
class GameBuilder
{
public:
    /**
     * @brief GameBuilder creates a gameBuilder object
     * @param factory is a pointer to a concrete implementation of AbstractFactory, GameBuilder takes ownership of this pointer
     */
    GameBuilder(AbstractFactory *factory);
    virtual ~GameBuilder();

    /**
     * @brief addBall adds a new ball to the game
     * @param ballJSon is the ball's information
     * @param stage is the stage of the assignment we're using, given in the JSON
     * @param childrenVisible is whether children balls should be visible or not, given in the JSON
     */
    void addBall(const QJsonObject &ballJSon, size_t stage, bool childrenVisible = false);

    /**
     * @brief recursiveAddBall is a recursive helper function to add all children balls to the game
     * @param ball is the parent ball
     * @param ballJSon is the ball's information
     * @param childrenVisible is whether or not the children should be visible when drawing
     * @return returns a pointer to the ball (with all its children and values set)
     */
    Ball* recursiveAddBall(Ball* ball, const QJsonObject &ballJSon, bool childrenVisible);

    /**
     * @brief builds the table for the game, this overwrites any previous calls to build table
     * @param tableJSon is the json configuration for the ball
     */
    void buildTable(const QJsonObject &tableJSon);

    /**
     * @brief getGame creates and returns a pointer to a PoolGame, the caller now has ownership of that pointer
     * @return pointer to the created poolgame
     */

    PoolGame* getGame(size_t stage);

    /**
     * @brief reverseBalls will reverse the balls, in order for the cue ball to be first. This means that the cue will be drawn over all other balls
     */
    void reverseBalls(){ std::reverse(m_balls.begin(), m_balls.end()); }

    /**
     * @brief addPocket adds a new pocket to the game, based on the given parameters
     * @param pocketJSon is the given parameters, from the JSON file
     */
    void addPocket(const QJsonObject &pocketJSon);

    /**
     * @brief hasCue returns whether or not the game currently has a cue ball allocated (there can only be one)
     * @return m_hasCue - boolean
     */
    bool hasCue() const { return m_hasCue; }

    /**
     * @brief setCue sets the game to have a cue ball allocated or not, depending on the given boolean
     * @param b - boolean
     */
    void setCue(const bool b) { m_hasCue = b; }

private:
    bool m_hasCue;
    std::vector<Ball*> m_balls;
    std::vector<Pocket*> m_pockets;
    Table *m_table;
    AbstractFactory *m_factory;
};

#endif // GAMEBUILDER_H
