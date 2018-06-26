
#include "MainWindow.h"
#include "BoxDemo.h"
#include "Model.h"
#include "Utils.h"

#include <algorithm>
#include <random>

int WINAPI wWinMain(HINSTANCE hInstance,  _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)                  
{

	AllocConsole();
	freopen("conout$", "w", stdout);

	MainWindow window(hInstance, 800, 600, "Fancy");

	Mesh box1 = BoxDemo::CreateBox(2, 2, 2);
	box1.position = Vector3(1.5, 0, 0);
	box1.texture  = Texture2D::LoadTexture2D(L"resources/texture/brick.jpg");
	window.GetGameScene().AddMesh(box1);

	Mesh box2 = BoxDemo::CreateBox(2, 2, 2);
	box2.position = Vector3(-1.5, 0, 0);
	box2.texture = Texture2D::LoadTexture2D(L"resources/texture/5.jpg");
	window.GetGameScene().AddMesh(box2);
	
	////¶à¸öºÐ×Ó
	//std::default_random_engine e;
	//std::uniform_real_distribution<> xrander(-5, 5);
	//std::uniform_real_distribution<> yrander(-5, 5);
	//std::uniform_real_distribution<> zrander(2, 20);
	//for (uint32 i = 0; i < 10; ++i)
	//{
	//	Mesh box = BoxDemo::CreateBox(2, 2, 2);
	//	box.position.x = xrander(e);
	//	box.position.y = yrander(e);
	//	box.position.z = zrander(e);
	//	box.rotation = Vector3(xrander(e) * 10, yrander(e) * 10, zrander(e) * 10);
	//	std::wstring path = L"resources/texture/" + std::to_wstring(i) + L".jpg";
	//	box.texture = Texture2D::LoadTexture2D(path.c_str());
	//	window.GetGameScene().AddMesh(box);
	//}

	//Model teapot;
	//teapot.LoadFromFile("resources/model/teapot/teapot.obj");
	//teapot.position = Vector3(0, 0, 5);
	//window.GetGameScene().AddModel(teapot);

	//Model house;
	//house.LoadFromFile("resources/model/house/house.obj");
	//house.position = Vector3(2, 0, 700);
	//window.GetGameScene().AddModel(house);

	//Model nanjia;
	//nanjia.LoadFromFile("resources/model/nanjia/nanjia.obj");
	//nanjia.position = Vector3(0, 0, 20);
	//window.GetGameScene().AddModel(nanjia);


	window.Run();
	return 0;
}