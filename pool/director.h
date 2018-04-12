#ifndef DIRECTOR_H
#define DIRECTOR_H

#include "poolbuilder.h"
#include <string>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#define tablespace 50
#define tablethickness 2

/**
 * @brief The Director will put together all needed objects into one big pool game. Will also parse JSON input.
 *
 * @author Filip Drazovic
 * @date April 2018
 *
 * In this case, there are multiple balls and a single table to be put in to the pool game.
 * These will be built (using the builder) and put together using construct().
 *
 * The director will also parse input from a given JSON file, named "config.JSON",
 * specifying the game's table and ball(s) with all parameters.
 */

class Director
{
public:
    Director(AbstractBuilder* builder);

    /**
     * @brief construct will make the balls and table required and put it in to a pool game
     * @return Returns the pool game
     */
    Pool construct();

    /**
     * @brief readJson will parse the JSON given in "config.JSON" in to a JSONArray of balls and JSONObject of the table
     */
    void readJson();

    /**
     * @brief tablewidthJSON will grab the width of the table from the given JSON file, or use a default
     * @return table width (float)
     */
    float tablewidthJSON();

    /**
     * @brief tableheightJSON will grab the height of the table from the given JSON file, or use a default
     * @return table height (float)
     */
    float tableheightJSON();

    /**
     * @brief tablecolourJSON will grab the colour of the table from the given JSON file, or use a default
     * @return table colour (string)
     */
    std::string tablecolourJSON();

    /**
     * @brief tablefrictionJSON will grab the friction of the table from the given JSON file, or use a default
     * @return table friction (float)
     */
    float frictionJSON();

    /**
     * @brief ballcolourJSON will grab the colour of the ball at the given index in the JSON file, or use a default
     * @param index
     * @return ball's colour (string)
     */
    std::string ballcolourJSON(int index);

    /**
     * @brief ballxPositionJSON will grab the x position of the ball at the given index in the JSON file, or use a default
     * @param index
     * @return ball's x position (float)
     */
    float ballxPositionJSON(int index);

    /**
     * @brief ballyPositionJSON will grab the y position of the ball at the given index in the JSON file, or use a default
     * @param index
     * @return ball's y position (float)
     */
    float ballyPositionJSON(int index);

    /**
     * @brief ballxVelocityJSON will grab the x velocity of the ball at the given index in the JSON file, or use a default
     * @param index
     * @return ball's x velocity (float)
     */
    float ballxVelocityJSON(int index);

    /**
     * @brief ballyVelocityJSON will grab the y velocity of the ball at the given index in the JSON file, or use a default
     * @param index
     * @return ball's y velocity (float)
     */
    float ballyVelocityJSON(int index);

    /**
     * @brief ballmassJSON will grab the mass of the ball at the given index in the JSON file, or use a default
     * @param index
     * @return ball's mass (float)
     */
    float ballmassJSON(int index);

    /**
     * @brief ballradiusJSON will grab the radius of the ball at the given index in the JSON file, or use a default
     * @param index
     * @return ball's radius (float)
     */
    float ballradiusJSON(int index);

private:
    AbstractBuilder* m_builder;
    QJsonArray ballsjson;
    QJsonObject tablejson;

};

#endif // DIRECTOR_H
