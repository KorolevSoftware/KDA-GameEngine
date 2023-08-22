#pragma once
#define SOL_ALL_SAFETIES_ON 1
#include <string_view>
#include <sol/sol.hpp>

namespace kdaScripts {
	int initialize();
	int finalize();
	

	sol::table createNameSpace(std::string_view name);
	void runScript(std::string_view script);
}