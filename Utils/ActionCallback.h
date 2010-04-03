// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------


#ifndef _OE_ACTION_CALLBACK_H_
#define _OE_ACTION_CALLBACK_H_

#include <Core/IListener.h>

namespace OpenEngine {
namespace Utils {

    template <class T, class A>
    class ActionCallback : public Core::IListener<A> {
        T* callee;
        void (T::*callback)(A);
    public:
        ActionCallback(T* who, void (T::*func)(A)) 
            : callee(who),callback(func) {}
        
        void Handle(A arg) {
            (callee->*callback)(arg);
        }
    };


} // NS Utils
} // NS OpenEngine

#endif // _OE_ACTION_CALLBACK_H_
