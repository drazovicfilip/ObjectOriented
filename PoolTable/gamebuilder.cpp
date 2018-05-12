#include "gamebuilder.h"
#include "stagetwofactory.h"
#include <iostream>

GameBuilder::GameBuilder(AbstractFactory *factory)
    :m_balls(),m_table(nullptr),m_factory(factory)
{

}
GameBuilder::~GameBuilder()
{
    //in normal operation m_table is likely to be nullptr
    //and m_balls is likely to empty
    //this is only not the case if the director terminates the builder mid build
    delete m_table;
    for(Ball * b: m_balls)
    {
        delete b;
    }
}

void GameBuilder::addBall(const QJsonObject &ballJSon)
{

    // If any part of a ball is placed off the table, print a warning message and ignore that ball
    float xPos = ballJSon["position"].toObject()["x"].toDouble();
    float yPos = ballJSon["position"].toObject()["y"].toDouble();
    float radius = ballJSon["radius"].toDouble();
    if (xPos <= radius || xPos - radius >= m_table->width() || yPos <= radius || yPos - radius >= m_table->height())
    {
        if (ballJSon["colour"].isString())
        {
            std::cerr << "Ignoring " << ballJSon["colour"].toString().toStdString() << " ball because it is outside the table." << std::endl;
        }
        else
        {
            std::cerr << "Ignoring current ball because it is outside the table." << std::endl;
        }

    }
    else{
        m_balls.push_back(m_factory->makeBall(ballJSon));
    }

}

void GameBuilder::buildTable(const QJsonObject &tableJSon)
{
    //since poolgame only has one table we delete the old one
    //this is a noop if m_table is nullptr
    delete m_table;
    m_table = m_factory->makeTable(tableJSon);
}


void GameBuilder::addPocket(const QJsonObject &pocketJson)
{
    m_pockets.push_back(((StageTwoFactory*)m_factory)->makePocket(pocketJson));
}


PoolGame *GameBuilder::getGame()
{
    //create the game and reset the member variables
    PoolGame * result = new PoolGame(m_table,m_balls, m_pockets);
    m_table = nullptr;
    m_balls.clear();
    m_pockets.clear();
    return result;
}
