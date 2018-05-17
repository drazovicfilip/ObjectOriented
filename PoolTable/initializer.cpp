#include "initializer.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "stageonefactory.h"
#include "stagetwofactory.h"

QJsonObject jsonFromFile(const std::string &configFilePath)
{
    std::ifstream configFile(configFilePath);
    if(!configFile.good())
    {
        std::cerr << "could not open \"" << configFilePath <<"\"" <<std::endl;
        return QJsonObject();
    }

    std::stringstream ss;
    //associate the read buffer to the stringstream, so now string stream will use that buffer
    ss << configFile.rdbuf();
    std::string s = ss.str();
    QJsonDocument jsonDocConfig = QJsonDocument::fromJson(QByteArray::fromStdString(ss.str()));
    if(jsonDocConfig.isNull())
    {
        std::cerr << configFilePath <<" is not valid Json" << std::endl;
        return QJsonObject();
    }
    return jsonDocConfig.object();
}

void Initializer::addCompositeBalls(QJsonArray& balls, GameBuilder& builder, size_t stage)
{



    /*
    for(int i = 0; i < balls.size(); ++i)
    {
        if (balls[i].isArray())
        {
            std::cout << "composite" << std::endl;
        }
        else{

            std::cout << "adding" << std::endl;
            builder.addBall(balls[i].toObject(), stage);
        }


    }
    */


}

PoolGame *Initializer::createPoolgame(const std::string &configFilePath)
{
    size_t stage = 1;

    QJsonObject config = jsonFromFile(configFilePath);
    if(config.isEmpty())
        return nullptr;

    //here the correct factory for the builder to use is selected
    //there aren't explicit subclasses of builder, rather a state variable (the factory) is used
    //to provide different behavior for different stages, additional design patterns amirite?
    //don't need any logic yet to decide which factory to use

    AbstractFactory *factory;
    bool childrenVisible = config["childrenVisible"].toBool(false);

    if (config.contains("stage2"))
    {
        if (config["stage2"].toBool())
        {
            stage = 2;
            factory = new StageTwoFactory();
        }
        else{
            factory = new StageOneFactory();
        }
    }
    else{
        factory = new StageOneFactory();
    }

    GameBuilder builder(factory);

    if(config.contains("table"))
    {
        builder.buildTable(config["table"].toObject());
        if (stage == 2)
        {
            if (config["table"].toObject().contains("pockets"))
            {
                QJsonArray pockets = (config["table"].toObject()["pockets"].toArray());
                for (int i = 0; i < pockets.size(); ++i)
                {
                    builder.addPocket(pockets[i].toObject());
                }
            }
        }
    }
    else
    {
        std::cerr << "no \"table\" key found" <<std::endl;
        return nullptr;
    }

    if(config.contains("balls"))
    {
        QJsonArray balls = config["balls"].toArray();
        for(int i = 0; i < balls.size();++i)
        {
              builder.addBall(balls[i].toObject(), stage, childrenVisible);
        }

        // Move cue ball to the end of the list
        builder.reverseBalls();

    }
    else
    {
        std::cerr << "no \"ball\" key found" <<std::endl;
        return nullptr;
    }
    return builder.getGame(stage);
}
