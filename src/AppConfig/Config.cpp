#include <fstream>
#include "Config.h"

using json = nlohmann::json;
using namespace App;

Config::Config(const char* config_file){
    std::ifstream i(config_file);
    i >> (this->load);
}