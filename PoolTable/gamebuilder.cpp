#include "gamebuilder.h"
#include "stagetwofactory.h"

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
    m_balls.push_back(m_factory->makeBall(ballJSon));
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
    PoolGame * result = new PoolGame(m_table,m_balls);
    m_table = nullptr;
    m_balls.clear();
    return result;
}
