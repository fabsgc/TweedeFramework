#include "TeD3D11RenderWindow.h"
#include "Private/Win32/TeWin32Platform.h"

namespace te
{
    D3D11RenderWindow::D3D11RenderWindow(const RENDER_WINDOW_DESC& desc)
        : RenderWindow(desc)
        , _properties(desc)
    {
    }

    D3D11RenderWindow::~D3D11RenderWindow()
    {
        SAFE_RELEASE(_swapChain);

        if (_window != nullptr)
        {
            _window->Destroy();
            te_delete(_window);
        }
    }

    void D3D11RenderWindow::Update()
    {
    }

    void D3D11RenderWindow::Initialize()
    {
        ZeroMemory(&_swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

        WINDOW_DESC windowDesc;
        windowDesc.ShowTitleBar = _desc.ShowTitleBar;
        windowDesc.ShowBorder = _desc.ShowBorder;
        windowDesc.AllowResize = _desc.AllowResize;
        windowDesc.EnableDoubleClick = true;
        windowDesc.Fullscreen = _desc.Fullscreen;
        windowDesc.Width = _desc.Mode.GetWidth();
        windowDesc.Height = _desc.Mode.GetHeight();
        windowDesc.Hidden = _desc.Hidden || _desc.HideUntilSwap;
        windowDesc.Left = _desc.Left;
        windowDesc.Top = _desc.Top;
        windowDesc.OuterDimensions = false;
        windowDesc.Title = _desc.Title;
        windowDesc.CreationParams = this;
        windowDesc.WndProc = &Win32Platform::_win32WndProc;
        
#ifdef BS_STATIC_LIB
        windowDesc.Module = GetModuleHandle(NULL);
#else
        windowDesc.Module = GetModuleHandle("TeD3D11RenderAPI.dll");
#endif

        _window = te_new<Win32Window>(windowDesc);

        _properties.Width = _window->GetWidth();
        _properties.Height = _window->GetHeight();
        _properties.Top = _window->GetTop();
        _properties.Left = _window->GetLeft();

        //createSwapChain();

        if (_properties.IsFullScreen)
        {
            /*if (outputInfo != nullptr)
                mSwapChain->SetFullscreenState(true, outputInfo->getDXGIOutput());
            else
                mSwapChain->SetFullscreenState(true, nullptr);*/
        }

        //createSizeDependedD3DResources();
        //mDXGIFactory->MakeWindowAssociation(mWindow->getHWnd(), NULL);
    }

    void D3D11RenderWindow::Destroy()
    {
    }

    void D3D11RenderWindow::GetCustomAttribute(const String& name, void* pData) const
    {
        if (name == "WINDOW")
        {
            UINT64 *pWnd = (UINT64*)pData;
            *pWnd = (UINT64)_window->GetHWnd();
            return;
        }
        
        RenderWindow::GetCustomAttribute(name, pData);
    }
}