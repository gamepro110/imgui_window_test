#include "src/ImGuiWindow.h"
#include "../vendor/imgui/imgui.h"

#include <vector>
#include <string>

int MainProgram();
void demowin();
void testWin();

template<typename ... Args>
void testWinArgs(Args ... args) {
	ImGUIWindow::ArgUnwrapper<Args...> unwrap{ args... };
	std::vector<int>* nums = unwrap.template Get<std::vector<int>*, 0>();
	ImFont* font = (*unwrap.template Get<ImFont**, 1>());

	ImGui::Begin("arg test", NULL);
	static ImGuiTextFilter filter;
	filter.Draw();
	for (size_t i = 0; i < nums->size(); i++) {
		auto num = nums->at(i);
		std::string str{ "num: " + std::to_string(num) };
		if (filter.PassFilter(str.c_str())) {
			ImGui::PushFont(font);
			ImGui::Text(str.c_str());
			ImGui::PopFont();
		}
	}
	ImGui::Text("end");
	ImGui::End();

}

template<typename ... Args>
void test(Args ... args) {
	ImGUIWindow::ArgUnwrapper<Args...> unwrap{ args... };
	std::vector<int>* nums = unwrap.template Get<std::vector<int>*, 0>();
	
	static int s_num = 1;
	s_num++;
	nums->at(0) = s_num;
	nums->at(1) += 2;
}

/// <summary>
/// default main entry point
/// </summary>
int main() {
	return MainProgram();
}

/// <summary>
/// win32 consoleless entry point
/// </summary>
int WinMain() {
	return MainProgram();
}

int MainProgram() {
	ImGUIWindow::ImGuiWindow window("test");

	std::vector<int> nums{};
	for (size_t i = 0; i < 10; i++) {
		nums.emplace_back(i);
	}

	bool hideTitleBar = false;
	bool noCollapse = true;
	bool hideClose = true;

	ImGuiWindowFlags windowFlags = 0;
	windowFlags |= hideTitleBar ? ImGuiWindowFlags_NoTitleBar : windowFlags;
	windowFlags |= noCollapse ? ImGuiWindowFlags_NoCollapse : windowFlags;

	ImFont* custom{ nullptr };
	std::vector<ImGUIWindow::fontWraper> fonts;
	fonts.emplace_back(
		ImGUIWindow::fontWraper(
			custom,
			24,
			#if WIN32
			// different paths because different build enviroments
			std::string("../../../../Chiller.TTF")
			#elif __linux__
			std::string("../../Chiller.TTF")
			#endif
		)
	);

	if (!window.Start(fonts)) {
		std::cout << "Unable to start...\n";
		return -1;
	}

	ImGUIWindow::CallbackVoid demo = { &demowin };
	ImGUIWindow::CallbackVoid cb1 = { &testWin };
	ImGUIWindow::CallbackArg<std::vector<int>*, ImFont**> cb2 = { testWinArgs<std::vector<int>*, ImFont**>, &nums, &custom };
	ImGUIWindow::CallbackArg<std::vector<int>*> cb3 = { test<std::vector<int>*>, &nums };

	window.AddSubWindow(&demo);
	window.AddSubWindow(&cb1);
	window.AddSubWindow(&cb2);
	window.AddSubWindow(&cb3);

	//
	window.Update();

	return 0;
}

void demowin() {
	ImGui::ShowDemoWindow();
}

void testWin() {
	bool hideTitleBar = false;
	bool noCollapse = true;
	bool hideClose = true;

	ImGuiWindowFlags windowFlags = 0;
	windowFlags |= hideTitleBar ? ImGuiWindowFlags_NoTitleBar : windowFlags;
	windowFlags |= noCollapse ? ImGuiWindowFlags_NoCollapse : windowFlags;

	ImGui::Begin("testWin", NULL, windowFlags);
	//---------------------------------

	for (size_t i = 0; i < 20; i++)
	{
		if (ImGui::CollapsingHeader(("secret" + std::to_string(i)).c_str()))
		{
			ImGui::Text("found me..., now what?");
		}
	}

	//---------------------------------
	ImGui::End();
}
