#include "pch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace T34DB
{
    std::shared_ptr<spdlog::logger> Log::p_logger{ nullptr };


    int32_t Log::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        p_logger = spdlog::stdout_color_mt("T34DB");
        p_logger->set_level(spdlog::level::trace);

        return true;
    }

}
