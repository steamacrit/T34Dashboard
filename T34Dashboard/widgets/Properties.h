#pragma once

#include "pch.h"

struct WidgetProperty 
{ 
};

template <typename T>
class StandardProperty : public WidgetProperty
{
public:
    StandardProperty(const std::string name, T default_value)
        : m_name(name)
        , value(default_value)
    {

    }

    inline const std::string & GetName() { return m_name; }
    inline void SetChanged(bool changed = true) { m_changed = changed; }
    inline bool HasChanged() { if (m_changed) { m_changed = false; return true; } return false; }
    inline void SetValue(T t) { value = t; m_changed = true; }
    inline void SetValueDirect(T t) { value = t; }
    inline T & GetValue() { return value; }

protected:
    std::string m_name;
    T value;
    bool m_changed{ false };
};

template <typename T>
class RangedProperty : public StandardProperty<T>
{
public:
    RangedProperty(const std::string name, T default_value, T max_value, T min_value)
        : StandardProperty<T>(name, default_value)
        , m_max_value(max_value)
        , m_min_value(min_value)
    {

    }

protected:
    T m_max_value;
    T m_min_value;
};

struct WidgetProperties { };

struct WindowProperties : WidgetProperties
{
    StandardProperty<float> pos_x{ StandardProperty<float>("Location X", 0.0f) };
    StandardProperty<float> pos_y{ StandardProperty<float>("Location Y", 0.0f) };
    StandardProperty<bool> fg_movable{ StandardProperty<bool>("Allow Move", true) };

    StandardProperty<float> size_w{ StandardProperty<float>("Width", 0.0f) };
    StandardProperty<float> size_h{ StandardProperty<float>("Height", 0.0f) };
    StandardProperty<bool> fg_resize{ StandardProperty<bool>("Allow Resize", true) };

    StandardProperty<bool> fg_titlebar{ StandardProperty<bool>("Has Title Bar", true) };

    int window_flags = 0;
};
