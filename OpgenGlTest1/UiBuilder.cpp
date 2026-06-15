#include "UiManager.h"
#include "GLFW/glfw3.h"
#include <iostream>

void UiManager::Init() {

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	unsigned int width = mode->width;
	unsigned int height = mode->height;

	UiButton* spawnBlocks = SpawnUi<UiButton>(font, Vec2f(300.f, 100.f), Vec2f(width / 2.f, height / 1.1f));
	spawnBlocks->text.Content = "Rectangle";
	spawnBlocks->rect.CornerRadius = 25.f;

	spawnBlocks->OnClick = [=, this]() 
		{
			Rectangle* obj = objects.SpawnWorld<Rectangle>(Vec2f(100.f, 100.f), Vec2f(width / 2.f, height / 2.f));
			obj->Transform.Rotation = asinf(.5f);
		};

	UiButton* spawnCircle = SpawnUi<UiButton>(font, Vec2f(300.f, 100.f), Vec2f(width / 2.f, height / 1.25f));
	spawnCircle->text.Content = "Circle";
	spawnCircle->rect.CornerRadius = 25.f;

	spawnCircle->OnClick = [=, this]()
		{
			Circle* obj = objects.SpawnWorld<Circle>(50.f, Vec2f(width / 2.f, height / 2.f));
		};
}