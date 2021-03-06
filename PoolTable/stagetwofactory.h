#ifndef STAGETWOFACTORY_H
#define STAGETWOFACTORY_H

#include "abstractfactory.h"
#include "ball.h"
#include "table.h"
#include "pocket.h"

/**
 * @brief The StageTwoFactory class creates concrete objects for stage two of the assignment
 */
class StageTwoFactory : public AbstractFactory
{
public:

    StageTwoFactory()
        : m_defaultRadius(10.0)
        , m_defaultMass(1.0)
        , m_defaultColour("white")
        , m_defaultStrength(FLT_MAX)
        , m_defaultPosition(QVector2D(0,0))
        , m_defaultVelocity(QVector2D(0,0))
        , m_defaultTableColour("green")
        , m_defaultFriction(0.01)
        , m_defaultTableSize(QVector2D(600.0,300.0))
        , m_defaultPocketRadius(15.0)
    {}

public:

    /**
     * @brief setUpBall will apply a given JSON object full of ball properties to a given ball object. It will check every property for validity, and apply default values if required
     * @param ball
     * @param config
     */
    void setUpBall(Ball* ball, const QJsonObject &config);

    /**
     * @brief makeBall makes and returns a CompositeBall
     * @param config is the configuration for the ball in json format
     * @return a pointer to a valid CompositeBall
     */
    Ball *makeBall(const QJsonObject &config);

    /**
     * @brief makeLeafBall makes and returns a LeafBall
     * @param config is the configuration for the ball in json format
     * @return a pointer to a valid LeafBall
     */
    Ball *makeLeafBall(const QJsonObject &config);

    /**
     * @brief makes and returns a StageOneTable. It will check every property for validity, and apply default values if required.
     * @param config is the configuration for the table in json format
     * @return a pointer to a valid StageOneTable
     */
    Table *makeTable(const QJsonObject &config) const;

    /**
     * @brief makePocket makes and returns a Pocket. It will check every property for validity, and apply default values if required.
     * @param config is the configuration for the pocket in json format
     * @return a pointer to a valid pocket
     */
    Pocket *makePocket(const QJsonObject &config) const;

private:
    float m_defaultRadius;
    float m_defaultMass;
    std::string m_defaultColour;
    float m_defaultStrength;
    QVector2D m_defaultPosition;
    QVector2D m_defaultVelocity;
    std::string m_defaultTableColour;
    float m_defaultFriction;
    QVector2D m_defaultTableSize;
    float m_defaultPocketRadius;

};
#endif // STAGETWOFACTORY_H
