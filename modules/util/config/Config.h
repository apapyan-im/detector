#pragma once

#include <string>

class Config {


public:
    explicit Config(std::string classesFile, std::string weightsFile, std::string modelConfiguration);

    std::string modelConfiguration;
    std::string weightsFile;
    std::string classesFile;
};


