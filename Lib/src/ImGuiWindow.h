#pragma once

#include "Data.h"
#include "windowApis/BaseWindow.h"
#include "Callbacks.h"

#if WIN32
#include "windowApis/Win32Api.h"
#elif __linux__
#include "windowApis/LinuxWindowApi.h"
#elif __APPLE__
#include "windowApis/mac.h"
#endif

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <memory>

namespace ImGUIWindow {
	class ImGuiWindow {
	public:
		ImGuiWindow(const std::string& windowTitle);
		~ImGuiWindow();

	public:
		bool Start(std::vector<fontWraper>& fonts);
		void Update();
		void AddSubWindow(CallbackBase* callback);

	private:
		Data* data{ nullptr };
		BaseWindow* window{ nullptr };
		std::vector<CallbackBase*> subWindows;
	};
}
