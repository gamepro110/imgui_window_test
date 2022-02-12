# ImGuiWindow

## Todo

- optimize
- add mac support

___

## how to incude

### folder structure

- project folder
  - exe folder
  - tests folder
  - vendor/3rd party folder
    - ImGuiWindow

### include

```cmake
file(
	GLOB
	ExampleSrc
	"src/*.cpp"
	"src/*.h"
)

add_executable(
    Example
    ${ExampleSrc}
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
	"${PROJECT_SOURCE_DIR}/vendor/Lib/"
)
```

___
