#if __APPLE__
#pragma once

#include "BaseWindow.h"

namespace ImGUIWindow {
	class AppleRendering : BaseWindow {
	public:
		AppleRendering(bool* runPtr) :
			BaseWindow(runPtr) {
		}
		~AppleRendering() {
			Destroy();
		}

	public:
		Init
		BeginFrame
		EndFrame
		Destroy

		void Init(bool* runPtr) override {}
		void BeginFrame() override {}
		void EndFrame() override {}
		void Destroy() override{}

	private:
	
	};
}

#endif
