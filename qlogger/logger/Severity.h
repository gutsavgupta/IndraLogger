/* @doc
 * filename:    Severity.h
 * author:      ugupta
 * Description:
 * Severity class defines the basic severity that can be used
 * via logger class and loggerTypes
 */

#pragma once

#include <utility/macroDefs/EnumCreator.h>

namespace qlogger {
namespace logger {

EnumCreator(Severity, NONE, CRIT, WARN, ALERT, ERROR, INFO, DATA, DEBUG, COUNT);

} // namespace utility
} // namespace qlogger
