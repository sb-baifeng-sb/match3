//
// Created by baifeng on 2019-07-28.
//

#ifndef APP_LEVEL_H
#define APP_LEVEL_H

#include <vector>
#include <functional>
#include <entt/entt.hpp>

class Level {
public:
    enum LAYER_INDEX {
        FLOOR = 0,
        TILE,
    };
    typedef std::vector<entt::entity> Layer;
    typedef std::function<void(LAYER_INDEX index, int x, int y, int id)>  OutputProc;
public:
    Level();
public:
    void clear();
    void resize(int w, int h);
    void setMaxId(int id);
    void set(LAYER_INDEX index, int x, int y, entt::entity e);
    entt::entity get(LAYER_INDEX index, int x, int y) const;
    void loadlevel(std::string const& fileName);
    void output(OutputProc proc);
    int makeGemId() const;
    int getMapWidth() const;
    int getMapHeight() const;
private:
    Layer& layer(LAYER_INDEX index);
    Layer const& layer(LAYER_INDEX index) const;
private:
    int w, h, max_id;
    Layer mLayers[2];
};


#endif //APP_LEVEL_H
