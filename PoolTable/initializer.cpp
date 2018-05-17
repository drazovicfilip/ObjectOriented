#include "initializer.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "stageonefactory.h"
#include "stagetwofactory.h"

QJsonObject jsonFromFile(const std::string &configFilePath){
    std::ifstream configFile(configFilePath);
    if(!configFile.good()){
        std::cerr << "could not open \"" << configFilePath <<"\"" <<std::endl;
        return QJsonObject();
    }

    std::stringstream ss;
    //associate the read buffer to the stringstream, so now string stream will use that buffer
    ss << configFile.rdbuf();
    std::string s = ss.str();
    QJsonDocument jsonDocConfig = QJsonDocument::fromJson(QByteArray::fromStdString(ss.str()));
    if(jsonDocConfig.isNull()){
        std::cerr << configFilePath <<" is not valid Json" << std::endl;
        return QJsonObject();
    }
    return jsonDocConfig.object();
}

PoolGame *Initializer::createPoolgame(const std::string &configFilePath){
    size_t stage = 1;

    QJsonObject config = jsonFromFile(configFilePath);
    if(config.isEmpty())
        return nullptr;

    AbstractFactory *factory;
    bool childrenVisible = config["childrenVisible"].toBool(false);

    // Assign the factory depending on the stage that is given in the JSON
    if (config.contains("stage2")){
        if (config["stage2"].toBool()){
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

    // Check if a table is given in the JSON, and build it
    if(config.contains("table")){
        builder.buildTable(config["table"].toObject());

        // Check if pockets are given in the JSON, and build them
        if (stage == 2){
            if (config["table"].toObject().contains("pockets")){
                QJsonArray pockets = (config["table"].toObject()["pockets"].toArray());
                for (size_t i = 0; i < (size_t)pockets.size(); ++i){
                    builder.addPocket(pockets[i].toObject());
                }
            }
        }
    }
    else{
        std::cerr << "no \"table\" key found" <<std::endl;
        return nullptr;
    }

    // Check if balls are given in the JSON, and build them
    if(config.contains("balls")){
        QJsonArray balls = config["balls"].toArray();
        for(size_t i = 0; i < (size_t)balls.size();++i){
              builder.addBall(balls[i].toObject(), stage, childrenVisible);
        }

        // Move cue ball to the end of the list so that the cue renders on top of everything else
        builder.reverseBalls();

    }
    else{
        std::cerr << "no \"ball\" key found" <<std::endl;
        return nullptr;
    }
    return builder.getGame(stage);
}
