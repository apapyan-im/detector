//
// Created by art on 11.10.20.
//

#include "Config.h"
#include <utility>

Config::Config(std::string classesFile, std::string weightsFile, std::string modelConfiguration) {
    this->modelConfiguration = std::move(modelConfiguration);
    this->weightsFile = std::move(weightsFile);
    this->classesFile = std::move(classesFile);

}
