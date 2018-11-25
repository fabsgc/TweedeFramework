#pragma once

#include "Prerequisites/TePrerequisitesUtility.h"
#include "Threading/TeThreading.h"

namespace te
{
    /** Data common to all event. */
    struct BaseConnectionData
    {
        BaseConnectionData() = default;
        virtual ~BaseConnectionData() = default;
        
        virtual void Deactivate()
        {
            IsActive = false;
        }

        BaseConnectionData* Previous = nullptr;
        BaseConnectionData* Next = nullptr;
        bool IsActive = true;
        UINT16 HandleLinks = 0;
    };

    /** Internal data for an Event, storing all connections. */
    class InternalData
    {
        InternalData() = default;
        ~InternalData() = default;

        void Connect(BaseConnectionData* connection)
        {
        }

        void Disconnect(BaseConnectionData* connection)
        {
        }

        void Clear(BaseConnectionData* connection)
        {
            RecursiveLock lock(_mutex);

            connection->HandleLinks--;

            if (connection->HandleLinks == 0 && !connection->IsActive)
                free(connection);
        }

        void FreeHandle()
        {
        }

        void Free(BaseConnectionData* connection)
        {
        }

        BaseConnectionData* _connections = nullptr;
        BaseConnectionData* _newConnections = nullptr;

        RecursiveMutex _mutex;
        bool _isCurrentlyTriggering = false;
    };

    /** Event handler. Allows you to track to which events you subscribed to and disconnect from them when needed. */
	class EventHandler
	{
	public:
		EventHandler() = default;
        ~EventHandler() = default;

        void disconnect()
		{
        }

        EventHandler& operator=(const EventHandler& rhs)
        {
            _connection = rhs._connection;
            _eventData = rhs._eventData;

            if (_connection != nullptr)
                _connection->HandleLinks++;

            return *this;
        }

    protected:
        BaseConnectionData* _connection = nullptr;
        SPtr<InternalData> _eventData;
    };

    /**
	 * Events allows you to register method callbacks that get notified when the event is triggered.
	 */
    template <class ReturnType, class... Args>
    class InternalEvent
    {
    public:
        struct ConnectionData : BaseConnectionData
        {
            void Deactivate() override
            {
                func = nullptr;
                BaseConnectionData::Deactivate();
            }

            std::function<ReturnType(Args...)> func;
        };

        InternalEvent()
            : _internalData(nullptr)
        {
        }

        ~InternalEvent()
        {
            Clear();
        }

        EventHandler connect(std::function<ReturnType(Args...)> func)
        {
        }

        void operator() (Args... args)
        {
        }

        void Clear()
        {
            _internalData->Clear();
        }

    protected:
        SPtr<InternalData> _internalData;
    };

    template <typename Signature>
	class Event;

    template <class ReturnType, class... Args>
	class TE_UTILITY_EXPORT Event<ReturnType(Args...) > : public InternalEvent <ReturnType, Args...>
	{ };
}