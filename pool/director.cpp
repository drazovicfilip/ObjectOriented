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
    pool.setTable(m_builder->buildTable(tablewidthJSON(), tableheightJSON(), tablethickness, tablespace, 1));

    pool.addBall(m_builder->buildBall(Coordinate(fwidth/5, fheight/2, tableheightJSON(), tablewidthJSON()), "green", 1, 20, -3, -3));
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
        out << "size" << endl;
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

float Director::tablecolourJSON(){
    return 0;
}
float Director::frictionJSON(){
    return 0;
}
float Director::ballcolourJSON(int index){
    return 0;
}
float Director::ballxPositionJSON(int index){
    return 0;
}
float Director::ballyPositionJSON(int index){
    return 0;
}
float Director::ballxVelocityJSON(int index){
    return 0;
}
float Director::ballyVelocityJSON(int index){
    return 0;
}
float Director::ballmassJSON(int index){
    return 0;
}
float Director::ballradiusJSON(int index){
    return 0;
}


