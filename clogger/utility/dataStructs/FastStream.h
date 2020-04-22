/* @doc
 * filename: FastStream.h
 * author: ugupta
 * Description:
 * These classes define basic properties and function
 * for a stream to be fast, reusable and avoid copying
 * deleting data elements every time we need to reuse it
 */

#pragma once

#include <ios>
#include <iostream>

namespace clogger {
namespace utility {

template <typename BufferType>
class FastStream : public std::iostream
{
protected:
    using BaseT     = std::iostream;
    using BufferT   = BufferType;
    using char_type = BaseT::char_type;

public:
    FastStream()
      : BaseT(&m_buffer)
    {
    }

    FastStream(const FastStream&& rhs)
      : m_buffer(rhs.m_buffer)
      , BaseT(&m_buffer)
    {
    }

    // Additional interface required by
    // StreamDataUnit class
    FastStream& read(char_type* addr, std::streamsize n);

    void reset();

protected:
    BufferT m_buffer;
};

template <typename T>
inline FastStream<T>& FastStream<T>::read(char_type* addr, std::streamsize n)
{
    // Usually badbit or fail bit are set in fastStream
    // because of io error, when putting characters into
    // buffer class, however this is not the endofstream
    // so we will dump the containing data
    if (not eof() && not good())
    {
        clear();
    }
    BaseT::read(addr, n);
    return *this;
}

template <typename T>
inline void FastStream<T>::reset()
{
    m_buffer.reset();
    clear();
}

} // namespace utility
} // namespace clogger
