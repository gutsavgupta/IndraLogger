/*******************************************************************
 * CLogger CloggerMain class
 *  created on:  3rd August 2019
 *  author:      utsav gupta
 ******************************************************************* 
 
 * @Description
 *
 * CloggerMain base class is designed to be a singleton object
 * CloggerMain base class has following functions on a high level
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

#ifndef CLOGGERMAIN_H_
#define CLOGGERMAIN_H_
namespace clogger{

template<typename LOGGER, typename DUMPER>
class CloggerMain
{
    public:
        using lid_t = LOGGER::LOGGER_ID;
        using did_t = DUMPER::DUMPER_ID:
    
    protected:
        // Containers Type definiton
        using CloggerMainPtr = std::unique_ptr<CloggerMain>;
        using LoggerPairType = std::pair<lid_t, LOGGER>;
        using LoggerContType = std::unordered_map<lid_t, LoggerPairType>;
        using DumperPairType = std::pair<did_t, DUMPER>;
        using DumperContType = std::unordered_map<did_t, DumperPairType>;

    public:
        // factory function
        CloggerMain& GetInstance();
        
        // Configure Function
        bool Configure(/*TODO insert config file*/);

        // Thread specific logger
        LoggerPairType GetLogger();

        // IdSpecific logger
        LoggerPairType GetLogger(lid_t loggerId);
        
        // Add Dumper in the logger
        bool AddDumper(DUMPER dumper);

        // Run logger for i steps (for i=-1, run indefinely)
        void run(int step = -1);

    protected:
        // proctected constructor so that this remain singleton
        CloggerMain();

    protected:
        CloggerMainPtr m_singleton;
        LoggerContType m_loggers;
        DumperContType m_dumpers;
};

} // namespace clogger
#endif 
