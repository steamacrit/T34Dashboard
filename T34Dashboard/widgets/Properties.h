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
        , m_value(default_value)
    {

    }

    inline const std::string & GetName() { return m_name; }
    inline void SetChanged(bool changed = true) { m_changed = changed; }
    inline bool HasChanged() { if (m_changed) { m_changed = false; return true; } return false; }
    inline void SetValue(T t) { m_value = t; m_changed = true; }
    inline void SetValueDirect(T t) { m_value = t; }
    inline T & GetValue() { m_changed = false;  return m_value; }
    
    T & operator=(const T & other) // copy assignment
    {
        if (this != &other) 
        { // self-assignment check expected
                m_value = other.m_value;
        }
        return *this;
    }

    StandardProperty<T> & operator=(const StandardProperty<T> & other) // copy assignment
    {
        if (this != &other)
        { // self-assignment check expected
            m_name = other.m_name;
            m_value = other.m_value;
            m_changed = other.m_changed;
        }
        return *this;
    }

protected:
    std::string m_name;
    T m_value;
    bool m_is_visible{ true };
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

struct WidgetProperties 
{ 
    StandardProperty<bool> visible{ StandardProperty<bool>("Is Visible", true) };
    StandardProperty<float> position_x{ StandardProperty<float>("Location X", 0.0f) };
    StandardProperty<float> position_y{ StandardProperty<float>("Location Y", 0.0f) };

    StandardProperty<float> size_w{ StandardProperty<float>("Width", 0.0f) };
    StandardProperty<float> size_h{ StandardProperty<float>("Height", 0.0f) };
};

struct WindowProperties : WidgetProperties
{
    StandardProperty<bool> fg_movable{ StandardProperty<bool>("Allow Move", true) };

    StandardProperty<bool> fg_resize{ StandardProperty<bool>("Allow Resize", true) };

    StandardProperty<bool> fg_titlebar{ StandardProperty<bool>("Has Title Bar", true) };

    int window_flags = 0;
};

struct TextProperties : WidgetProperties
{
    StandardProperty<std::string> text{ StandardProperty<std::string>("Text", "") };
};
