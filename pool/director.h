#ifndef DIRECTOR_H
#define DIRECTOR_H

#include "poolbuilder.h"
#include <string>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class Director
{
public:
    Director(AbstractBuilder* builder);
    Pool construct();
    void readJson();

    float tablewidthJSON();
    float tableheightJSON();
    std::string tablecolourJSON();
    float frictionJSON();

    std::string ballcolourJSON(int index);
    float ballxPositionJSON(int index);
    float ballyPositionJSON(int index);
    float ballxVelocityJSON(int index);
    float ballyVelocityJSON(int index);
    float ballmassJSON(int index);
    float ballradiusJSON(int index);

private:
    AbstractBuilder* m_builder;
    QJsonArray ballsjson;
    QJsonObject tablejson;

};

#endif // DIRECTOR_H
