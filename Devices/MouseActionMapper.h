// Mouse event to action mapper.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_MOUSE_ACTION_MAPPER_H_
#define _OE_MOUSE_ACTION_MAPPER_H_

#include <Devices/IMouse.h>
#include <Core/IListener.h>
#include <list>

namespace OpenEngine {
namespace Devices {

/**
 * Mouse event to action mapper.
 *
 * @class MouseActionMapper MouseActionMapper.h Devices/MouseActionMapper.h
 */
template <class Action>
class MouseActionMapper
    : public Core::IListener<MouseButtonEventArg>
    , public Core::IListener<MouseMovedEventArg> {

public:

    void Handle(MouseButtonEventArg arg) {
        typename std::list<BtnListener>::iterator itr;
        for (itr = btnList.begin(); itr != btnList.end(); itr++) {
            BtnListener m = *itr;
            if ((m.b & arg.button) && (m.e & arg.type))
                m.l->Handle(toAction(arg));
        }
    }

    void Handle(MouseMovedEventArg arg) {
        typename std::list<MoveListener>::iterator itr;
        for (itr = moveList.begin(); itr != moveList.end(); itr++) {
            (*itr).l->Handle(toAction(arg));
        }
    }

    /**
     * Listen to input from a mouse.
     */
    void listenTo(IMouse& m) {
        m.MouseButtonEvent().Attach(*this);
        m.MouseMovedEvent().Attach(*this);
    }

    /**
     * Add an action to a mouse event.
     */
    void onButtonEvent(MouseButton b, ButtonEvent e, Core::IListener<Action>& l) {
        BtnListener m; m.e=e; m.b=b; m.l=&l;
        btnList.push_back(m);
    }

    /**
     * Short forms for convenience.
     */
    void onLeftPress(Core::IListener<Action>& l)        { onButtonEvent(BUTTON_LEFT,       EVENT_PRESS,   l); }
    void onLeftRelease(Core::IListener<Action>& l)      { onButtonEvent(BUTTON_LEFT,       EVENT_RELEASE, l); }
    void onMiddlePress(Core::IListener<Action>& l)      { onButtonEvent(BUTTON_MIDDLE,     EVENT_PRESS,   l); }
    void onMiddleRelease(Core::IListener<Action>& l)    { onButtonEvent(BUTTON_MIDDLE,     EVENT_RELEASE, l); }
    void onRightPress(Core::IListener<Action>& l)       { onButtonEvent(BUTTON_RIGHT,      EVENT_PRESS,   l); }
    void onRightRelease(Core::IListener<Action>& l)     { onButtonEvent(BUTTON_RIGHT,      EVENT_RELEASE, l); }
    void onWheelUpPress(Core::IListener<Action>& l)     { onButtonEvent(BUTTON_WHEEL_UP,   EVENT_PRESS,   l); }
    void onWheelUpRelease(Core::IListener<Action>& l)   { onButtonEvent(BUTTON_WHEEL_UP,   EVENT_RELEASE, l); }
    void onWheelDownPress(Core::IListener<Action>& l)   { onButtonEvent(BUTTON_WHEEL_DOWN, EVENT_PRESS,   l); }
    void onWheelDownRelease(Core::IListener<Action>& l) { onButtonEvent(BUTTON_WHEEL_DOWN, EVENT_RELEASE, l); }

    /**
     * User defined conversions between mouse events and user actions.
     */
    virtual Action toAction(MouseButtonEventArg arg) = 0;
    virtual Action toAction(MouseMovedEventArg arg) = 0;

private:
    struct BtnListener {
        ButtonEvent e;
        MouseButton b;
        Core::IListener<Action>* l;
    };
    struct MoveListener {
        Core::IListener<Action>* l;
    };
    std::list<BtnListener> btnList;
    std::list<MoveListener> moveList;
};

} // NS Devices
} // NS OpenEngine

#endif // _OE_MOUSE_ACTION_MAPPER_H_
