#include "stageonefactory.h"

#include "simpleball.h"
#include "stageonetable.h"

#include <QColor>
#include <QVector2D>
#include <QJsonObject>
#include <QJsonValue>
#include <QString>

/**
 * @brief converts a value that is an object of the form {"x":float,"y":float} into a QVector2D with the appropriate values
 * @param v is the QJsonValue to convert

 */
QVector2D StageOneFactory::QJsonValueToVector2D(const QJsonValue &v, float defaultX = 0, float defaultY = 0) const {
    return QVector2D(v.toObject()["x"].toDouble(defaultX),v.toObject()["y"].toDouble(defaultY));
}

Ball *StageOneFactory::makeBall(const QJsonObject &config){
    //we kind of use a builder style setx, sety, etc, here but just because
    //it is easier than setting all the stuff in the constructor
    //this means we don't need any of the common stuff cluttering the SimpleBall class
    SimpleBall * ball = new SimpleBall();

    ball->setVelocity(QJsonValueToVector2D(config["velocity"]));
    ball->setRadius(config["radius"].toDouble(10));
    ball->setPosition(QJsonValueToVector2D(config["position"],ball->radius(),ball->radius()));
    ball->setMass(config["mass"].toDouble(1.0));
    ball->setColour(config["colour"].toString());

    return ball;
}

Table *StageOneFactory::makeTable(const QJsonObject &config) const {
    //not really worth doing the builder style with only 3 variables
    QVector2D dimensions = QJsonValueToVector2D(config["size"],300,600);
    float friction = config["friction"].toDouble();
    QColor colour = QColor(config["colour"].toString());

    return new StageOneTable(dimensions.x(),dimensions.y(),friction,colour);
}

