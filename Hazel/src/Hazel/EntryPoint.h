#pragma once

#ifdef HZ_PLATFORM_WINDOWS
extern Hazel::Application* Hazel::CreateApplication();//��ĳ���ط�����ĺ����᷵��ʵ�ʵ�Ӧ�ó���
int main(int argc,char** argv) {

	Hazel::Log::Init();

	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}
#else
	#error Hazel only supports Windows!
#endif // HZ_PLATFORM_WINDOWS

