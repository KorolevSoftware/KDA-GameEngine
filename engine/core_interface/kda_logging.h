#pragma once
#include <string_view>

namespace ILogger {
	void info(std::string_view string);
	void warning(std::string_view string);
	void error(std::string_view string);
	void critical(std::string_view string);
}