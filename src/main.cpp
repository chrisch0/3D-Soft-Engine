#include "app.hpp"
#include "scene/test_scene.hpp"

int main(int argc, char* argv[])
{
	App app;
	app.Initialize();
	app.Run(UVTest);
	return 0;
}