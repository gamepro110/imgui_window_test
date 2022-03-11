#include "ImGuiWindow.h"

namespace ImGUIWindow {
	ImGuiWindow::ImGuiWindow(const std::string& windowTitle) {
#if WIN32
		data = new Data(new Win32Api());
#elif __linux__
		data = new Data(new LinuxWindowApi());
#elif __APPLE__
		// currently unable to test/develop due to not having apple hard/software
		data = new Data(new AppleRendering());
#else
#error "unsupported os detected..."
#endif // WIN32

		window = data->GetWindow();
		data->GetWindow()->SetWindowTitle(windowTitle);
	}

	ImGuiWindow::~ImGuiWindow() {
		delete data;
		delete window;
	}

	bool ImGuiWindow::Start() {
		return window->Init(&data->Run());
	}

	void ImGuiWindow::Update() {
		while (data->Run())
		{
			window->BeginFrame();
			for (auto& sub : subWindows)
			{
				sub->Invoke();
			}
			window->EndFrame();
		}
	}

	void ImGuiWindow::AddSubWindow(CallbackBase* callback) {
		subWindows.emplace_back(callback);
	}
}
