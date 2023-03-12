#include "JSONObject.hpp"

#include <algorithm>
#include <vector>
#include <iostream>

using GeneticJSON::JSONObject;

std::vector<std::string> split(std::string s, char delim)
{
	std::vector<std::string> splits;
	
	std::string subSplit;
	for (char c : s)
	{
		if (c == delim)
		{
			splits.push_back(subSplit);
			subSplit = "";
		}
		else subSplit += c;
	}
	splits.push_back(subSplit);
	
	return splits;
}

std::string trim(std::string s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);}));
	s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
	return s;
}

JSONObject::JSONObject() { }

JSONObject::JSONObject(std::string value)
{ 
	data = trim(value);
	if (data[0] == '{')
	{
		data = data.substr(1, data.size()-2);

		std::vector<std::string> subObjectStrings = split(data, ',');
		std::transform(subObjectStrings.begin(), subObjectStrings.end(), subObjectStrings.begin(), [](std::string s) {
			return trim(s);
		});
		
		for (std::string objectString : subObjectStrings)
		{
			std::vector<std::string> keyVal = split(objectString, ':');
			std::transform(keyVal.begin(), keyVal.end(), keyVal.begin(), [](std::string s) {
				return trim(s);
			});
			
			subObjects[keyVal[0]] = JSONObject(keyVal[1]);
		}
	}
}

void JSONObject::addObject(std::string key, JSONObject obj)
{
	subObjects[key] = obj;
	data = "{";
	for (auto keyVal : subObjects)
	{
		data += keyVal.first + ':' + keyVal.second.asJSON();
		data += ',';
	}
	data.pop_back();
	data += "}";
}

void JSONObject::addInt(std::string key, int val) { addObject(key, JSONObject(std::to_string(val))); }

void JSONObject::addFloat(std::string key, double val) { addObject(key, JSONObject(std::to_string(val))); }

void JSONObject::addBool(std::string key, bool val) { addObject(key, JSONObject(std::to_string(val))); }

void JSONObject::addString(std::string key, std::string val) { addObject(key, JSONObject('"'+val+'"')); }

std::string JSONObject::asJSON() const
{
	return data;
}

JSONObject JSONObject::operator[](std::string key) const
{
	return subObjects.at(key);
}

int JSONObject::asInt() const
{
	return std::stoi(data);
}

double JSONObject::asFloat() const
{
	return std::stod(data);
}

bool JSONObject::asBool() const
{
	if (data == "true") return true;
	return false;
}

std::string JSONObject::asString() const
{
	//Exclude double quotes
	return data.substr(1, data.size()-2);
}