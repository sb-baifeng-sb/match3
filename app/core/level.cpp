//
// Created by baifeng on 2019-07-28.
//

#include "Level.h"

#define MAP_INDEX(x, y, w) (y*w+x)

Level::Level():w(0), h(0), max_id(0) {
}

void Level::resize(int w, int h) {
    this->w = w;
    this->h = h;
    int size = w * h;
}

void Level::setMaxId(int id) {
    this->max_id = id;
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

int Level::getMapSize() const {
    return this->w * this->h;
}