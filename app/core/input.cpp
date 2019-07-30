//
// Created by baifeng on 2019-07-28.
//

#include "input.h"

input::input():_window(nullptr) {

}

void input::setWindow(Window *window) {
    _window = window;
}

void input::handleEvent(InputProc proc) {
    assert(_window);
    InputEvent event;
    while (_window->pollEvent(event)) {
        proc(event);
    }
}