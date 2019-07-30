//
// Created by baifeng on 2019-07-28.
//

#include "render.h"

Render::Render():_window(nullptr), w(0), h(0) {
}

Render::~Render() {
    delete(_window);
}

void Render::init(unsigned int w, unsigned int h) {
    if (_window == nullptr) {
        // Create the window of the application
        _window = new sf::RenderWindow(sf::VideoMode(w, h, 32), "demo", sf::Style::Titlebar | sf::Style::Close);
        _window->setVerticalSyncEnabled(true);
        _window->setFramerateLimit(60);
        this->w = w;
        this->h = h;
    }
}

Render::Window* Render::window() {
    return _window;
}

bool Render::alive() {
    return _window->isOpen();
}

void Render::begin(int r, int g, int b, int a) {
    _window->clear(sf::Color(r, g, b, a));
}

void Render::draw(Drawable& target) {
    _window->draw(target);
}

void Render::end() {
    _window->display();
}

int Render::screenWidth() const {
    return this->w;
}

int Render::screenHeight() const {
    return this->h;
}