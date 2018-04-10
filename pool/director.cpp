#include "director.h"

#define tablespace 50
#define tablethickness 2

#include <QTextStream>

Director::Director(AbstractBuilder* builder)
    : m_builder(builder)
{
    readJson();
}

Pool Director::construct(){
    Pool pool = m_builder->getPool();
    pool.setTable(m_builder->buildTable(tablewidthJSON(), tableheightJSON(), tablethickness, tablespace, frictionJSON(), tablecolourJSON()));


    pool.addBall(m_builder->buildBall(Coordinate(ballxPositionJSON(0) + tablethickness + tablespace, ballyPositionJSON(0) + tablethickness + tablespace, tableheightJSON(), tablewidthJSON()), ballcolourJSON(0), ballmassJSON(0), ballradiusJSON(0), ballxVelocityJSON(0), ballyVelocityJSON(0)));
    pool.addBall(m_builder->buildBall(Coordinate(fwidth/5, fheight/3, tableheightJSON(), tablewidthJSON()), "green", 1, 20, 3, 1));
    pool.addBall(m_builder->buildBall(Coordinate(fwidth/5, fheight/4, tableheightJSON(), tablewidthJSON()), "green", 1, 20, -5, -3));

    pool.addBall(m_builder->buildBall(Coordinate(fwidth/4, fheight/2, tableheightJSON(), tablewidthJSON()), "red", 1, 20, 3, 1));
    pool.addBall(m_builder->buildBall(Coordinate(fwidth/4, fheight/4, tableheightJSON(), tablewidthJSON()), "red", 1, 20, 3, 2));

    //pool.addBall(m_builder->buildBall(Coordinate(fwidth/4, fheight/4, fheight, fwidth), "red", 1, 20, -3.25, 1.23));
    return pool;
}

void Director::readJson(){
    QFile file("config.json");

    if (!file.open(QFile::ReadOnly)){
        qWarning("Couldn't open JSON file");
        exit(EXIT_FAILURE);
    }

    QJsonDocument* document = new QJsonDocument(QJsonDocument::fromJson(file.readAll()));
    QJsonObject object = document->object();

    // Read table from JSON
    if (object.contains("table") && object["table"].isObject()){
        tablejson = object["table"].toObject();
    }
    else{
        qWarning("No table given in JSON file");
        exit(EXIT_FAILURE);
    }

    // Read balls array from JSON
    if (object.contains("balls") && object["balls"].isArray()){
        ballsjson = object["balls"].toArray();
    }
    else{
        qWarning("No balls given in JSON file");
        exit(EXIT_FAILURE);
    }

}

float Director::tablewidthJSON(){

    QTextStream out(stdout);

    if (tablejson.contains("size") && tablejson["size"].isObject()){
        QJsonObject size = tablejson["size"].toObject();
        if (size.contains("x") && size["x"].isDouble()){
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
float Director::tableheightJSON(){
    if (tablejson.contains("size") && tablejson["size"].isArray()){
        QJsonObject size = tablejson["size"].toObject();
        if (size.contains("y") && size["y"].isDouble()){
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

std::string Director::tablecolourJSON(){
    if (tablejson.contains("colour") && tablejson["colour"].isString()){
        return tablejson["colour"].toString().toStdString();
    }
    else{
        return "green"; // default colour
    }
}
float Director::frictionJSON(){
    if (tablejson.contains("friction") && tablejson["friction"].isDouble()){
        return tablejson["friction"].toDouble();
    }
    else{
        return 1; // default friction
    }
}
std::string Director::ballcolourJSON(int index){
    if (ballsjson[index].toObject().contains("colour") && ballsjson[index].toObject()["colour"].isString()){
        return ballsjson[index].toObject()["colour"].toString().toStdString();
    }
    else{
        return "red"; // default colour
    }
}
float Director::ballxPositionJSON(int index){
    if (ballsjson[index].toObject().contains("position") && ballsjson[index].toObject()["position"].isObject()){
        QJsonObject object = ballsjson[index].toObject()["position"].toObject();
        if (object.contains("x") && object["x"].isDouble()){
            return object["x"].toDouble();
        }
        else{
            return tablewidthJSON()/2;
        }

    }
    else{
        return tablewidthJSON()/2; // default x position
    }
}
float Director::ballyPositionJSON(int index){
    if (ballsjson[index].toObject().contains("position") && ballsjson[index].toObject()["position"].isObject()){
        QJsonObject object = ballsjson[index].toObject()["position"].toObject();
        if (object.contains("y") && object["y"].isDouble()){
            return object["y"].toDouble();
        }
        else{
            return tableheightJSON()/2;
        }

    }
    else{
        return tableheightJSON()/2; // default y position
    }
}
float Director::ballxVelocityJSON(int index){
    if (ballsjson[index].toObject().contains("velocity") && ballsjson[index].toObject()["velocity"].isObject()){
        QJsonObject object = ballsjson[index].toObject()["velocity"].toObject();
        if (object.contains("x") && object["x"].isDouble()){
            return object["x"].toDouble();
        }
        else{
            return 1;
        }

    }
    else{
        return 1; // default x velocity
    }
}
float Director::ballyVelocityJSON(int index){
    if (ballsjson[index].toObject().contains("velocity") && ballsjson[index].toObject()["velocity"].isObject()){
        QJsonObject object = ballsjson[index].toObject()["velocity"].toObject();
        if (object.contains("y") && object["y"].isDouble()){
            return object["y"].toDouble();
        }
        else{
            return 1;
        }

    }
    else{
        return 1; // default y velocity
    }
}
float Director::ballmassJSON(int index){
    if (ballsjson[index].toObject().contains("mass") && ballsjson[index].toObject()["mass"].isDouble()){
        return ballsjson[index].toObject()["mass"].toDouble();
    }
    else{
        return 1; // default mass
    }
}
float Director::ballradiusJSON(int index){
    if (ballsjson[index].toObject().contains("radius") && ballsjson[index].toObject()["radius"].isDouble()){
        return ballsjson[index].toObject()["radius"].toDouble();
    }
    else{
        return 10; // default radius
    }
}


