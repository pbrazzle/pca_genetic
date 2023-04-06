#ifndef ABSTRACT_JSON_FACTORY
#define ABSTRACT_JSON_FACTORY

#include <map>
#include <string>
#include <functional>

#include "JSONObject.hpp"

namespace JSON_IO
{
    template<typename T>
    using abstractFactory = std::function<std::unique_ptr<T>()>;

    template<typename T>
    using typenameMap = std::map<std::string, abstractFactory<T>>;

    template<typename T>
    std::unique_ptr<T> makeAbstractFromJSON(const typenameMap<T>& typeMap, const JSONObject& obj)
    {
        std::string typeString = obj["typename"].asString();
        auto derivedObj = typeMap.at(typeString)();
        derivedObj->fromJSON(obj["data"]);
        return std::move(derivedObj);
    }
}

template <typename Base, typename Derived>
std::unique_ptr<Base> makeDefaultDerived() { return std::unique_ptr<Base>(new Derived()); }

#endif