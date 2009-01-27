#include <Testing/Testing.h>

#include <Devices/MouseActionMapper.h>
#include <Devices/KeyboardActionMapper.h>

using namespace std;
using namespace OpenEngine::Core;
using namespace OpenEngine::Devices;

// Action argument implementation (user defined)
class MyActionArg {

};

// Action implementation (user defined)
class MyAction : public IListener<MyActionArg> {
    void Handle(MyActionArg action) {
        std::cout << "Action Triggered!" << std::endl;
    }
};

// Mouse mapper implementation (converts to user-defined action type)
class MM : public MouseActionMapper<MyActionArg> {
    MyActionArg toAction(MouseButtonEventArg arg) { return MyActionArg(); }
    MyActionArg toAction(MouseMovedEventArg arg) { return MyActionArg(); }
};

class KM : public KeyboardActionMapper<MyActionArg> {
    MyActionArg toAction(KeyboardEventArg arg) { return MyActionArg(); }
};

int test_main(int argc, char* argv[]) {
    MyAction action;

    // Bind mouse input to the action
    MM mm;
    mm.onButtonEvent(BUTTON_LEFT, EVENT_PRESS, action);
    mm.onLeftRelease(action);
    // We listen to a stub impl. of IMouse to test event work
    // mm.listenTo( ...IMouse... );

    // Bind keyboard input to the (same) action
    KM km;
    km.onKeyEvent(KEY_x, EVENT_PRESS, action);
    km.onKeyPress(KEY_y, action);
    // We need to stub IKeyboard to trigger testing events
    // km.listenTo( ...IKeyboard... );

    return 0;
}
