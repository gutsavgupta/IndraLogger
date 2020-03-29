/* @doc
 * filename: StreamDumper.h
 * Description:
 * Streamdumper is a class which is templated on ostream classes
 * and put the local buffer to the stream object
 */

#pragma once

#include <iostream>
#include <ostream>

namespace clogger {
namespace dumper {

template <typename StreamType>
class StreamDumper
{
public:
    using StreamT = StreamType;

public:
    static constexpr size_t MaxBufferLen{ 1ULL << 15 };

public:
    StreamDumper();

    StreamDumper(StreamT& stream)
      : m_stream(stream)
    {
    }

    char*  getBuffStart() { return m_buffer; }
    size_t getBuffMaxLen() const { return MaxBufferLen; }
    bool   dump(const char* buff, size_t len);

private:
    char     m_buffer[MaxBufferLen];
    StreamT& m_stream;
};

template <typename T>
bool StreamDumper<T>::dump(const char* buff, const size_t len)
{
    return m_stream.write(buff, len).good();
}

template <>
StreamDumper<std::ostream>::StreamDumper()
  : m_stream(std::cout)
{
}

} // namespace dumper
} // namespace clogger
