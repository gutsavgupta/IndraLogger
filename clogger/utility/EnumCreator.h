#pragma once

/* @doc
 * EnumCreator.h : defines EnumCreator macro for defining simple
 * Enum type with stringify() functionality in built, apart from
 * this if we are not using stringigy, the performance impact is
 * minimal
 *
 * Main Methods
 *  - stringify()
 *
 * Known Limitation:
 *  - Only works for simple enum declaration not for value initalized
 *    Enum. For ex: enum {E1 = 1, E2 = 2 ..}
 */

#include <exception>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace clogger {
namespace utility {

template <typename EnumClass>
class Stringify
{
public:
    using Enum          = typename EnumClass::Enum;
    using ContainerType = typename std::unordered_map<Enum, std::string>;

public:
    static std::string& ConvertToString(Enum val)
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

protected:
    static bool parse()
    {
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
            for (auto itr = s_enumStringMap.begin();
                 itr != s_enumStringMap.end();
                 ++itr)
            {
                std::cout << itr->first << " :: " << itr->second
                          << "::" << std::endl;
            }
        };
        return true;
    }

    static std::string& ltrim(std::string& str)
    {
        return str.erase(0, str.find_first_not_of(whiteSpace));
    }

    static std::string& rtrim(std::string& str)
    {
        return str.erase(str.find_last_not_of(whiteSpace) + 1);
    }

    static std::string& trim(std::string& str) { return ltrim(rtrim(str)); }

protected:
    static constexpr const char* whiteSpace = " \t\n";
    static ContainerType         s_enumStringMap;
    static bool                  s_isParsed;
};

template <typename T>
typename Stringify<T>::ContainerType Stringify<T>::s_enumStringMap;

template <typename T>
bool Stringify<T>::s_isParsed{ false };

} // namespace utility
} // namespace clogger

#define EnumCreator(enumName, ...)                                             \
    struct enumName                                                            \
    {                                                                          \
        enum Enum                                                              \
        {                                                                      \
            __VA_ARGS__                                                        \
        };                                                                     \
                                                                               \
        static std::vector<Enum> GetEnumList()                                 \
        {                                                                      \
            return std::vector<Enum>{ __VA_ARGS__ };                           \
        }                                                                      \
                                                                               \
        static std::string GetEnumStr()                                        \
        {                                                                      \
            return std::string{ #__VA_ARGS__ };                                \
        }                                                                      \
                                                                               \
        constexpr enumName(Enum _enumVal)                                      \
          : m_enumVal(_enumVal)                                                \
        {                                                                      \
        }                                                                      \
        constexpr operator Enum() const { return m_enumVal; }                  \
                                                                               \
        std::string& stringify() { return stringify(m_enumVal); }              \
                                                                               \
        static std::string& stringify(Enum val)                                \
        {                                                                      \
            using StringifyType =                                              \
              typename clogger::utility::Stringify<enumName>;                  \
            return StringifyType::ConvertToString(val);                        \
        }                                                                      \
                                                                               \
    private:                                                                   \
        Enum m_enumVal;                                                        \
    };
