#include "TeCoreApplication.h"

#include "Utility/TeTime.h"
#include "Threading/TeThreading.h"
#include "Utility/TeDynLibManager.h"
#include "Utility/TeDynLib.h"

namespace te
{
    CoreApplication::CoreApplication(START_UP_DESC desc)
        : _primaryWindow(nullptr)
        , _startUpDesc(desc)
        , _rendererPlugin(nullptr)
        , _isFrameRenderingFinished(true)
        , _runMainLoop(false)
    {
    }

    CoreApplication::~CoreApplication()
    {
    }

    void CoreApplication::OnStartUp()
    {
        for (auto& importerName : _startUpDesc.importers)
            LoadPlugin(importerName);

        Time::StartUp();
    }
    
    void CoreApplication::OnShutDown()
    {
        Time::ShutDown();
    }

    void CoreApplication::RunMainLoop()
    {
        _runMainLoop = true;

        while (_runMainLoop)
        {
            // Limit FPS if needed
            if (_frameStep > 0)
            {
                UINT64 currentTime = gTime().GetTimePrecise();
                UINT64 nextFrameTime = _lastFrameTime + _frameStep;
                while (nextFrameTime > currentTime)
                {
                    UINT32 waitTime = (UINT32)(nextFrameTime - currentTime);

                    // If waiting for longer, sleep
                    if (waitTime >= 2000)
                    {
                        TE_SLEEP(waitTime / 1000);
                        currentTime = gTime().GetTimePrecise();
                    }
                    else
                    {
                        // Otherwise we just spin, sleep timer granularity is too low and we might end up wasting a 
                        // millisecond otherwise. 
                        // Note: For mobiles where power might be more important than input latency, consider using sleep.
                        while (nextFrameTime > currentTime)
                            currentTime = gTime().GetTimePrecise();
                    }
                }

                _lastFrameTime = currentTime;
            }

            gTime().Update();

            PreUpdate();

            for (auto& pluginUpdateFunc : _pluginUpdateFunctions)
                pluginUpdateFunc.second();

            PostUpdate();
        }
    }

    void CoreApplication::PreUpdate()
    {
        // Do nothing
    }

    void CoreApplication::PostUpdate()
    {
        // Do nothing
    }

    void CoreApplication::StopMainLoop()
    {
        _runMainLoop = false; // No sync primitives needed, in that rare case of
        // a race condition we might run the loop one extra iteration which is acceptable
    }

    void CoreApplication::QuitRequested()
    {
        StopMainLoop();
    }

    void CoreApplication::SetFPSLimit(UINT32 limit)
    {
        if (limit > 0)
            _frameStep = (UINT64)1000000 / limit;
        else
            _frameStep = 0;
    }

    void CoreApplication::StartUpRenderer()
    {
    }

    void* CoreApplication::LoadPlugin(const String& pluginName, DynLib** library, void* passThrough)
    {
        DynLib* loadedLibrary = gDynLibManager().Load(pluginName);
        if (library != nullptr)
            *library = loadedLibrary;

        void* retVal = nullptr;
        if (loadedLibrary != nullptr)
        {
            if (passThrough == nullptr)
            {
                typedef void* (*LoadPluginFunc)();

                LoadPluginFunc loadPluginFunc = (LoadPluginFunc)loadedLibrary->GetSymbol("loadPlugin");

                if (loadPluginFunc != nullptr)
                    retVal = loadPluginFunc();
            }
            else
            {
                typedef void* (*LoadPluginFunc)(void*);

                LoadPluginFunc loadPluginFunc = (LoadPluginFunc)loadedLibrary->GetSymbol("loadPlugin");

                if (loadPluginFunc != nullptr)
                    retVal = loadPluginFunc(passThrough);
            }

            UpdatePluginFunc loadPluginFunc = (UpdatePluginFunc)loadedLibrary->GetSymbol("updatePlugin");

            if (loadPluginFunc != nullptr)
                _pluginUpdateFunctions[loadedLibrary] = loadPluginFunc;
        }

        return retVal;
    }

    void CoreApplication::UnloadPlugin(DynLib* library)
    {
        typedef void(*UnloadPluginFunc)();

        UnloadPluginFunc unloadPluginFunc = (UnloadPluginFunc)library->GetSymbol("unloadPlugin");

        if (unloadPluginFunc != nullptr)
            unloadPluginFunc();

        _pluginUpdateFunctions.erase(library);
        gDynLibManager().Unload(library);
    }

    CoreApplication& gCoreApplication()
    {
        return CoreApplication::Instance();
    }
}