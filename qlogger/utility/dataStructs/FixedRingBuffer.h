/* @doc
 * filename: FixedRingBuffer
 * author: ugupta
 * date: 30th March 2020
 * Description:
 * Simple implemetation for FixedRingBuffer
 * This buffer is not thread safe currently, however
 * we can use this with single reader and single write program
 */
#pragma once

#include <vector>

namespace qlogger {
namespace utility {

template <typename DataUnitType>
class FixedRingBuffer
{
public:
    static constexpr size_t MaxBufferSize{ 1ULL << 16 };
    using DataUnitT = DataUnitType;

public:
    FixedRingBuffer(size_t _size = MaxBufferSize) { SetSize(_size); }

    bool SetSize(size_t bufferSize);

    size_t NextIdx(size_t idx) { return (idx + 1) & m_size; }

    void clear() { m_head = m_tail = 0; }

    bool empty() { return m_tail == m_head; }

    bool filled() { return NextIdx(m_head) == m_tail; }

    DataUnitT* getHead() { return &(m_buffer.at(m_head)); }

    DataUnitT* getTail() { return &(m_buffer.at(m_tail)); }

    void incrHead() { m_head = (not filled()) ? NextIdx(m_head) : m_head; }
    void incrTail() { m_tail = (not empty()) ? NextIdx(m_tail) : m_tail; }

private:
    using ContainerT = std::vector<DataUnitT>;
    ContainerT m_buffer;
    size_t     m_head{ 0 };
    size_t     m_tail{ 0 };
    size_t     m_size{ 0 };
};

template <typename T>
bool FixedRingBuffer<T>::SetSize(size_t bufferSize)
{
    auto nextPowerOf2 = [](size_t a) -> size_t {
        --a;
        a |= a >> 1;
        a |= a >> 2;
        a |= a >> 4;
        a |= a >> 8;
        a |= a >> 16;
        return a;
    };

    if (bufferSize > MaxBufferSize)
    {
        return false;
    }

    m_size = nextPowerOf2(bufferSize);
    m_buffer.resize(m_size + 1);
    return true;
}

} // namespace utility
} // namespace qlogger
