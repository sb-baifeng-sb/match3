//
// Created by baifeng on 2019-07-28.
//

#ifndef APP_RENDER_H
#define APP_RENDER_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <functional>

typedef sf::Drawable Drawable;
typedef std::function<void(Drawable&)> DrawFN;

class render {
public:
    typedef sf::RenderWindow Window;
public:
    render();
    ~render();
public:
    void init(unsigned int w, unsigned int h);
    Window* window();
    bool alive();
    int screenWidth() const;
    int screenHeight() const;
public:
    void begin(int r = 0, int g = 0, int b = 0, int a = 255);
    void draw(Drawable& target);
    void end();
private:
    int w, h;
    Window* _window;
};


#endif //APP_RENDER_H
