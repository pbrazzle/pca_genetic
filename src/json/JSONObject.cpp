#include "JSONObject.hpp"

#include <algorithm>
#include <vector>
#include <iostream>
#include <cmath>

using JSON_IO::JSONObject;

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

JSONObject parseObjectFromString(std::string objString);

JSONObject readObjectFromList(std::string& listString)
{
	if (listString.size() == 0) return JSONObject();
	int bracketDepth = 0;

	std::string objString;
	char current = listString.front();
	do
	{
		if (current == '{' || current == '[') bracketDepth++;
		if (current == '}' || current == ']') bracketDepth--;

		objString += current;

		listString.erase(0, 1);
		if (listString.size() == 0) return parseObjectFromString(objString);
		current = listString.front();
	} while (current != ',' || bracketDepth);
	listString.erase(0, 1);
	return parseObjectFromString(objString);
}

std::pair<std::string, std::string> firstSplit(std::string val, char delim)
{
	std::pair<std::string, std::string> result;
	if (val.empty()) return result;

	while (val.front() != delim)
	{
		result.first += val.front();
		val.erase(0, 1);

		if (val.empty()) return result;
	}
	val.erase(0, 1);
	result.second = val;

	return result;
}

std::string bracketAwareSplit(std::string& listString)
{
	if (listString.empty()) return "";
	int bracketDepth = 0;

	std::string objString;
	char current = listString.front();
	do
	{
		if (current == '{' || current == '[') bracketDepth++;
		if (current == '}' || current == ']') bracketDepth--;

		objString += current;

		listString.erase(0, 1);
		if (listString.empty()) return objString;
		current = listString.front();
	} while (current != ',' || bracketDepth);
	listString.erase(0, 1);
	return objString;
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
		while (!objString.empty())
		{
			auto nextObjString = bracketAwareSplit(objString);
			arr.push_back(parseObjectFromString(nextObjString));
		}
		return JSONObject(arr);
	}

	if (objString[0] == '{')
	{
		JSONObject obj;
		auto noDelims = objString.substr(1, objString.size() - 2);

		while (!noDelims.empty())
		{
			auto nextSubObjString = bracketAwareSplit(noDelims);
			auto keyVal = firstSplit(nextSubObjString, ':');
			obj.addObject(keyVal.first, parseObjectFromString(keyVal.second));
		}

		return obj;
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
	if (value.size() == 0)
	{
		data = "null";
		return;
	}
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

JSONObject JSONObject::operator[](const std::string key) const
{
	if (!subObjects.count(key)) return JSONObject();
	return subObjects.at(key);
}

JSONObject JSONObject::operator[](const char* key) const
{
	return (*this)[std::string(key)];
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

	std::vector<JSONObject> objects;
	JSONObject nextObj = readObjectFromList(noDelims);
	while(nextObj)
	{
		objects.push_back(nextObj);
		nextObj = readObjectFromList(noDelims);
	}

	return objects;
}

bool JSONObject::isNull() const
{
	return data == "null";
}

JSONObject::operator bool() const
{
	return !isNull();
}