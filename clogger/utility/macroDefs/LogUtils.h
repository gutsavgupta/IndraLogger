#pragma once

#define LOG(logger, severity, text)                                            \
    {                                                                          \
        decltype(logger.WriteNext(severity)) bufferPtr =                       \
          logger.CheckSeverity(severity) ? logger.WriteNext(severity)          \
                                         : nullptr;                            \
        bufferPtr ? (void)((*bufferPtr) << text << '\n') : (void)(0);          \
        bufferPtr ? (void)(logger.WriteFinish()) : (void)(0);                  \
    }

#define CLOG(severity, text)                                                   \
    LOG(clogger::Clogger::GetInstance().GetLogger(), severity, text)
