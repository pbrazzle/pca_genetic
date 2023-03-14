#include <iostream>
#include <cassert>

#include "JSONObject.hpp"

using GeneticJSON::JSONObject;

void testJSONInt()
{
	JSONObject intTest(10);
	assert(intTest.asInt() == 10);
	std::cout << "JSON asInt passed\n";
}

void testJSONBool()
{
	JSONObject boolTest(true);
	assert(boolTest.asBool() == true);
	std::cout << "JSON asBool passed\n";
}

void testJSONFloat()
{
	JSONObject floatTest(5.567);
	assert(floatTest.asFloat() == 5.567);
	std::cout << "JSON asFloat passed\n";
}

void testJSONString()
{
	JSONObject stringTest("Hello string");
	assert(stringTest.asString() == "Hello string");
	std::cout << "JSON asString passed\n";
}

void testJSONObject()
{
	JSONObject objectTest("{	\
		int : 10,				\
		bool: true,				\
		float: 5.567,			\
		string: \"Hello string\"}");
	assert(objectTest["int"].asInt() == 10);
	assert(objectTest["bool"].asBool() == true);
	assert(objectTest["float"].asFloat() == 5.567);
	assert(objectTest["string"].asString() == "Hello string");
	std::cout << "JSON object reading passed\n";
}

void testReadJSONArray()
{
	std::vector<JSONObject> objectArr = {JSONObject(0), JSONObject(1), JSONObject(2), JSONObject(3), JSONObject(4)};
	JSONObject arrObj(objectArr);
	auto objects = arrObj.asArray();
	for (int i = 0; i < 5; i++) assert(objects[i].asInt() == i);
	std::cout << "JSON array reading passed\n";
}

void testWriteJSONArray()
{
	
}

void testBuildingJSONObject()
{
	JSONObject buildTest;
	buildTest.addInt("test", 10);
	std::cout << buildTest.asJSON() << '\n';
	assert(buildTest["test"].asInt() == 10);
	
	buildTest.addString("string", "hello JSON");
	assert(buildTest["string"].asString() == "hello JSON");
	
	JSONObject readWrittenOutput(buildTest.asJSON());
	assert(readWrittenOutput["test"].asInt() == 10);
	assert(readWrittenOutput["string"].asString() == "hello JSON");

	std::cout << buildTest.asJSON() << '\n';
	std::cout << "JSON adding subobjects passed\n";
}

int main()
{
	std::cout << "Testing JSONObject...\n";
	
	JSONObject test;
	
	testJSONInt();
	testJSONBool();
	testJSONFloat();
	testJSONString();
	testJSONObject();
	testReadJSONArray();
	testWriteJSONArray();
	testBuildingJSONObject();
}