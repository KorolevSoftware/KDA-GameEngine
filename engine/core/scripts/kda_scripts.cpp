#include <kda_scripts.h>
#include <sol/sol.hpp>
#include <string_view>
#include <functional>

void start() {}
void end() {}

namespace kdaScripts {
	struct vars {
		int boop = 0;
	};

	int initialize() {
		std::array<std::function<void()>, 5> arr = { start, end };
		sol::state lua;
		lua.open_libraries();
		lua.script("local a = 3");
		lua.script("print(a)");
		return 0;
	}

	int finalize() {
		return 0;
	}
}