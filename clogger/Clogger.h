/* @doc
 * filename: Clogger.h
 * author: ugupta
 * description
 * Defines default Clogger alias as CloggerMain<DefaultCloggerTypes>
 */

#pragma once

#include <CloggerMain.h>
#include <CloggerTypes.h>

// Macro headers
#include <utility/macroDefs/LogUtils.h>

namespace clogger {

using Clogger = CloggerMain<DefaultCloggerTypes>;

} // namespace clogger
