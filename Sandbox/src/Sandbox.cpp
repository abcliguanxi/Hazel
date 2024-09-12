#include <Hazel.h>

class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
	}

	~Sandbox()
	{

	}
};

//定义一个函数
Hazel::Application* Hazel::CreateApplication() 
{
	return new Sandbox();
}


//#include "spdlog/spdlog.h"
//int main(int argc, char** argv) {
//
//	//Hazel::Log::Init();
//	//HZ_CORE_WARN("Initialized Log!");
//	//HZ_INFO("Hello! var={0}",5);
//	spdlog::info("aaa");
//	/*auto app = Hazel::CreateApplication();
//	app->Run();
//	delete app;*/
//}