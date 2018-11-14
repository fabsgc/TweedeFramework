#include "TeCoreApplication.h"

#if TE_PLATFORM == TE_PLATFORM_WIN32
#include <windows.h>

int CALLBACK WinMain(
    _In_  HINSTANCE hInstance,
    _In_  HINSTANCE hPrevInstance,
    _In_  LPSTR lpCmdLine,
    _In_  int nCmdShow
)
#else
int main()
#endif
{
    te::START_UP_DESC desc;

    te::CoreApplication::StartUp(desc);
    te::gCoreApplication().RunMainLoop();
    te::CoreApplication::ShutDown();

    return 0;
}
