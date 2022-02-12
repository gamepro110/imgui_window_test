#pragma once

#include "windowApis/BaseWindow.h"

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <memory>

namespace ImGUIWindow {
	class Data {
	public:
		Data(BaseWindow* win) :
			window(win),
			run(true)
		{}

	public:
		BaseWindow* GetWindow() { return window; }
		bool& Run() { return run; }

	private:
		BaseWindow* window;
		bool run;
	};
}