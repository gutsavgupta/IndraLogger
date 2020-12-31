/* @doc
 * filename:    DumperTypes.h
 * author:      ugupta
 * Description:
 * DumperTypes contain default dumper type and
 * other types required to completely define dumper class
 */

#pragma once

#include "StreamDumper.h"

namespace qlogger {
namespace dumper {

struct DefaultDumperTypes
{
    using StreamT = std::ostream;
    using DumperT = StreamDumper<StreamT>;
};

} // namespace qlogger
} // namespace dumper
