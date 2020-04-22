/* @doc
 * filename: FastBuffer.h
 * author: ugupta
 * Description:
 * These classes define basic properties and function
 * for a buffer to be used in fastStream class
 */

#pragma once

#include <iostream>
#include <streambuf>

namespace clogger {
namespace utility {

template <typename BufferUnitType>
class FastBuffer : public std::streambuf
{
protected:
    using BaseT       = std::streambuf;
    using TraitsT     = typename BaseT::traits_type;
    using int_type    = typename BaseT::int_type;
    using char_type   = typename BaseT::char_type;
    using BufferUnitT = BufferUnitType;

public:
    FastBuffer() = default;

    // interface required by FastStream class
    void reset();

protected:
    // overriding below interface from
    // basic_iostream<charT>
    int_type underflow() override;
    int_type overflow(int_type = TraitsT::eof()) override;

    BufferUnitT m_buffer;
};

template <typename T>
auto FastBuffer<T>::underflow() -> int_type
{
    if (BaseT::egptr() >= BaseT::pptr())
    {
        return TraitsT::eof();
    }
    else
    {
        setg(BaseT::eback(), BaseT::egptr() + 1, BaseT::pptr());
        return TraitsT::to_int_type(*BaseT::egptr());
    }
}

template <typename T>
auto FastBuffer<T>::overflow(int_type ch) -> int_type
{
    auto oldSize = m_buffer.size();

    if (not m_buffer.IncreaseSize())
    {
        m_buffer.ResetBack('\n');
        std::cerr << __func__ << ":: log overflown for size greater than["
                  << m_buffer.size() << "] chars" << std::endl;
        return TraitsT::eof();
    }
    else
    {
        // set put area
        auto strPtr = static_cast<char_type*>(m_buffer.begin());
        auto curPtr = strPtr + oldSize;
        auto endPtr = strPtr + m_buffer.size();
        std::fill(curPtr, endPtr, '\0');
        BaseT::setp(curPtr, endPtr);

        // set get area
        auto gbck = BaseT::eback();
        auto gcur = BaseT::gptr();
        auto gend = BaseT::egptr();
        BaseT::setg(strPtr, strPtr + (gcur - gbck), strPtr + (gend - gbck));

        return BaseT::sputc(ch);
    }
}

template <typename T>
void FastBuffer<T>::reset()
{
    m_buffer.reset();

    // reset the put area
    auto strPtr = static_cast<char_type*>(m_buffer.begin());
    auto endPtr = static_cast<char_type*>(strPtr + m_buffer.size());

    std::fill(strPtr, endPtr, '\0');
    BaseT::setp(strPtr, endPtr);

    // reset the get area
    auto rendPtr = strPtr - 1;
    BaseT::setg(strPtr, rendPtr, rendPtr);
}

} // namespace utility
} // namespace clogger

