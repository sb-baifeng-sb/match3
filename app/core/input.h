//
// Created by baifeng on 2019-07-28.
//

#ifndef APP_INPUT_H
#define APP_INPUT_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <functional>

typedef sf::Event InputEvent;
typedef std::function<void(InputEvent& event)> InputProc;

class input {
public:
    typedef sf::RenderWindow Window;
public:
    input();
    void setWindow(Window* window);
    void handleEvent(InputProc proc);
private:
    Window* _window;
};


#endif //APP_INPUT_H
