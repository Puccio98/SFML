#ifndef SFML_HEALTHBAR_H
#define SFML_HEALTHBAR_H

#include <SFML/Graphics.hpp>
#include "Structs/ProgressBarData.h"

namespace GUI {
    class HealthBar {
    public:
        explicit HealthBar(const ProgressBarData &progressBarData);

        virtual ~HealthBar();

        void update(const ProgressBarData &progressBarData);

        void render(sf::RenderTarget &target);

    private:
        std::vector<sf::RectangleShape> hpContainers;
        std::string fullHeartTexturePath;
        std::string emptyHeartTexturePath;
        sf::Texture fullHeartTexture;
        sf::Texture emptyHeartTexture;

        float width;
        float height;

        void init(const ProgressBarData &progressBarData);

        void updateContainer(int containerIndex, const ProgressBarData &progressBarData);
    };
}

#endif //SFML_HEALTHBAR_H
