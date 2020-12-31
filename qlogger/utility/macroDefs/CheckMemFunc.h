/* @doc
 * filename: CheckMemFunc.h
 * author: ugupta
 * description:
 * CheckMemberFunction macro helps us to detect wheather a
 * class contains a function with /<name/> and /<signature/>
 * Uses basic sfinae rule to verify the same
 *
 * Note: Please use exact signature of function and not pointer
 *       types, example the sig for following functio
 *       func: void foo(int a, char b)
 *       sign: void (int a, char b)
 */

#pragma once

#include <type_traits>
#include <utility/sfinaeStructs/ExtractFuncSign.h>

#define CHECK_MEMBER_FUNC_EXIST(classT, funcName, funcSign)                    \
    struct check##funcName                                                     \
    {                                                                          \
        static constexpr void type(...) { return; }                            \
                                                                               \
        template <typename T, typename R = decltype(&T::funcName)>             \
        static constexpr auto type(T&&) ->                                     \
          typename qlogger::utility::ExtractFuncSign<R>::Type*                 \
        {                                                                      \
            return nullptr;                                                    \
        }                                                                      \
                                                                               \
        constexpr check##funcName()                                            \
        {                                                                      \
            using SigType = funcSign;                                          \
            static_assert(                                                     \
              std::is_same<SigType*,                                           \
                           decltype(type(std::declval<classT>()))>::value,     \
              "ERROR: No member " #classT "::" #funcName                       \
              " with signature:" #funcSign);                                   \
        }                                                                      \
    } tempObj##funcName;

