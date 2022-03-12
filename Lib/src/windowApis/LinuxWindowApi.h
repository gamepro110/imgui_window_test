#if __linux__
#pragma once

#include "BaseWindow.h"

#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_vulkan.h"

#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#ifdef _DEBUG
#define IMGUI_VULKAN_DEBUG_REPORT
#endif

namespace ImGUIWindow {
    class LinuxWindowApi : public BaseWindow {
    public:
        LinuxWindowApi() {
        }

        ~LinuxWindowApi() {
            Destroy();
        }

    public:
        bool Init(bool* runPtr, std::vector<fontWraper>& fonts) override;
        void BeginFrame() override;
        void EndFrame() override;
        void Destroy() override;

    public:
        static void glfw_handleResizeWindow_callback(GLFWwindow* win, int w, int h);
        static void glfw_closeWindow_callback(GLFWwindow*);
        static void glfw_error_callback(int error, const char* description);

        static LinuxWindowApi* Get() {
            return s_instance;
        }

        void SetWindowTitle(const std::string& title);

    private:
        static void check_vk_result(VkResult);

#ifdef IMGUI_VULKAN_DEBUG_REPORT
        static VKAPI_ATTR VkBool32 VKAPI_CALL debug_report(VkDebugReportFlagsEXT, VkDebugReportObjectTypeEXT, uint64_t, size_t, int32_t, const char*, const char*, void*);
#endif // IMGUI_VULKAN_DEBUG_REPORT

        static void SetupVulkan(const char** extensions, uint32_t extensions_count);

        // All the ImGui_ImplVulkanH_XXX structures/functions are optional helpers used by the demo.
        // Your real engine/app may not use them.
        static void SetupVulkanWindow(ImGui_ImplVulkanH_Window*, VkSurfaceKHR, int, int);
        static void CleanupVulkan();
        static void CleanupVulkanWindow();
        static void FrameRender(ImGui_ImplVulkanH_Window*, ImDrawData*);
        static void FramePresent(ImGui_ImplVulkanH_Window*);


    private:
        static LinuxWindowApi* s_instance;

        VkSurfaceKHR surface;
        VkResult err{};
        ImGui_ImplVulkanH_Window* wd;
        ImGuiIO* io = nullptr;
        int w;
        int h;
        std::string windowTitle;

    };
}

#endif
