#pragma once

namespace te
{
    /** Values that represent in which order are euler angles applied when used in transformations. */
    enum class EulerAngleOrder
    {
        XYZ,
        XZY,
        YXZ,
        YZX,
        ZXY,
        ZYX
    };

    /** Enum used for object construction specifying the object should be zero initialized. */
    enum TE_ZERO { TeZero };

    /** Enum used for matrix/quaternion constructor specifying it should be initialized with an identity value. */
    enum TE_IDENTITY { TeIdentity };

    class GeneralAllocator;
    template<class T> 
    class MemoryAllocator;
    template <class T, class Allocator>
    class StdAllocator;
    class BasicAllocator;
    class LinearAllocator;
    class StackAllocator;
    template<size_t ElementSize, size_t ElementsPerBlock, size_t Alignment> 
    class PoolAllocator;

    class Console;

    class DynLib;
    class DynLibManager;

    template<class T> class Module;

    class Time;
    class Timer;

    class AABox;
    class Bounds;
    class Line2;
    class LigneSegment3;
    class Vector2;
    class Vector2I;
    class Vector3;
    class Vector3I;
    class Vector4;
    class Vector4I;
    class Matrix3;
    class Matrix4;
    class Rect2;
    class Rect2I;
    class Rect3;
    class Math;
    class Quaternion;
    class Frustum;
    class Angle;
    class Degree;
    class Radian;
    class Plane;
    class Sphere;
    class Ray;

    class NonCopyable;

    class TaskScheduler;
    class Task;
}