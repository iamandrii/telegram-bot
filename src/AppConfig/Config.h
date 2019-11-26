#pragma once

#include "../libs/json.hpp"

using json = nlohmann::json;

namespace App{
	class Config{
	private:
	    json load;
	public:
	    Config(const char* config_file = "config.json");

	    template<typename T>
	    T get(const char* name){
	        return this->load[name].get<T>();
	    }

	    template<typename T>
	    void set(const char* name, T val){
	    	this->load[name] = val;
	    }
	};
}