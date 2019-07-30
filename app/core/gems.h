//
// Created by baifeng on 2019-07-29.
//

#ifndef APP_GEMS_H
#define APP_GEMS_H

#include <SFML/Graphics.hpp>
#include <vector>

class Gems {
public:
    enum {
        ID_MAX = 7,
        INDEX_MAX = 3,
        GEM_WIDTH = 64,
        GEM_HEIGHT = 64,
    };
    typedef sf::Rect<int> rect;
    typedef std::vector<rect> rectArray;
    typedef std::vector<rectArray> frameArray;
    typedef sf::Texture texture;
    typedef sf::Sprite sprite;
public:
    Gems();
    void loadGems(std::string const& fileName);
    rect const& getGemFrame(int id, int index = 0) const;
    texture const& getTexture() const;
    sprite& getSprite();
private:
    sf::Texture mTex;
    sf::Sprite mSp;
    frameArray mFrames;
};

#endif //APP_GEMS_H
