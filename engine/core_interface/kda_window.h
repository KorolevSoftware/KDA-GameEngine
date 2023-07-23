#pragma once

namespace kdaWindow {

	struct Input {
		bool quit;
	};

	int initialize();
	void* get_nwh();
	int finalize();

	Input getPollEvent();
}