/*
 * Basic Dumper to dump the logs
 * virtual functions allowed
 */

#ifndef CDUMPER_H
#define CDUMPER_H

class CDumper
{
public:

proceted:
    virtual size_t dump(void *buffer, size_t bufferLen);
};

#endif
