#include "gamebuilder.h"
#include "stagetwofactory.h"
#include "leafball.h"
#include <iostream>
#include <QJsonArray>

GameBuilder::GameBuilder(AbstractFactory *factory)
    :m_balls(),m_table(nullptr),m_factory(factory),m_hasCue(false)
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

Ball* GameBuilder::recursiveAddBall(Ball* ball, const QJsonObject &ballJSon)
{
    std::cout << "calling recursiveaddball on " << ballJSon["colour"].toString().toStdString() << std::endl;
    CompositeBall* compositeball = dynamic_cast<CompositeBall*>(ball);

    for (int i = 0; i < ballJSon.size(); i++)
    {
        if (ballJSon.contains("balls"))
        {
            QJsonArray innerballs = ballJSon["balls"].toArray();
            for (int b = 0; b < innerballs.size(); b++)
            {

                // TODO: their radius+distance from center must not be greater than the radius of their parent

                std::cout << "recurse" << std::endl;
                CompositeBall* newball = dynamic_cast<CompositeBall*>(m_factory->makeBall((innerballs[b]).toObject()));
                compositeball->addBall(newball);
                newball->setParent(true);
                recursiveAddBall(newball, (innerballs[b]).toObject());
            }
            return compositeball;
        }
        else
        {
            std::cout << "base case" << std::endl;
            return ((dynamic_cast<StageTwoFactory*>(m_factory))->makeLeafBall(ballJSon));
        }
    }
}

void GameBuilder::addBall(const QJsonObject &ballJSon, size_t stage)
{
    // If any part of a ball is placed off the table, print a warning message and ignore that ball
    float xPos = ballJSon["position"].toObject()["x"].toDouble();
    float yPos = ballJSon["position"].toObject()["y"].toDouble();
    float radius = ballJSon["radius"].toDouble();
    if (xPos <= radius || xPos + radius >= m_table->width() || yPos <= radius || yPos + radius >= m_table->height())
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
        if (stage == 1)
        {
            Ball* ball = m_factory->makeBall(ballJSon);
            m_balls.push_back(ball);
        }

        else{

            Ball * ball;

            ball = recursiveAddBall(m_factory->makeBall(ballJSon), ballJSon);

            if ((ballJSon["colour"].toString() == "white") && (hasCue() == false))
            {
                Ball* cue = new BallDecorator(ball);
                m_balls.insert(m_balls.begin(), std::move(cue));
            }
            else
            {
                m_balls.push_back(ball);
            }
        }
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


PoolGame *GameBuilder::getGame(size_t stage)
{
    //create the game and reset the member variables
    PoolGame * result = new PoolGame(m_table,m_balls,m_pockets,stage);
    m_table = nullptr;
    m_balls.clear();
    m_pockets.clear();

    return result;
}
