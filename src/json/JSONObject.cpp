#include "JSONObject.hpp"

#include <algorithm>
#include <vector>
#include <iostream>
#include <cmath>

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

JSONObject parseObjectFromString(std::string objString)
{
	if (objString == "null") return JSONObject();
	try
	{
		double d = std::stod(objString);
		if (floor(d) == d) return JSONObject((int) d);
		return JSONObject(d);
	} catch(...) { }
	if (objString == "true") return JSONObject(true);
	if (objString == "false") return JSONObject(false);
	
	if (objString[0] == '[')
	{
		objString = objString.substr(1, objString.size()-2);
		auto arrStrings = split(objString, ',');
		std::vector<JSONObject> arr;
		for (auto str : arrStrings) arr.push_back(parseObjectFromString(str));
		return JSONObject(arr);
	}
	
	return JSONObject(objString.substr(1, objString.size()-2));
}

JSONObject::JSONObject() : data("null") { }

JSONObject::JSONObject(const char* value) : JSONObject(std::string(value)) { }
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
			
			JSONObject parsedObj = parseObjectFromString(keyVal[1]);
			
			subObjects[keyVal[0]] = parsedObj;
		}
	}
	else
	{
		data = '"' + data + '"';
	}
}

JSONObject::JSONObject(int value) { data = std::to_string(value); }
			
JSONObject::JSONObject(bool value)
{
	if (value) data = "true";
	else data = "false";
}

JSONObject::JSONObject(double value) { data = std::to_string(value); }

JSONObject::JSONObject(std::vector<JSONObject> value)
{
	data = "[";
	for (auto obj : value) data += obj.asJSON() + ',';
	data.pop_back();
	data += ']';
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

void JSONObject::addInt(std::string key, int val) { addObject(key, JSONObject(val)); }

void JSONObject::addFloat(std::string key, double val) { addObject(key, JSONObject(val)); }

void JSONObject::addBool(std::string key, bool val) { addObject(key, JSONObject(val)); }

void JSONObject::addString(std::string key, std::string val) { addObject(key, JSONObject(val)); }

void JSONObject::addArray(std::string key, std::vector<JSONObject> arr) { addObject(key, JSONObject(arr)); }

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

std::vector<JSONObject> JSONObject::asArray() const
{
	if (data[0] != '[') return std::vector<JSONObject>();
	
	std::string noDelims = data.substr(1, data.size()-2);
	auto objectStrings = split(noDelims, ',');
	
	std::vector<JSONObject> objects;
	for (auto objString : objectStrings)
	{
		objects.push_back(parseObjectFromString(objString));
	}
	return objects;
}