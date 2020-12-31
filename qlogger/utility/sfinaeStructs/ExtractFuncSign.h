#pragma once

namespace qlogger {
namespace utility {

template <typename T>
struct ExtractFuncSign
{
    using Type = void;
};

template <typename U, typename S>
struct ExtractFuncSign<S U::*>
{
    using Type = S;
};

} // namespace utility
} // namespace qlogger

