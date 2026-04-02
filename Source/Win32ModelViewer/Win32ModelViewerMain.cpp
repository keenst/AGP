#include <windows.h>
#include <assert.h>
#include <stdio.h>

#define VK_USE_PLATFORM_WIN32_KHR
#define VK_NO_PROTOTYPES
#include "vulkan/vulkan.h"

#include "GraphicsEngine/Vulkan/RenderDeviceVulkan.h"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

typedef void (*FP_AppInit)(VkInstance, VkSurfaceKHR, PFN_vkGetInstanceProcAddr);
FP_AppInit AppInit;
typedef void (*FP_AppUpdateAndRender)(void);
FP_AppUpdateAndRender AppUpdateAndRender;

LRESULT WndProc(HWND aWindow, UINT aMessage, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(aWindow, aMessage, wParam, lParam);
}

int WinMain(HINSTANCE aInstance, HINSTANCE aPrevInstance, LPSTR aCmdLine, int aCmdShow)
{
	AllocConsole();
	FILE* out;
	freopen_s(&out, "CONOUT$", "w", stdout);
	freopen_s(&out, "CONOUT$", "w", stderr);

	printf("Hello world!\n");

	// Create window
	const char* className = "ModelViewer";
	WNDCLASS windowClass =
	{
		.lpfnWndProc = WndProc,
		.hInstance = aInstance,
		.lpszClassName = className
	};
	RegisterClass(&windowClass);

	RECT clientRect =
	{
		.left = 0,
		.top = 0,
		.right = WINDOW_WIDTH,
		.bottom = WINDOW_HEIGHT
	};
	AdjustWindowRect(&clientRect, WS_OVERLAPPEDWINDOW, 0);

	HWND window = CreateWindowEx(
			0,
			className, className,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			clientRect.right - clientRect.left,
			clientRect.bottom - clientRect.top,
			nullptr, nullptr,
			aInstance, nullptr);
	assert(window);

	ShowWindow(window, aCmdShow);

	// Create vulkan instance and surface
	HMODULE vulkan = LoadLibrary("vulkan-1.dll");

	// TODO(leo):
	// Causes crash when user doesn't have the vulkan SKD installed.
	// Maybe only enable validation in debug?
	const char* enabledLayers[] =
	{
		"VK_LAYER_KHRONOS_validation"
	};

	const char* instanceExtensions[] =
	{
		VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
		VK_KHR_SURFACE_EXTENSION_NAME,
		VK_EXT_DEBUG_UTILS_EXTENSION_NAME
	};

	const char* deviceExtensions[] =
	{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME,
		VK_KHR_SHADER_DRAW_PARAMETERS_EXTENSION_NAME
	};

	const uint32_t enabledLayerCount = sizeof(enabledLayers) / sizeof(char*);
	const uint32_t instanceExtensionCount = sizeof(instanceExtensions) / sizeof(char*);
	const uint32_t deviceExtensionCount = sizeof(deviceExtensions) / sizeof(char*);

	VkApplicationInfo applicationInfo =
	{
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pApplicationName = "AGP",
		.applicationVersion = VK_MAKE_VERSION(0, 1, 0),
		.apiVersion = VK_API_VERSION_1_0
	};

	VkInstanceCreateInfo instanceInfo =
	{
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pApplicationInfo = &applicationInfo,
		.enabledLayerCount = enabledLayerCount,
		.ppEnabledLayerNames = enabledLayers,
		.enabledExtensionCount = instanceExtensionCount,
		.ppEnabledExtensionNames = instanceExtensions
	};

	PFN_vkCreateInstance vkCreateInstance =
		(PFN_vkCreateInstance)GetProcAddress(vulkan, "vkCreateInstance");

	VkInstance vulkanInstance;
	VkResult instanceResult = vkCreateInstance(&instanceInfo, nullptr, &vulkanInstance);
	assert(instanceResult == VK_SUCCESS);

	VkWin32SurfaceCreateInfoKHR surfaceInfo =
	{
		.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
		.hinstance = aInstance, .hwnd = window
	};

	PFN_vkCreateWin32SurfaceKHR vkCreateWin32SurfaceKHR =
		(PFN_vkCreateWin32SurfaceKHR)GetProcAddress(vulkan, "vkCreateWin32SurfaceKHR");

	VkSurfaceKHR surface;
	VkResult surfaceResult = vkCreateWin32SurfaceKHR(vulkanInstance, &surfaceInfo, nullptr, &surface);
	assert(surfaceResult == VK_SUCCESS);

	// Start application layer
	HMODULE app = LoadLibrary("Build/ModelViewer.dll");
	assert(app);

	AppInit = (FP_AppInit)GetProcAddress(app, "AppInit");
	AppUpdateAndRender = (FP_AppUpdateAndRender)GetProcAddress(app, "AppUpdateAndRender");
	assert(AppInit);
	assert(AppUpdateAndRender);

	AppInit(
			vulkanInstance,
			surface,
			(PFN_vkGetInstanceProcAddr)GetProcAddress(vulkan, "vkGetInstanceProcAddr"));

	while (true)
	{
		MSG message;
		while (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;

			TranslateMessage(&message);
			DispatchMessage(&message);
		}

		AppUpdateAndRender();
	}
}
