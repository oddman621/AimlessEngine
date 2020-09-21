#pragma once
#include <vulkan/vulkan.h>
#include <vector>

class VulkanApp
{
	const std::vector<const char*> deviceExtensions = {};//extension list to use
	const std::vector<const char*> requiredExtensions;
public:
	VulkanApp() : requiredExtensions({}) {
	}
private:
	// Vulkan Essentials
	VkInstance instance = nullptr;
	VkPhysicalDevice physicalDevice = nullptr; // literally.
	VkDevice device = nullptr; // logical device. end-user device?
private:
	bool CreateInstance();
	bool CreatePhysicalDevice();
	bool CreateLogicalDevice();
private:
	void DestroyLogicalDevice();
	void DestroyInstance();
};