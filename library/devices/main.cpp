bool isKeyDown(char key);
//bool isMouseButtonPressed();
//int getMousePositionX();
//int getMousePositionY();

#if defined(_WIN32)
    #ifdef _WIN32_WINDOWS
        #undef _WIN32_WINDOWS
    #endif
    #ifdef _WIN32_WINNT
        #undef _WIN32_WINNT
    #endif
    #define _WIN32_WINDOWS 0x0501
    #define _WIN32_WINNT   0x0501
    #include <windows.h>

bool isKeyDown(char key)
{
    return (GetAsyncKeyState(VkKeyScanA(key)) & 0x8000) != 0;
}

#elif defined(__linux__)
    #include <X11/Xlib.h>
    #include <X11/keysym.h>

bool isKeyDown(char key)
{
    char str[1];
    str[0] = key;
    KeySym keysym = XStringToKeysym(str);

    Display* display = XOpenDisplay(nullptr);
    KeyCode keycode = XKeysymToKeycode(display, keysym);
    if (keycode != 0)
    {
        char keys[32];
        XQueryKeymap(display, keys);
        XCloseDisplay(display);
        return (keys[keycode / 8] & (1 << (keycode % 8))) != 0;
    }
    else
    {
        XCloseDisplay(display);
        return false;
    }
}

#else
    #pragma message ("OS not fully supported")

bool isKeyDown(char key)
{
    return false;
}

#endif

#include "nobject.h"
#include "Common.h"

object::objectPtr initDevices (object::objectPtr obj, object::arrayType& args)
{
    obj->addChild(constructObject(obj, "Object", nullptr)->setName("keyboard")
        ->addChild(makeObject(function<bool (*)(char), isKeyDown, bool, std::string>, name("isKeyDown")))
        );
    return nullptr;
}
