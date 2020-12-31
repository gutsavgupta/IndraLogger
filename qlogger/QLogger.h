/* @doc
 * filename: QLogger.h
 * author: ugupta
 * description
 * Defines default QLogger alias as QLoggerMain<DefaultQLoggerTypes>
 */

#pragma once

#include "QLoggerMain.h"
#include "QLoggerTypes.h"

// Macro headers
#include "utility/macroDefs/LogUtils.h"

namespace qlogger {

using QLogger = QLoggerMain<DefaultQLoggerTypes>;

} // namespace clogger
