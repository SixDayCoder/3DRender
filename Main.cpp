
#include "device/MainWindow.h"
#include "test/BoxDemo.h"
#include "math3d/Model.h"
#include "math3d/Utils.h"


#include <algorithm>
#include <random>

int WINAPI wWinMain(HINSTANCE hInstance,  _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)                  
{

	AllocConsole();
	freopen("conout$", "w", stdout);

	MainWindow window(hInstance, 800, 600, "Fancy");

	Texture2D brick = Texture2D::LoadTexture2D(L"resources/texture/brick.jpg");
	Texture2D numberthree = Texture2D::LoadTexture2D(L"resources/texture/3.jpg");
	Texture2D darkred = Texture2D::LoadTexture2D(L"resources/texture/dark_red.jpg");

	//Mesh box1 = BoxDemo::CreateBox(2, 2, 2);
	//box1.position = Vector3(1.5, 0, 0);
	//box1.shader.SetTexture2D(brick);
	//window.GetGameScene().AddMesh(box1);

	//Mesh box2 = BoxDemo::CreateBox(2, 2, 2);
	//box2.position = Vector3(-1.5, 0, 0);
	//box2.shader.SetTexture2D(numberthree);
	//window.GetGameScene().AddMesh(box2);

	Model nanjia;
	nanjia.LoadFromFile("resources/model/nanjia/nanjia.obj");
	nanjia.position = Vector3(0, 0, 5);
	nanjia.shader.SetTexture2D(darkred);
	window.GetGameScene().AddModel(nanjia);
	
	window.Run();
	return 0;
}