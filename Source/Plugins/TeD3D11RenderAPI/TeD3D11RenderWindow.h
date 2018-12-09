#pragma once

#include "TeD3D11RenderAPIPrerequisites.h"
#include "RenderAPI/TeRenderWindow.h"
#include "Private/Win32/TeWin32Window.h"

namespace te
{
    class D3D11RenderWindow : public RenderWindow
	{
	public:
        D3D11RenderWindow(const RENDER_WINDOW_DESC& desc);
		~D3D11RenderWindow();

        void Destroy() override;
        void Update() override;
        void Initialize() override;
        void GetCustomAttribute(const String& name, void* pData) const override;

    protected:
        RenderWindowProperties _properties;
        IDXGISwapChain* _swapChain = nullptr;
        DXGI_SWAP_CHAIN_DESC _swapChainDesc;
        Win32Window* _window = nullptr;
    };
}