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
        : m_hasCue(false)
    {}

    // AbstractFactory interface
public:

     QVector2D QJsonValueToVector2D(const QJsonValue &v, float defaultX, float defaultY) const;
    /**
     * @brief makes and returns a stageTwoBall
     * @param config is the configuration for the ball in json format
     * @return a pointer to a valid stageTwoBall
     */
    Ball *makeBall(const QJsonObject &config);

    /**
     * @brief makes and returns a stageTwoTable
     * @param config is the configuration for the table in json format
     * @return a pointer to a valid stageTwoTable
     */
    Table *makeTable(const QJsonObject &config) const;

    Pocket *makePocket(const QJsonObject &config) const;

    bool hasCue() const { return m_hasCue; }
    void setCue(const bool b) { m_hasCue = b; }

private:
    bool m_hasCue;
};
#endif // STAGETWOFACTORY_H
