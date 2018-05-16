#ifndef STAGETWOFACTORY_H
#define STAGETWOFACTORY_H

#include "abstractfactory.h"
#include "ball.h"
#include "table.h"
#include "pocket.h"

/**
 * @brief The StageTwoFactory class creates concrete objects for stage two
 */
class StageTwoFactory : public AbstractFactory
{
public:
    StageTwoFactory()
    {}

    // AbstractFactory interface
public:

     QVector2D QJsonValueToVector2D(const QJsonValue &v, float defaultX, float defaultY) const;
    /**
     * @brief makes and returns a CompositeBall
     * @param config is the configuration for the ball in json format
     * @return a pointer to a valid CompositeBall
     */
    Ball *makeBall(const QJsonObject &config);

    Ball *makeLeafBall(const QJsonObject &config);

    /**
     * @brief makes and returns a stageTwoTable
     * @param config is the configuration for the table in json format
     * @return a pointer to a valid stageTwoTable
     */
    Table *makeTable(const QJsonObject &config) const;

    Pocket *makePocket(const QJsonObject &config) const;

};
#endif // STAGETWOFACTORY_H
