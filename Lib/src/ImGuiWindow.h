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
	class ImGuiWindow
	{
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

/*
int main() {
	std::shared_ptr<ImGUIWindow::Data> data;

#if WIN32
	data = std::make_shared<ImGUIWindow::Data>(new ImGUIWindow::Win32Api(&data->Run()));
	static_cast<ImGUIWindow::Win32Api*>(data->GetWindow())->SetWindowTitle("test window (vulkan win32 x64)");
#elif __linux__
	data = std::make_shared<ImGUIWindow::Data>(new ImGUIWindow::LinuxWindowApi(&data->Run()));
	static_cast<ImGUIWindow::LinuxWindowApi*>(data->GetWindow())->SetWindowTitle("test window (vulkan linux x64)");
#elif __APPLE__
	// unable to test/develop due to not having apple hard/software
	data = std::make_shared<ImGUIWindow::Data>(new ImGUIWindow::AppleRendering(&data->Run()));
#else
	return -1;
#endif // WIN32

	if (!data->GetWindow()->Init()) {
		return -1;
	}

	bool hideTitleBar = false;
	bool noCollapse = true;
	bool hideClose = true;

	ImGuiWindowFlags windowFlags = 0;
	windowFlags |= hideTitleBar ? ImGuiWindowFlags_NoTitleBar : windowFlags;
	windowFlags |= noCollapse ? ImGuiWindowFlags_NoCollapse : windowFlags;

	float f = 0;
	bool testWindow = true;
	bool showDemoWindow = true;

	while (data->Run()) {
		data->GetWindow()->BeginFrame();
		//------------------------------

		ImGui::Begin("test", NULL, windowFlags);
		ImGui::Text("Hello, world %d", 123);
		if (ImGui::Button("click me"))
		{
			auto cb = []() {
				fprintf(stderr, "button callback\n");
			};
			cb();
		}
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
		ImGui::End();

		ImGui::ShowDemoWindow(&showDemoWindow);

		//------------------------------
		data->GetWindow()->EndFrame();
	}

	data->GetWindow()->Destroy();
	return 0;
}
*/
