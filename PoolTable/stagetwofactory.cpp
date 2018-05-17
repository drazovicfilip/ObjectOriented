#include "stagetwofactory.h"

#include "compositeball.h"
#include "leafball.h"
#include "stageonetable.h"
#include "stagetwopocket.h"
#include <float.h>

#include <QColor>
#include <QVector2D>
#include <QJsonObject>
#include <QJsonValue>
#include <QString>
#include <iostream>

void StageTwoFactory::setUpBall(Ball* ball, const QJsonObject &config){

    // *************
    // VELOCITY
    // *************
    float xVel = m_defaultVelocity.x();
    float yVel = m_defaultVelocity.y();
    if (config.contains("velocity")){
        if ((!config["velocity"].toObject()["x"].isDouble())){
            std::cerr << "Incorrect ball velocity X given, setting to a default value of " << m_defaultVelocity.x() << std::endl;
        }
        else{
            xVel = config["velocity"].toObject()["x"].toDouble();
        }
        if ((!config["velocity"].toObject()["y"].isDouble())){
            std::cerr << "Incorrect ball velocity Y given, setting to a default value of " << m_defaultVelocity.y() << std::endl;
        }
        else{
            yVel = config["velocity"].toObject()["y"].toDouble();
        }
    }
    else{
        std::cerr << "No ball velocity given, setting to a default value of (" << m_defaultVelocity.x() << ", " << m_defaultVelocity.y() << ")" << std::endl;
    }
    ball->setVelocity(QVector2D(xVel, yVel));

    // *************
    // RADIUS
    // *************

    if ((!config["radius"].isDouble()) || config["radius"].toDouble() <= 0){
        std::cerr << "Incorrect ball radius given, setting to a default value of " << m_defaultRadius << std::endl;
        ball->setRadius(m_defaultRadius);
    }
    else{
        ball->setRadius(config["radius"].toDouble());
    }

    // *************
    // POSITION
    // *************

    float xPos = m_defaultPosition.x();
    float yPos = m_defaultPosition.y();

    if (config.contains("position")){
        if ((!config["position"].toObject()["x"].isDouble())){
            std::cerr << "Incorrect ball position X given, setting to a default value of " << m_defaultPosition.x() << std::endl;
        }
        else{
            xPos = config["position"].toObject()["x"].toDouble();
        }
        if ((!config["position"].toObject()["y"].isDouble())){
            std::cerr << "Incorrect ball position Y given, setting to a default value of " << m_defaultPosition.y() << std::endl;
        }
        else{
            yPos = config["position"].toObject()["y"].toDouble();
        }
    }
    else{
        std::cerr << "No ball position given, setting to a default value of (" << m_defaultPosition.x() << ", " << m_defaultPosition.y() << ")" << std::endl;
    }
    ball->setPosition(QVector2D(xPos, yPos));

    // *************
    // MASS
    // *************

    if ((!config["mass"].isDouble()) || config["mass"].toDouble() <= 0){
        std::cerr << "Incorrect ball mass given, setting to a default value of " << m_defaultMass << std::endl;
        ball->setMass(m_defaultMass);
    }
    else{
        ball->setMass(config["mass"].toDouble());
    }

    // *************
    // COLOUR
    // *************

    if (!config["colour"].isString()){
        std::cerr << "Incorrect ball colour given, setting to a default value of " << m_defaultColour << std::endl;
        ball->setColour(QString::fromStdString(m_defaultColour));
    }
    else{
        ball->setColour(config["colour"].toString());
    }

    // *************
    // STRENGTH
    // *************

    if (config["strength"].toString() == "infinity"){
        ball->setStrength(FLT_MAX);
    }
    else{
        if ((!config["strength"].isDouble()) || config["strength"].toDouble() <= 0){
            std::cerr << "Incorrect ball strength given, setting to a default value of " << m_defaultStrength << std::endl;
            ball->setStrength(m_defaultStrength);
        }
        else{
            ball->setStrength(config["strength"].toDouble());
        }
    }
}

Ball *StageTwoFactory::makeLeafBall(const QJsonObject &config){
    Ball * ball = new LeafBall();
    setUpBall(ball, config);
    return ball;
}

Ball *StageTwoFactory::makeBall(const QJsonObject &config){
    Ball * ball = new CompositeBall();
    setUpBall(ball, config);
    return ball;
}

Table *StageTwoFactory::makeTable(const QJsonObject &config) const {

    // *************
    // SIZE
    // *************

    float x = m_defaultTableSize.x();
    float y = m_defaultTableSize.y();

    if (config.contains("size")){
        if ((!config["size"].toObject()["x"].isDouble()) || config["size"].toObject()["x"].toDouble() <= 0){
            std::cerr << "Incorrect table size X given, setting to a default value of " << m_defaultTableSize.x() << std::endl;
        }
        else{
            x = config["size"].toObject()["x"].toDouble();
        }
        if ((!config["size"].toObject()["y"].isDouble()) || config["size"].toObject()["y"].toDouble() <= 0){
            std::cerr << "Incorrect table size Y given, setting to a default value of " << m_defaultTableSize.y() << std::endl;
        }
        else{
            y = config["size"].toObject()["y"].toDouble();
        }
    }
    else{
        std::cerr << "No table size given, setting to a default value of (" << m_defaultTableSize.x() << ", " << m_defaultTableSize.y() << ")" << std::endl;
    }

    // *************
    // FRICTION
    // *************

    float friction = m_defaultFriction;

    if ((!config["friction"].isDouble()) || config["friction"].toDouble() < 0){
        std::cerr << "Incorrect table friction given, setting to a default value of " << m_defaultFriction << std::endl;
    }
    else{
        friction = config["friction"].toDouble();
    }

    // *************
    // COLOUR
    // *************

    QColor colour = QString::fromStdString(m_defaultTableColour);

    if ((!config["colour"].isString())){
        std::cerr << "Incorrect table colour given, setting to a default value of " << m_defaultTableColour << std::endl;
    }
    else{
        colour = config["colour"].toString();
    }

    return new StageOneTable(x,y,friction,colour);
}

Pocket *StageTwoFactory::makePocket(const QJsonObject &config) const {
    StageTwoPocket * pocket = new StageTwoPocket();

    // *************
    // POSITION
    // *************

    float xPos = -1;
    float yPos = -1;
    if (config.contains("position")){
        if ((!config["position"].toObject()["x"].isDouble()) || config["position"].toObject()["x"].toDouble() <= 0){
            std::cerr << "Incorrect pocket position X given, ignoring it." << std::endl;
        }
        else{
            xPos = config["position"].toObject()["x"].toDouble();
        }
        if ((!config["position"].toObject()["y"].isDouble()) || config["position"].toObject()["y"].toDouble() <= 0){
            std::cerr << "Incorrect pocket position X given, ignoring it." << std::endl;
        }
        else{
            yPos = config["position"].toObject()["y"].toDouble();
        }
    }
    else{
        std::cerr << "No pocket position given, ignoring it." << std::endl;
    }
    if (!(xPos == -1 || yPos == -1)){
        pocket->setPosition(QVector2D(xPos, yPos));
    }

    // *************
    // RADIUS
    // *************

    if ((!config["radius"].isDouble()) || config["radius"].toDouble() <= 0){
        std::cerr << "Incorrect pocket radius given, setting to a default value of " << m_defaultPocketRadius << std::endl;
        pocket->setRadius(m_defaultPocketRadius);
    }
    else{
        pocket->setRadius(config["radius"].toDouble());
    }

    return pocket;
}


