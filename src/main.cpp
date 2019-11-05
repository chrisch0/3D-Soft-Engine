#include "app.hpp"
#include "scene/test_scene.hpp"
#include "scene/light2d.hpp"

int main(int argc, char* argv[])
{
	App app;
	app.Initialize();
	app.Run(FirstLight);
	return 0;
}