//
// Created by baifeng on 2019-07-28.
//

#include "Input.h"
#include <assert.h>

Input::Input():_window(nullptr) {

}

void Input::setWindow(Window *window) {
    _window = window;
}

void Input::handleEvent(InputProc proc) {
    assert(_window);
    InputEvent event;
    while (_window->pollEvent(event)) {
        proc(event);
    }
}