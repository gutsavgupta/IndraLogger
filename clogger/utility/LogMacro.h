#pragma once

#define LOG(logger, severity, text)                                            \
    decltype(logger->WriteBuffer(severity)) bufferPtr =                        \
      (logger && logger->CheckSeverity(severity))                              \
        ? logger->WriteBuffer(severity)                                        \
        : nullptr;                                                             \
    bufferPtr ? (void)((*bufferPtr) << text << '\n') : (void)(0);              \
    bufferPtr ? (void)(logger->WriteFinish()) : (void)(0);

