#include "UiManager.h"
#include "GLFW/glfw3.h"

void UiManager::Init() {

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	unsigned int width = mode->width;
	unsigned int height = mode->height;

	UiButton* spawnBlocks = SpawnUi<UiButton>(font, Vec2f(300.f, 100.f), Vec2f(width / 2.f, height / 1.1f));
	spawnBlocks->text.Content = "Rectangle";

	spawnBlocks->OnClick = [&]() 
		{
			objects.SpawnWorld<Rectangle>(Vec2f(100.f, 100.f), Vec2f(width / 2.f,height / 2.f));
		};
}