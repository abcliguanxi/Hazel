#pragma once

#ifdef HZ_PALTFORM_WINDOWS
extern Hazel::Application* Hazel::CreateApplication();//在某个地方定义的函数会返回实际的应用程序
int main(int argc,char** argv) {
	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}
#else
	#error Hazel only supports Windows!
#endif // HZ_PLATFORM_WINDOWS

