/*
 * Config.cpp
 *
 *  Created on: Nov 19, 2017
 *      Author: pidbip
 */

#include "config.h"

/*
 * Constructor
 */
config::config(const std::string &filename){
	std::ifstream cFile(filename);
	if (cFile.is_open()){
		std::string line;
		while(std::getline(cFile, line)){
			line.erase(remove_if(line.begin(), line.end(), ::isspace),line.end());
			if(line[0] == '#' || line.empty()) // find comment line and reject it
				continue;
			auto delimiterPos = line.find("=");
			auto endLine = line.find("#");
			auto property = line.substr(0, delimiterPos);
			std::string value;
			// reject chank after sharp sign
			if (endLine == line.npos) {
				value = line.substr(delimiterPos + 1);
			} else {
				value = line.substr(delimiterPos + 1, endLine - delimiterPos - 1);
			}
			
			//if string value property
			if(value[0] == '"')//Delete quotes
				value = value.substr(1, value.size() - 2);

			m_map.insert(std::make_pair(property, value));
		}
		cFile.close();
	} else {
		throw std::runtime_error("Unable to open config file.");
	}
}

/*
 * Destructor
 */
config::~config(){
}

/*
 * method get() - string specialization
 * throw exception if property not found
 */
template<>
const std::string& config::get(const std::string &property) const {
	auto it = m_map.find(property);
	if (it == m_map.end())
		throw std::runtime_error("Config: Property not found.");

	return it->second;
}

/*
 * method get() - string specialization with default value
 * default_value - is default value
 */
template<>
const std::string& config::get(const std::string &property, const std::string &default_value) const{
	auto it = m_map.find(property);
	if (it == m_map.end()){
		//Property not found.
		//Set default value.
		return default_value;
	}

	return it->second;
}

/*
 * return true if property is exist
 */
bool config::isExist(const std::string &property) const {
	return (m_map.find(property) != m_map.end());
}

