#ifndef STAGEONEFACTORY_H
#define STAGEONEFACTORY_H

#include <QJsonObject>

#include "abstractfactory.h"
#include "ball.h"
#include "table.h"
#include "pocket.h"

/**
 * @brief The StageOneFactory class creates concrete objects for stage one
 */
class StageOneFactory : public AbstractFactory
{
public:
    StageOneFactory(){}

    // AbstractFactory interface
public:
     QVector2D QJsonValueToVector2D(const QJsonValue &v, float defaultX, float defaultY) const;
    /**
     * @brief makes and returns a stageOneBall
     * @param config is the configuration for the ball in json format
     * @return a pointer to a valid stageOneBall
     */
    Ball *makeBall(const QJsonObject &config);

    /**
     * @brief makes and returns a stageOneTable
     * @param config is the configuration for the table in json format
     * @return a pointer to a valid stageOneTable
     */
    Table *makeTable(const QJsonObject &config) const;
};

#endif // STAGEONEFACTORY_H
