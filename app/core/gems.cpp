//
// Created by baifeng on 2019-07-29.
//

#include "gems.h"

gems::gems() {
    int xpos[ID_MAX] = {0, 64, 128, 192, 256, 320, 384};
    int ypos[INDEX_MAX] = {0, 64, 128};
    for (int i = 0; i < ID_MAX; ++i) {
        rectArray rects;
        for (int j = 0; j < INDEX_MAX; ++j) {
            rects.push_back(rect(xpos[i], ypos[j], GEM_WIDTH, GEM_HEIGHT));
        }
        mFrames.push_back(rects);
    }
}

void gems::loadGems(std::string const& fileName) {
    mTex.loadFromFile(fileName);
    mTex.setSmooth(true);
    mSp.setTexture(mTex);
    mSp.setOrigin(GEM_WIDTH*0.5f, GEM_HEIGHT*0.5f);
}

gems::rect const& gems::getGemFrame(int id, int index) const {
    if (id <= 0 || id > ID_MAX) {
        id = 1;
    }
    if (index < 0 || index >= INDEX_MAX) {
        index = 0;
    }
    return mFrames[id-1][index];
}

gems::texture const& gems::getTexture() const {
    return mTex;
}

gems::sprite& gems::getSprite() {
    return mSp;
}