//
// Created by baifeng on 2019-07-28.
//

#include "Level.h"

#define MAP_INDEX(x, y, w) (y*w+x)

Level::Level():w(0), h(0), max_id(0) {
    this->layer(FLOOR).clear();
    this->layer(TILE).clear();
}

void Level::clear() {
    this->layer(FLOOR).clear();
    this->layer(TILE).clear();
}

void Level::resize(int w, int h) {
    this->w = w;
    this->h = h;
    int size = w * h;
    this->clear();
    for (int i = 0; i < size; ++i) {
        this->layer(LAYER_INDEX::FLOOR).push_back(entt::null);
        this->layer(LAYER_INDEX::TILE).push_back(entt::null);
    }
}

void Level::setMaxId(int id) {
    this->max_id = id;
}

void Level::set(LAYER_INDEX index, int x, int y, entt::entity e) {
    if (x < 0 || x >= this->w || y < 0 || y >= this->h) {
        return;
    }
    this->layer(index)[MAP_INDEX(x, y, this->w)] = e;
}

entt::entity Level::get(LAYER_INDEX index, int x, int y) const {
    if (x < 0 || x >= this->w || y < 0 || y >= this->h) {
        return entt::null;
    }
    return this->layer(index)[MAP_INDEX(x, y, this->w)];
}

Level::Layer& Level::layer(LAYER_INDEX index) {
    return mLayers[int(index)];
}

Level::Layer const& Level::layer(LAYER_INDEX index) const {
    return mLayers[int(index)];
}

void Level::loadlevel(std::string const& fileName) {

}

void Level::output(OutputProc proc) {
    int size = this->w * this->h;
    std::vector<int> arr;
    arr.reserve(size);
    for (int i = 0; i < size; ++i) {
        arr.push_back(rand()%this->max_id+1);
    }
    for (int i = 0; i < size; ++i) {
        proc(LAYER_INDEX::TILE, i % this->w, i / this->w, arr[i]);
    }
}

int Level::makeGemId() const {
    return rand()%this->max_id+1;
}

int Level::getMapWidth() const {
    return this->w;
}

int Level::getMapHeight() const {
    return this->h;
}