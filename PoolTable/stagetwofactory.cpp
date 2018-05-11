#include "stagetwofactory.h"

#include "stagetwoball.h"
#include "stagetwotable.h"
#include "stagetwopocket.h"

#include <QColor>
#include <QVector2D>
#include <QJsonObject>
#include <QJsonValue>
#include <QString>

/**
 * @brief converts a value that is an object of the form {"x":float,"y":float} into a QVector2D with the appropriate values
 * @param v is the QJsonValue to convert
 * @return the QVector2D that is encoded in the JSon
 */
QVector2D StageTwoFactory::QJsonValueToVector2D(const QJsonValue &v, float defaultX = 0, float defaultY = 0) const
{
    return QVector2D(v.toObject()["x"].toDouble(defaultX),v.toObject()["y"].toDouble(defaultY));
}

Ball *StageTwoFactory::makeBall(const QJsonObject &config) const
{
    //we kind of use a builder style setx, sety, etc, here but just because
    //it is easier than setting all the stuff in the constructor
    //this means we don't need any of the common stuff cluttering the stageTwoBall class
    StageTwoBall * ball = new StageTwoBall();

    ball->setVelocity(QJsonValueToVector2D(config["velocity"]));
    ball->setRadius(config["radius"].toDouble(10));
    ball->setPosition(QJsonValueToVector2D(config["position"],ball->radius(),ball->radius()));
    ball->setMass(config["mass"].toDouble(1.0));
    ball->setColour(config["colour"].toString());

    return ball;
}

Table *StageTwoFactory::makeTable(const QJsonObject &config) const
{
    //not really worth doing the builder style with only 3 variables
    QVector2D dimensions = QJsonValueToVector2D(config["size"],300,600);
    float friction = config["friction"].toDouble();
    QColor colour = QColor(config["colour"].toString());

    return new StageTwoTable(dimensions.x(),dimensions.y(),friction,colour);

}


Pocket *StageTwoFactory::makePocket(const QJsonObject &config) const
{
    StageTwoPocket * pocket = new StageTwoPocket();
    pocket->setPosition(QJsonValueToVector2D(config["position"],pocket->radius(),pocket->radius()));
    pocket->setRadius(config["radius"].toDouble(10));

    return pocket;
}


