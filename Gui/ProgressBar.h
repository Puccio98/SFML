#ifndef SFML_PROGRESSBAR_H
#define SFML_PROGRESSBAR_H

#include <SFML/Graphics.hpp>
#include "Structs/ProgressBarData.h"

namespace GUI {
    class ProgressBar {
    public:
        explicit ProgressBar(const sf::Font &font, const ProgressBarData &progressBarData);

        virtual ~ProgressBar();

        void update(const ProgressBarData &progressBarData);

        void render(sf::RenderTarget &target);

    private:
        sf::RectangleShape progressBarBack;
        sf::RectangleShape progressBarFilled;
        sf::Font font;

        float width = 100.f;
        float height = 20.f;

        void init(const ProgressBarData &progressBarData);

        float calculateProgress(float maxValue, float currentValue) const;
    };
}

#endif //SFML_PROGRESSBAR_H
