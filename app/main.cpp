
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>

#ifdef SFML_SYSTEM_IOS
#include <SFML/Main.hpp>
#endif

#include <core/context.h>
#include <helpers/gemHelper.h>
#include <sys/renderGems.h>
#include <sys/deadSystem.h>
#include <sys/gemFallingSystem.h>
#include <sys/inputSystem.h>
#include <sys/gemSwapSystem.h>
#include <sys/gemsAnimation.h>
#include <sys/checkGemLink.h>

#include <struct/state.h>
#include <time.h>

std::string resourcesDir()
{
#ifdef SFML_SYSTEM_IOS
    return "";
#else
    return "assets/";
#endif
}

#define assets(name) (resourcesDir()+name)

int main() {
    context app;
    app.render.init(768, 768);
    app.input.setWindow(app.render.window());
    app.gems.loadGems(assets("gems.png"));
    app.level.resize(12, 12);
    app.level.setMaxId(3); // 关卡最多3个种类的宝石
    app.check_link = true;

    // 初始化关卡和画面
    srand(time(nullptr));
    app.level.output([&](Level::LAYER_INDEX index, int x, int y, int id) {
        float _x = x * Gems::GEM_WIDTH + Gems::GEM_WIDTH*0.5f;
        float _y = y * Gems::GEM_HEIGHT + Gems::GEM_HEIGHT*0.5f;
        auto e = createGem(app.entity, id, Position{_x, _y}, Tile{x, y});
    });

    sf::Clock clock;
    bool click = false;
    while (app.render.alive()) {
        app.input.handleEvent([&](InputEvent& event) {
            if (event.type == sf::Event::Closed
                or (event.type == sf::Event::KeyPressed
                    and event.key.code == sf::Keyboard::Escape) ) {
                app.render.window()->close();
                return;
            }
            if (event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Left) {
                // 鼠标按下
                click = true;
                onMousePressed(app, event.mouseButton.x, event.mouseButton.y);
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                // 鼠标放开
                if (!click) {
                    return;
                }
                click = false;
                onMouseReleased(app, event.mouseButton.x, event.mouseButton.y);
            }
            if (event.type == sf::Event::MouseMoved) {
                if (!click) {
                    return;
                }
                onMouseMoved(app, event.mouseMove.x, event.mouseMove.y);
            }
        });

        auto ms = clock.restart().asMilliseconds();

        updateGemSwap(app, ms); // 处理宝石交换
        updateGemSwapReverse(app, ms); // 处理宝石位置还原
        updateGemsSelectAni(app, ms); // 处理点击宝石的动画
        checkSwapGemLink(app); // 宝石交换后检查是否连接，无连接进行复位

        gemFallingSystem(app, ms); // 处理宝石下落
        updateIndeadGems(app, ms); // 处理宝石消除效果
        updateDeadGems(app); // 处理消除后的逻辑
        checkGemLink(app); // 检查是否有宝石可以消除

        app.render.begin();
        renderGems(app); // 绘制关卡
        app.render.end();
    }
    return 0;
}