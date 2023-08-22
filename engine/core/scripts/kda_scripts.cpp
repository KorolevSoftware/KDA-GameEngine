#include <kda_scripts.h>
#include <sol/sol.hpp>
#include <string_view>
#include <functional>

void start() {}
void end() {}


namespace kdaScripts {
	sol::state lua;
	struct vars {
		int boop = 0;
	};

	sol::table createNameSpace(std::string_view name) {
		return lua[name].get_or_create<sol::table>();
	}

	void runScript(std::string_view script) {
		lua.script(script);
	}

	int initialize() {

		std::array<std::function<void()>, 5> arr = { start, end };
		
		sol::table bark = createNameSpace("bark");
		int t = 0;
		bark["add"] = [&t](int m) {
			t = m;
		};
		lua.open_libraries(sol::lib::table);
		/*lua.script("bark.add(3)");
		lua.script("print(a)");*/
		
		return 0;
	}

	int finalize() {
		return 0;
	}
}