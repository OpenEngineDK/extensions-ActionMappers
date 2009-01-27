// Keyboard event to action mapper.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_KEYBOARD_ACTION_MAPPER_H_
#define _OE_KEYBOARD_ACTION_MAPPER_H_

#include <Devices/IKeyboard.h>
#include <Core/IListener.h>
#include <list>

namespace OpenEngine {
namespace Devices {

/**
 * Keyboard event to action mapper.
 *
 * @class KeyboardActionMapper KeyboardActionMapper.h Devices/KeyboardActionMapper.h
 */
template <class Action>
class KeyboardActionMapper : public Core::IListener<KeyboardEventArg> {
public:

    void Handle(KeyboardEventArg arg) {
        typename std::list<KeyListener>::iterator itr;
        for (itr = keyList.begin(); itr != keyList.end(); itr++) {
            KeyListener m = *itr;
            if ((m.k == arg.sym) && (m.e & arg.type))
                m.l->Handle(toAction(arg));
        }
    }

    /**
     * Listen to input from a keyboard.
     */
    void listenTo(IKeyboard& m) {
        m.KeyEvent().Attach(*this);
    }

    /**
     * Add an action to a keyboard event.
     */
    void onKeyEvent(Key k, ButtonEvent e, Core::IListener<Action>& l) {
        KeyListener m; m.e=e; m.k=k; m.l=&l;
        keyList.push_back(m);
    }

    /**
     * Short forms for convenience.
     */
    void onKeyPress  (Key k, Core::IListener<Action>& l) { onKeyEvent  (k, EVENT_PRESS,   l); }
    void onKeyRelease(Key k, Core::IListener<Action>& l) { onKeyRelease(k, EVENT_RELEASE, l); }

    /**
     * User defined conversions between keyboard events and user actions.
     */
    virtual Action toAction(KeyboardEventArg arg) = 0;

private:
    struct KeyListener {
        ButtonEvent e;
        Key k;
        Core::IListener<Action>* l;
    };
    std::list<KeyListener> keyList;
};

} // NS Devices
} // NS OpenEngine

#endif // _OE_KEYBOARD_ACTION_MAPPER_H_
