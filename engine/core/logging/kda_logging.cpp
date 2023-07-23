#include <kda_logging.h>
#include <spdlog/spdlog.h>

void ILogger::info(std::string_view string) {
	spdlog::info(string);
}

void ILogger::warning(std::string_view string) {
	spdlog::warn(string);
}

void ILogger::error(std::string_view string) {
	spdlog::error(string);
}

void ILogger::critical(std::string_view string) {
	spdlog::critical(string);
}
