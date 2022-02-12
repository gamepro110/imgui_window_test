#include "mac.h"
#if __APPLE__

namespace ImGUIWindow {
	AppleRendering::Init(bool* runPtr) {
		run = runPtr;
	}
}

#endif // __APPLE__
