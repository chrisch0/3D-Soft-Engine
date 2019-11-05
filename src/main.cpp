#include "app.hpp"
#include "scene/test_scene.hpp"
#include "scene/light2d.hpp"

int main(int argc, char* argv[])
{
	App app(512, 512);
	app.Initialize();
	app.SingleFrame(FirstLight);
	system("pause");
	return 0;
}