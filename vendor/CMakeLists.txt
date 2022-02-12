# vendor

## imgui
file(
	GLOB
	IMGUI_SRC
	"${vendorPath}/imgui/*.cpp"
	"${vendorPath}/imgui/*.h"
	"${vendorPath}/imgui/backends/imgui_impl_glfw.cpp"
	"${vendorPath}/imgui/backends/imgui_impl_glfw.h"
	#"${vendorPath}/imgui/backends/imgui_impl_.h"
)

if(WIN32)
	file(
		GLOB
		IMGUI_WIN_SRC
		"${IMGUI_SRC}"
		"${vendorPath}/imgui/backends/imgui_impl_vulkan.cpp"
		"${vendorPath}/imgui/backends/imgui_impl_vulkan.h"
	)
endif(WIN32)

if(APPLE)
	file(
		GLOB
		IMGUI_MAC_SRC
		"${vendorPath}/imgui/backends/imgui_impl_metal.mm"
		"${vendorPath}/imgui/backends/imgui_impl_metal.h"
		"${vendorPath}/imgui/backends/imgui_impl_osx.mm"
		"${vendorPath}/imgui/backends/imgui_impl_osx.h"
	)
endif(APPLE)

if(UNIX)
	if(NOT APPLE)
		file(
			GLOB
			IMGUI_LIN_SRC
			"${vendorPath}/imgui/backends/imgui_impl_vulkan.cpp"
			"${vendorPath}/imgui/backends/imgui_impl_vulkan.h"
		)
	endif(NOT APPLE)
endif(UNIX)

add_library(
	IMGUI_LIB
	${IMGUI_SRC}
	"${IMGUI_WIN_SRC}"
	"${IMGUI_LIN_SRC}"
	"${IMGUI_MAC_SRC}"
)

set_target_properties(
	IMGUI_LIB
	PROPERTIES
	VERSION 1.0
	POSITION_INDEPENDENT_CODE ON
	CXX_STANDARD 20
	FOLDER "ImGui_Lib"
)

target_link_libraries(
	IMGUI_LIB
	PUBLIC
	"${Vulkan_LIBRARIES}"
)

target_include_directories(
	IMGUI_LIB
	PUBLIC
	"${Vulkan_INCLUDE_DIRS}"
	"glfw/include/"
)

target_include_directories(
	IMGUI_LIB
	PUBLIC
	"${vendorPath}/imgui/"
	"${vendorPath}/imgui/backends"
)

## glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("${vendorPath}/glfw/" "${vendorPath}/glfw/")
