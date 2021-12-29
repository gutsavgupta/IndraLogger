#pragma once

#define LOG(logger, severity, text)                                            \
    {                                                                          \
        decltype(logger.WriteNext(severity)) bufferPtr =                       \
          logger.CheckSeverity(severity) ? logger.WriteNext(severity)          \
                                         : nullptr;                            \
        bufferPtr ? (void)((*bufferPtr) << text << '\n') : (void)(0);          \
        bufferPtr ? (void)(logger.WriteFinish()) : (void)(0);                  \
    }

#define QLOG(severity, text)                                                   \
    LOG(qlogger::QLogger::GetInstance().GetLogger(),                           \
        qlogger::Severity::severity,                                           \
        text)
