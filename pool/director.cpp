#include "director.h"

#include <QTextStream>

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

Director::Director(AbstractBuilder* builder)
    : m_builder(builder)
{
    readJson();
}

/**
 * @brief construct will make the balls and table required and put it in to a pool game
 * @return Returns the pool game
 */
Pool Director::construct(){

    // Initialise an empty pool game. Balls and a table will be added to this
    Pool pool = m_builder->getPool();

    // Make a new table from the JSON file parameters and add it to the pool game
    pool.setTable(m_builder->buildTable(tablewidthJSON(), tableheightJSON(), tablethickness, tablespace, frictionJSON(), tablecolourJSON()));

    // Make new balls from the JSON file parameters and add them to the pool game
    for (int i = 0; i < ballsjson.size(); i++){
        pool.addBall(m_builder->buildBall(Coordinate(ballxPositionJSON(i) + tablethickness + tablespace, ballyPositionJSON(i) + tablethickness + tablespace, tableheightJSON(), tablewidthJSON()), ballcolourJSON(i), ballmassJSON(i), ballradiusJSON(i), ballxVelocityJSON(i), ballyVelocityJSON(i)));
    }

    return pool;
}

/**
 * @brief readJson will parse the JSON given in "config.JSON" in to a JSONArray of balls and JSONObject of the table
 */
void Director::readJson(){

    // Open the JSON file. If it cannot be opened, return an error and exit.
    QFile file("config.json");
    if (!file.open(QFile::ReadOnly)){
        qWarning("Couldn't open JSON file");
        exit(EXIT_FAILURE);
    }

    // The file must be read to a document first before being put in to an object.
    QJsonDocument* document = new QJsonDocument(QJsonDocument::fromJson(file.readAll()));
    QJsonObject object = document->object();

    // Extract table object from the overall file object
    if (object.contains("table") && object["table"].isObject()){
        tablejson = object["table"].toObject();
    }
    else{
        qWarning("No table given in JSON file");
        exit(EXIT_FAILURE);
    }

    // Extract balls array from the overall file object
    if (object.contains("balls") && object["balls"].isArray()){
        ballsjson = object["balls"].toArray();
    }
    else{
        qWarning("No balls given in JSON file");
        exit(EXIT_FAILURE);
    }

}

/**
 * @brief tablewidthJSON will grab the width of the table from the given JSON file, or use a default
 * @return table width (float)
 */
float Director::tablewidthJSON(){

    // Extract the size object from the overall table object
    if (tablejson.contains("size") && tablejson["size"].isObject()){
        QJsonObject size = tablejson["size"].toObject();

        // Extract the x value of the size object from the overall table object
        if (size.contains("x") && size["x"].isDouble()){

            // Convert the size->x object to a float, accounting for the parts outside the table
            return (float)size["x"].toDouble() + tablespace + tablethickness;
        }
        else{
            return 1000; // default width
        }
    }

    else{
        return 1000; // default width
    }
}

/**
 * @brief tableheightJSON will grab the height of the table from the given JSON file, or use a default
 * @return table height (float)
 */
float Director::tableheightJSON(){

    // Extract the size object from the overall table object
    if (tablejson.contains("size") && tablejson["size"].isArray()){
        QJsonObject size = tablejson["size"].toObject();

        // Extract the y value of the size object from the overall table object
        if (size.contains("y") && size["y"].isDouble()){

            // Convert the size->y object to a float, accounting for the parts outside the table
            return (float)size["y"].toDouble() + tablespace + tablethickness;
        }
        else{
            return 600; // default height
        }
    }

    else{
        return 600; // default height
    }
}

/**
 * @brief tablecolourJSON will grab the colour of the table from the given JSON file, or use a default
 * @return table colour (string)
 */
std::string Director::tablecolourJSON(){

    // Extract the colour object from the overall table object
    if (tablejson.contains("colour") && tablejson["colour"].isString()){

        // Convert the colour object to a string
        return tablejson["colour"].toString().toStdString();
    }
    else{
        return "green"; // default colour
    }
}

/**
 * @brief tablefrictionJSON will grab the friction of the table from the given JSON file, or use a default
 * @return table friction (float)
 */
float Director::frictionJSON(){

    // Extract the friction object from the overall table object
    if (tablejson.contains("friction") && tablejson["friction"].isDouble()){

        // Convert the friction object to a number
        return tablejson["friction"].toDouble();
    }
    else{
        return 1; // default friction
    }
}

/**
 * @brief ballcolourJSON will grab the colour of the ball at the given index in the JSON file, or use a default
 * @param index
 * @return ball's colour (string)
 */
std::string Director::ballcolourJSON(int index){

    // Extract the colour object from the given ball object
    if (ballsjson[index].toObject().contains("colour") && ballsjson[index].toObject()["colour"].isString()){

        // Convert the colour object to a string
        return ballsjson[index].toObject()["colour"].toString().toStdString();
    }
    else{
        return "red"; // default colour
    }
}

/**
 * @brief ballxPositionJSON will grab the x position of the ball at the given index in the JSON file, or use a default
 * @param index
 * @return ball's x position (float)
 */
float Director::ballxPositionJSON(int index){

    // Extract the position object from the given ball object
    if (ballsjson[index].toObject().contains("position") && ballsjson[index].toObject()["position"].isObject()){
        QJsonObject object = ballsjson[index].toObject()["position"].toObject();

        // Extract the x object from the position object
        if (object.contains("x") && object["x"].isDouble()){

            // If the position is given as outside the table, return it to be inside the table
            if (object["x"].toDouble() >= tablewidthJSON()){
                return tablewidthJSON() - ballradiusJSON(index);
            }
            if (object["x"].toDouble() <= 0){
                return ballradiusJSON(index);
            }
            return object["x"].toDouble();
        }
        else{
            return tablewidthJSON()/2; // default x position
        }

    }
    else{
        return tablewidthJSON()/2; // default x position
    }
}


/**
 * @brief ballyPositionJSON will grab the y position of the ball at the given index in the JSON file, or use a default
 * @param index
 * @return ball's y position (float)
 */
float Director::ballyPositionJSON(int index){

    // Extract the position object from the given ball object
    if (ballsjson[index].toObject().contains("position") && ballsjson[index].toObject()["position"].isObject()){
        QJsonObject object = ballsjson[index].toObject()["position"].toObject();

        // Extract the y object from the position object
        if (object.contains("y") && object["y"].isDouble()){

            // If the position is given as outside the table, return it to be inside the table
            if (object["y"].toDouble() >= tableheightJSON()){
                return tableheightJSON() - ballradiusJSON(index);
            }
            if (object["y"].toDouble() <= 0){
                return ballradiusJSON(index);
            }
            return object["y"].toDouble();
        }
        else{
            return tableheightJSON()/2; // default y position
        }

    }
    else{
        return tableheightJSON()/2; // default y position
    }
}

/**
 * @brief ballxVelocityJSON will grab the x velocity of the ball at the given index in the JSON file, or use a default
 * @param index
 * @return ball's x velocity (float)
 */
float Director::ballxVelocityJSON(int index){

    // Extract the velocity object from the given ball object
    if (ballsjson[index].toObject().contains("velocity") && ballsjson[index].toObject()["velocity"].isObject()){
        QJsonObject object = ballsjson[index].toObject()["velocity"].toObject();

        // Extract the x object from the velocity object
        if (object.contains("x") && object["x"].isDouble()){

            // Convert the velocity -> x object to a number
            return object["x"].toDouble();
        }
        else{
            return 1; // default x velocity
        }

    }
    else{
        return 1; // default x velocity
    }
}


/**
 * @brief ballyVelocityJSON will grab the y velocity of the ball at the given index in the JSON file, or use a default
 * @param index
 * @return ball's y velocity (float)
 */
float Director::ballyVelocityJSON(int index){

    // Extract the velocity object from the given ball object
    if (ballsjson[index].toObject().contains("velocity") && ballsjson[index].toObject()["velocity"].isObject()){
        QJsonObject object = ballsjson[index].toObject()["velocity"].toObject();

        // Extract the y object from the velocity object
        if (object.contains("y") && object["y"].isDouble()){

            // Convert the velocity -> y object to a number
            return object["y"].toDouble();
        }
        else{
            return 1; // default y velocity
        }

    }
    else{
        return 1; // default y velocity
    }
}

/**
 * @brief ballmassJSON will grab the mass of the ball at the given index in the JSON file, or use a default
 * @param index
 * @return ball's mass (float)
 */
float Director::ballmassJSON(int index){

    // Extract the mass object from the given ball object
    if (ballsjson[index].toObject().contains("mass") && ballsjson[index].toObject()["mass"].isDouble()){

        // If the mass is negative, set it to a default value
        if (ballsjson[index].toObject()["mass"].toDouble() <= 0){
            return 1;
        }

        // Convert the mass object to a number
        return ballsjson[index].toObject()["mass"].toDouble();
    }
    else{
        return 1; // default mass
    }
}

/**
 * @brief ballradiusJSON will grab the radius of the ball at the given index in the JSON file, or use a default
 * @param index
 * @return ball's radius (float)
 */
float Director::ballradiusJSON(int index){

    // Extract the radius object from the given ball object
    if (ballsjson[index].toObject().contains("radius") && ballsjson[index].toObject()["radius"].isDouble()){

        // If the radius is negative or zero, set it to a default value
        if (ballsjson[index].toObject()["radius"].toDouble() <= 0){
            return 10;
        }

        // Convert the radius object to a number
        return ballsjson[index].toObject()["radius"].toDouble();
    }
    else{
        return 10; // default radius
    }
}


