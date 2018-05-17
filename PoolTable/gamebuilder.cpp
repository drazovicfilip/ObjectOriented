#include "gamebuilder.h"
#include "stagetwofactory.h"
#include "leafball.h"

#include <math.h>
#include <iostream>
#include <QJsonArray>

GameBuilder::GameBuilder(AbstractFactory *factory)
    : m_hasCue(false)
    , m_balls()
    , m_table(nullptr)
    , m_factory(factory)
{}

GameBuilder::~GameBuilder(){
    //in normal operation m_table is likely to be nullptr
    //and m_balls is likely to empty
    //this is only not the case if the director terminates the builder mid build
    delete m_table;
    for(Ball * b: m_balls){
        delete b;
    }
}


Ball* GameBuilder::recursiveAddBall(Ball* ball, const QJsonObject &ballJSon, bool childrenVisible){

    CompositeBall* compositeball = dynamic_cast<CompositeBall*>(ball);
    for (size_t i = 0; i < (size_t)ballJSon.size(); i++){

        // If the ball we're about to make will have any sub-balls
        if (ballJSon.contains("balls")){
            QJsonArray innerballs = ballJSon["balls"].toArray();

            // Traverse through all the children balls given in the JSON, making them and setting them as children of the given ball
            for (size_t b = 0; b < (size_t)innerballs.size(); b++){

                float ballRadius = innerballs[b].toObject()["radius"].toDouble(10.0);
                float parentRadius = compositeball->radius();
                float ballPositionX = innerballs[b].toObject()["position"].toObject()["x"].toDouble(0.0);
                float ballPositionY = innerballs[b].toObject()["position"].toObject()["y"].toDouble(0.0);

                // Their radius+distance from center must not be greater than the radius of their parent
                if (ballRadius + sqrt(pow(ballPositionX, 2) + pow(ballPositionY, 2)) > parentRadius){
                    std::cerr << "Ball outside parent, ignoring it." << std::endl;
                }

                else{
                    CompositeBall* newball = dynamic_cast<CompositeBall*>(m_factory->makeBall((innerballs[b]).toObject()));

                    // Add the new ball as a child of the parent ball
                    compositeball->addBall(newball);
                    compositeball->setChildrenVisible(childrenVisible);

                    // Make sure that strength is properly inherited from the parent
                    if (innerballs[b].toObject().contains("strength")){
                        newball->setStrength(innerballs[b].toObject()["strength"].toDouble());
                    }
                    else{
                        newball->setStrength(compositeball->strength());
                    }

                    // Some of the new ball's properties depend on its parent, so allocate them as well
                    newball->setVelocity(QVector2D(compositeball->velocity().x(), compositeball->velocity().y()));
                    newball->setPosition(QVector2D(compositeball->position().x(), compositeball->position().y()) + QVector2D(ballPositionX, ballPositionY));
                    newball->setColour(innerballs[b].toObject()["colour"].toString(ballJSon["colour"].toString()));

                    // If the new ball has any children, they are made also
                    recursiveAddBall(newball, (innerballs[b]).toObject(), childrenVisible);
                }
            }
            return compositeball;
        }

        // If there are no children, the ball is a leaf
        else{
            return ((dynamic_cast<StageTwoFactory*>(m_factory))->makeLeafBall(ballJSon));
        }
    }
    return compositeball;
}

void GameBuilder::addBall(const QJsonObject &ballJSon, size_t stage, bool childrenVisible){

    // If any part of a ball is placed off the table, print a warning message and ignore that ball
    float xPos = ballJSon["position"].toObject()["x"].toDouble();
    float yPos = ballJSon["position"].toObject()["y"].toDouble();
    float radius = ballJSon["radius"].toDouble();
    if (xPos <= radius || xPos + radius >= m_table->width() || yPos <= radius || yPos + radius >= m_table->height()){
        if (ballJSon["colour"].isString()){
            std::cerr << "Ignoring " << ballJSon["colour"].toString().toStdString() << " ball because it is outside the table." << std::endl;
        }
        else{
            std::cerr << "Ignoring current ball because it is outside the table." << std::endl;
        }
    }

    else{

        // Stage 1 of the assignment just makes a ball with no worrying about composites/children
        if (stage == 1){
            Ball* ball = m_factory->makeBall(ballJSon);
            m_balls.push_back(ball);
        }
        else{
            Ball * ball;

            // If there are children given in the JSON, they must be recursively added to the ball
            if (ballJSon.contains("balls")){
                ball = recursiveAddBall(m_factory->makeBall(ballJSon), ballJSon, childrenVisible);
            }

            // If there are no children, the current ball is a leaf
            else{
                ball = recursiveAddBall((dynamic_cast<StageTwoFactory*>(m_factory))->makeLeafBall(ballJSon), ballJSon, childrenVisible);
            }

            // If the current ball is the first white ball to appear, it is assigned to be the cue ball
            if ((ball->colour().name().toStdString() == "#ffffff") && (hasCue() == false)){

                // The cue ball uses the Decorator design pattern to draw the cue on top of it
                Ball* cue = new BallDecorator(ball);

                // The cue ball should have max strength no matter what
                cue->setStrength(FLT_MAX);
                m_balls.insert(m_balls.begin(), std::move(cue));
                setCue(true);
            }

            // If it is not a cue ball
            else{
                m_balls.push_back(ball);
            }
        }
    }
}

void GameBuilder::buildTable(const QJsonObject &tableJSon){

    // Since poolgame only has one table we delete the old one
    // This is a noop if m_table is nullptr
    delete m_table;
    m_table = m_factory->makeTable(tableJSon);
}

void GameBuilder::addPocket(const QJsonObject &pocketJson){
    m_pockets.push_back(((StageTwoFactory*)m_factory)->makePocket(pocketJson));
}


PoolGame *GameBuilder::getGame(size_t stage){
    // Create the game and reset the member variables
    PoolGame * result = new PoolGame(m_table,m_balls,m_pockets,stage);
    m_table = nullptr;
    m_balls.clear();
    m_pockets.clear();

    return result;
}
