/*******************************************************************
 * CLogger CollectorBase class
 *  created on:  3rd August 2019
 *  author:      utsav gupta
 ******************************************************************* 
 
 * @Description
 *
 * CLogger collector base class is designed to be a singleton object
 * Clogger collector base class has following functions on a high level
 *
 *  > Maintains map of loggers
 *  > Maintains map of dumpers
 *  > Collect logs from loggers
 *  > Synchronize collected logs
 *  > Dump collected logs to the dumper
 *  > Maintains configuruer
 *  > TODO
 *******************************************************************/
/*******************************************************************
 *  TODO: @copyright statement
 *******************************************************************/

#ifndef COLLECTOR_H_
#define COLLECTOR_H_
namespace clogger{
namespace collector{

template<TYPES_DICT>
class CollectorBase
{
    public:
        using LOGGER_TYPE = TYPES_DICT::LOGGER_TYPE;
        using DUMPER_TYPE = TYPES_DICT::DUMPER_TYPE;

    public:

        // public functions
        // TODO
    private:
        // private functions
        // TODO
    private:
        // private data memebers
        // TODO
};

} // namespace collector
} // namespace clogger
#endif
