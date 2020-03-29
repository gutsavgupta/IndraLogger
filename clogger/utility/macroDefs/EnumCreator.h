/* @doc
 * filename: EnumCreator.h
 * author: ugupta
 * date: 29th March 2020
 * Description:
 * Creates Enum class with underlying enum, the enum class also provides
 * the strigify method to print the enum name
 */

#pragma once

#include <utility/dataStructs/StringifyEnum.h>

#include <string>
#include <vector>

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
        constexpr enumName(Enum _enumVal = static_cast<Enum>(0))               \
          : m_enumVal(_enumVal)                                                \
        {                                                                      \
        }                                                                      \
                                                                               \
        constexpr operator Enum() const { return m_enumVal; }                  \
                                                                               \
        std::string& stringify() const { return stringify(m_enumVal); }        \
                                                                               \
        static std::string& stringify(const Enum val)                          \
        {                                                                      \
            using StringifyType =                                              \
              typename clogger::utility::StringifyEnum<enumName>;              \
            return StringifyType::ConvertToString(val);                        \
        }                                                                      \
                                                                               \
    private:                                                                   \
        Enum m_enumVal;                                                        \
    };
