//
// Created by baifeng on 2019-07-28.
//

#include "render.h"

render::render():_window(nullptr), w(0), h(0) {
}

render::~render() {
    delete(_window);
}

void render::init(unsigned int w, unsigned int h) {
    if (_window == nullptr) {
        // Create the window of the application
        _window = new sf::RenderWindow(sf::VideoMode(w, h, 32), "demo", sf::Style::Titlebar | sf::Style::Close);
        _window->setVerticalSyncEnabled(true);
        _window->setFramerateLimit(60);
        this->w = w;
        this->h = h;
    }
}

render::Window* render::window() {
    return _window;
}

bool render::alive() {
    return _window->isOpen();
}

void render::begin(int r, int g, int b, int a) {
    _window->clear(sf::Color(r, g, b, a));
}

void render::draw(Drawable& target) {
    _window->draw(target);
}

void render::end() {
    _window->display();
}

int render::screenWidth() const {
    return this->w;
}

int render::screenHeight() const {
    return this->h;
}