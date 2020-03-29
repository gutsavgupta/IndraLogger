/* @doc
 * filename: StringifyEnum.h
 * author: ugupta
 * date: 29th March 2020
 * Description:
 * Helps to define Enum with stringify() functionality in built, apart from
 * this if we are not using stringigy, the performance impact is minimal
 *
 * Main Methods
 *  - stringify()
 *
 * Known Limitation:
 *  - Only works for simple enum declaration not for value initalized
 *    Enum. For ex: enum {E1 = 1, E2 = 2 ..}
 *  - First Stringify comes with cost, rest are extracted from map
 */

#pragma once

#include <exception>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace clogger {
namespace utility {

template <typename EnumClass>
class StringifyEnum
{
public:
    using Enum          = typename EnumClass::Enum;
    using ContainerType = typename std::unordered_map<Enum, std::string>;

public:
    static std::string& ConvertToString(Enum val);

protected:
    static bool parse();

    static std::string& ltrim(std::string& str);
    static std::string& rtrim(std::string& str);
    static std::string& trim(std::string& str);

protected:
    static constexpr const char* whiteSpace = " \t\n";
    static ContainerType         s_enumStringMap;
    static bool                  s_isParsed;
};

template <typename T>
typename StringifyEnum<T>::ContainerType StringifyEnum<T>::s_enumStringMap;

template <typename T>
bool StringifyEnum<T>::s_isParsed{ false };

template <typename T>
std::string& StringifyEnum<T>::ConvertToString(Enum val)
{
    s_isParsed ? (void)0 : (void)(s_isParsed = parse());
    try
    {
        return s_enumStringMap.at(val);
    }
    catch (std::exception& e)
    {
        std::cerr << __func__ << ":: Exception:" << e.what() << std::endl;
        static std::string empty{};
        return empty;
    }
}

template <typename T>
bool StringifyEnum<T>::parse()
{
    using EnumClass = T;
    auto   enumStr  = EnumClass::GetEnumStr();
    auto   enumList = EnumClass::GetEnumList();
    size_t lastPos  = 0;

    try
    {
        for (auto enumVal : enumList)
        {
            auto nextPos = enumStr.find(',', lastPos);
            auto subStr  = enumStr.substr(lastPos, nextPos - lastPos);
            s_enumStringMap.emplace(enumVal, trim(subStr));
            lastPos = ++nextPos;
        }
    }
    catch (std::exception& e)
    {
        std::cerr << __func__ << ":: Exception:" << e.what() << std::endl;
        return false;
    }

    // Utility function to print enumMap, currently keeping it as lamda
    auto printEnumMap = [&]() -> void {
        for (auto itr = s_enumStringMap.begin(); itr != s_enumStringMap.end();
             ++itr)
        {
            std::cout << itr->first << " :: " << itr->second
                      << "::" << std::endl;
        }
    };
    return true;
}

template <typename T>
inline std::string& StringifyEnum<T>::ltrim(std::string& str)
{
    return str.erase(0, str.find_first_not_of(whiteSpace));
}

template <typename T>
inline std::string& StringifyEnum<T>::rtrim(std::string& str)
{
    return str.erase(str.find_last_not_of(whiteSpace) + 1);
}

template <typename T>
inline std::string& StringifyEnum<T>::trim(std::string& str)
{
    return ltrim(rtrim(str));
}

} // namespace utility
} // namespace clogger

