# example config

option(ExampleAppHideConsole "hides the console window (WINDOWS ONLY)" true)

file(
	GLOB
	ExampleSrc
	"src/*.cpp"
	"src/*.h"
)

if(WIN32)
	if(ExampleAppHideConsole)
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
	
		add_executable(
			Example
			WIN32
			${ExampleSrc}
		)
	else()
		add_executable(
			Example
			${ExampleSrc}
		)
	endif(ExampleAppHideConsole)
else()
	add_executable(
		Example
		${ExampleSrc}
	)
endif()

set_target_properties(
	Example
	PROPERTIES
	VERSION 1.0
	POSITION_INDEPENDENT_CODE ON
	CXX_STANDARD 20
	FOLDER "ImGui_Lib"
)

target_link_libraries(
	Example
	PUBLIC
	glfw
	ImGUIWindow_Lib
)

target_include_directories(
	Example
	PUBLIC
	"${PROJECT_SOURCE_DIR}/Lib/"
)
