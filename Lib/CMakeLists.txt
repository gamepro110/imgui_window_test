# lib config

#imgui style option
set(
	ImGuiStyle
	"Dark"
	CACHE
	STRING
	"ImGuiStyle chosen by the user at CMake configure time"
)

set_property(
	CACHE
	ImGuiStyle
	PROPERTY
	STRINGS
	"Dark"
	"Light"
	"Classic"
)

add_compile_definitions(
	"ImGuiTheme${ImGuiStyle}"
)

message(
	STATUS
	"> ImGuiStyle = '${ImGuiStyle}'"
)
#imgui style option

file(
	GLOB_RECURSE
	APP_SRC
	"src/*.cpp"
	"src/*.h"
)

add_library(
	ImGUIWindow_Lib
	STATIC
	${APP_SRC}
)

set_target_properties(
	ImGUIWindow_Lib
	PROPERTIES
	VERSION 1.0
	POSITION_INDEPENDENT_CODE ON
	CXX_STANDARD 20
	FOLDER "ImGui_Lib"
)

target_include_directories(
	ImGUIWindow_Lib
	PUBLIC
	"${vendorPath}/imgui/"
	"${vendorPath}/glfw/include/"
	"${Vulkan_INCLUDE_DIRS}"
)

target_link_libraries(
	ImGUIWindow_Lib
	PUBLIC
	glfw
	IMGUI_LIB
	"${Vulkan_LIBRARIES}"
)
