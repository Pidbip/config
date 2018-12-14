/*
 * Config.h
 *
 *  Created on: Nov 19, 2017
 *      Author: pidbip
 */

#ifndef COMMON_CONFIG_H_
#define COMMON_CONFIG_H_


#include <map>
#include <string>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>


#include <exception>


class config {
public:
	/*
	 * Constructor
	 */
	explicit config(const std::string &filename);

	/*
	 * Destructor
	 */
	~config();

	/*
	 * method declaration get() with default value
	 * default_value - is default value
	 */
	template<typename T>
	T get(const std::string &property, T default_value) const;

	/*
	 * method declaration get()
	 * throw exception if property not found
	 */
	template<typename T>
	T get(const std::string &property) const;

	/*
	 * return true if property is exist
	 */
	bool isExist(const std::string &property) const;



private:
	std::map<std::string, std::string> m_map;
};

/*
* method definition get() with default value
* default_value - is default value
*/
template<typename T>
T config::get(const std::string &property, T default_value) const {
	T t;
	auto it = m_map.find(property);
	if (it == m_map.end()) {
		//Property not found.
		//Set default value.
		return default_value;
	}
	std::istringstream stream(it->second);
	stream >> t;

	return t;
}


/*
* method definition get()
* throw exception if property not found
*/
template<typename T>
T config::get(const std::string &property) const {
	T t;
	auto it = m_map.find(property);
	if (it == m_map.end())
		throw std::runtime_error("Config: Property not found.");
	std::istringstream stream(it->second);
	stream >> t;

	return t;
}

/*
* method get() - bool specialization
* throw exception if property not found
*
* FIXME: doesn't work correctly with O3 optimization
*/
template<>
inline bool config::get(const std::string &property) const {
	auto it = m_map.find(property);
	if (it == m_map.end())
		throw std::runtime_error("Config: Property not found.");

	if (it->second == "true") {
		return true;
	}
	else if (it->second == "false") {
		return false;
	}

	throw std::runtime_error("Config: Invalid property.");

	return false;
}

/*
* method get() - bool specialization with default value
* default_value - is default value
*/
template<>
inline bool config::get(const std::string &property, bool default_value)const {
	auto it = m_map.find(property);
	if (it == m_map.end()) {
		//Property not found.
		//Set default value.
		return default_value;
	}

	if (it->second == "true") {
		return true;
	}
	else if (it->second == "false") {
		return false;
	}

	//Invalid property.
	//Set default value.
	return default_value;
}

#endif /* COMMON_CONFIG_H_ */
