#pragma once

#define LOG(logger, severity, text)                                            \
    auto bufferPtr = (logger && logger->CheckSeverity(severity))               \
                       ? logger->WriteBuffer()                                 \
                       : nullptr;                                              \
    bufferPtr ? (void)((*bufferPtr) << '\n' << text) : (void)(0);              \
    bufferPtr ? (void)(bufferPtr->WriteFinish()) : (void)(0);

