/* @doc
 * filename: StringBuffer.h
 * author: ugupta
 * Description:
 * Defines simple string buffer to be used with
 * FastBuffer class for FastStream I/O operations
 */

#pragma once

#include <string>

namespace clogger {
namespace utility {

class StringBuffer : public std::string
{
public:
    using BaseT = std::string;
    using BaseT::BaseT;

    StringBuffer()
      : BaseT()
    {
        reset();
    }

    // interface required by FastBuffer
    bool  IncreaseSize();
    void  ResetBack(const char c = '\n');
    void  reset();
    char* begin();
    char* end();

private:
    static constexpr size_t s_initSize{ 1 << 11 };
};

inline bool StringBuffer::IncreaseSize()
{
    auto currSize = BaseT::size();
    auto newSize  = std::min(BaseT::max_size(), currSize << 1);

    if (currSize == newSize)
    {
        return false;
    }
    else
    {
        BaseT::resize(newSize, 0);
        return true;
    }
}

inline void StringBuffer::ResetBack(const char c)
{
    BaseT::back() = c;
}

inline void StringBuffer::reset()
{
    BaseT::resize(s_initSize, 0);
}

inline char* StringBuffer::begin()
{
    return &*BaseT::begin();
}

inline char* StringBuffer::end()
{
    return &*BaseT::end();
}

} // namespace utility
} // namespace clogger
