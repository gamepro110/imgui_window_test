#pragma once

#if WIN32
#	define UseVulkan
#	define GLFW_INCLUDE_VULKAN
#elif __linux__
#	define UseVulkan
#	define GLFW_INCLUDE_VULKAN
#elif __APPLE__
#	define UseMetal
#endif // WIN32

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#ifdef UseVulkan
#	include "backends/imgui_impl_vulkan.h"
#	include <vulkan/vulkan.h>
#endif // UseVulkan

#ifdef UseMetal
#	include "backends/imgui_impl_metal.h"
#endif // UseMetal

#include <string>
#include <vector>
#include <iostream>

namespace ImGUIWindow {
#ifdef UseVulkan
	static VkAllocationCallbacks*	g_Allocator = NULL;
	static VkInstance               g_Instance = VK_NULL_HANDLE;
	static VkPhysicalDevice         g_PhysicalDevice = VK_NULL_HANDLE;
	static VkDevice                 g_Device = VK_NULL_HANDLE;
	static uint32_t                 g_QueueFamily = (uint32_t)-1;
	static VkQueue                  g_Queue = VK_NULL_HANDLE;
	static VkDebugReportCallbackEXT g_DebugReport = VK_NULL_HANDLE;
	static VkPipelineCache          g_PipelineCache = VK_NULL_HANDLE;
	static VkDescriptorPool         g_DescriptorPool = VK_NULL_HANDLE;

	static ImGui_ImplVulkanH_Window g_MainWindowData;
	static int                      g_MinImageCount = 2;
	static bool                     g_SwapChainRebuild = false;
#endif // Vulkan

	struct fontWraper {
		fontWraper(ImFont*& font, int fontSize, std::string path) :
			font(font),
			fontSize(fontSize),
			path(path)
		{}

		ImFont*& font;
		int fontSize{ 12 };
		const std::string path{};
	};

	class BaseWindow {
	public:
		BaseWindow() = default;
		virtual ~BaseWindow() = default;

	public:
		virtual bool Init(bool* runPtr, std::vector<fontWraper>& fonts) = 0;
		virtual void BeginFrame() = 0;
		virtual void EndFrame() = 0;
		virtual void Destroy() = 0;

	public:
		void SetWindowTitle(const std::string& title) {
			windowTitle = std::string{ title };
		}
		GLFWwindow* GetGlfwWin() {
			return glfwWindow;
		}

	protected:
		void loadFontFromWrapper(fontWraper& wrap) {
			wrap.font = io->Fonts->AddFontFromFileTTF(
				wrap.path.c_str(),
				wrap.fontSize,
				NULL,
				NULL
			);
			IM_ASSERT(wrap.font != NULL);
			if (wrap.font == nullptr) {
				std::cout << "failed to load font (\"" << wrap.path << "\")\n";
			}
		};

	protected:
		bool* run{ nullptr };
		GLFWwindow* glfwWindow{ nullptr };
		std::string windowTitle;
		ImGuiIO* io = nullptr;

	};
}
