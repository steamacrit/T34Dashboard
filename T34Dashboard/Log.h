#pragma once

#include <spdlog/spdlog.h>

namespace T34DB
{
    class spdlog::logger;

    class Log
    {
    public:
        static int32_t Init();

        static inline std::shared_ptr<spdlog::logger> & GetLogger() { return p_logger; }

    private:
        static std::shared_ptr<spdlog::logger> p_logger;
    };

}

#ifdef _DEBUG
    #define LOG_DEBUG(...)  ::T34DB::Log::GetLogger()->debug(__VA_ARGS__)
    #define LOG_TRACE(...)  ::T34DB::Log::GetLogger()->trace(__VA_ARGS__)
    #define LOG_INFO(...)   ::T34DB::Log::GetLogger()->info(__VA_ARGS__)
    #define LOG_WARN(...)   ::T34DB::Log::GetLogger()->warn(__VA_ARGS__)
    #define LOG_ERROR(...)  ::T34DB::Log::GetLogger()->error(__VA_ARGS__)
    #define LOG_FATAL(...)  ::T34DB::Log::GetLogger()->critical(__VA_ARGS__)
#else
    #define LOG_DEBUG(...)  
    #define LOG_TRACE(...)  
    #define LOG_INFO(...)   
    #define LOG_WARN(...)   
    #define LOG_ERROR(...)  
    #define LOG_FATAL(...)  
#endif