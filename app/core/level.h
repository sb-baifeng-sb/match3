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
    typedef std::function<void(LAYER_INDEX index, int x, int y, int id)>  OutputProc;
public:
    Level();
public:
    void resize(int w, int h);
    void setMaxId(int id);
    void loadlevel(std::string const& fileName);
    void output(OutputProc proc);
    int makeGemId() const;
    int getMapWidth() const;
    int getMapHeight() const;
    int getMapSize() const;
private:
    int w, h, max_id;
};


#endif //APP_LEVEL_H
