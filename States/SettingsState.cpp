//
// Created by malte on 28/01/2024.
//

#include "SettingsState.h"

SettingsState::SettingsState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys,
                             std::stack<State *> *states, sf::Font &font) : State(window, supportedKeys, states, font) {
    this->initVariables();
    this->initBackground();
    State::initKeybinds("Config/menustate_keybinds.ini");
    this->initButtons();
    this->initDropDownLists();
    this->initOptionsText();
}

SettingsState::~SettingsState() {
    for (auto &button: this->buttons) {
        delete button.second;
    }
    for (auto &ddl: this->dropDownList) {
        delete ddl.second;
    }
}

void SettingsState::update(const float &dt) {
    State::update(dt);

    this->updateMousePositions();
    this->updateButtons();
    updateDropDownLists();
}

void SettingsState::updateDropDownLists() {
    for (auto &ddl: dropDownList) {
        ddl.second->update(mousePosView);
    }
}


void SettingsState::render(sf::RenderTarget *target) {
    if (!target) {
        target = this->window;
    }

    target->draw(this->background);
    this->renderButtons(*target);
    renderDropDownLists(target);

    target->draw(this->optionsText);
}

void SettingsState::renderDropDownLists(sf::RenderTarget *target) {
    for (auto &ddl: dropDownList) {
        ddl.second->render(*target);
    }
}

void SettingsState::handleEvent(sf::Event &event, const float &dt) {
    if (event.type == sf::Event::KeyPressed && event.key.code == this->keybinds["CLOSE"]) {
        this->endState();
    }

    for (auto &button: this->buttons) {
        button.second->handleEvent(event, mousePosView);
    }

    for (auto &ddl: this->dropDownList) {
        ddl.second->handleEvent(event, mousePosView);
    }
}

void SettingsState::initBackground() {
    this->background.setSize(
            sf::Vector2f(static_cast<float>(this->window->getSize().x),
                         static_cast<float>(this->window->getSize().y))
    );
    this->background.setFillColor(sf::Color::White);
}

void SettingsState::renderButtons(sf::RenderTarget &target) {
    for (auto &button: this->buttons) {
        button.second->render(target);
    }
}

void SettingsState::initButtons() {
    this->buttons["BACK"] = new GUI::Button(100, 400, 150, 50, &this->font, "Back", 50,
                                            sf::Color(120, 50, 80, 200),
                                            sf::Color(150, 50, 80, 250),
                                            sf::Color(90, 40, 60, 50),
                                            sf::Color(120, 50, 80, 0),
                                            sf::Color(150, 50, 80, 0),
                                            sf::Color(90, 40, 60, 0));

    this->buttons["APPLY"] = new GUI::Button(300, 400, 150, 50, &this->font, "Apply", 50,
                                             sf::Color(120, 50, 80, 200),
                                             sf::Color(150, 50, 80, 250),
                                             sf::Color(90, 40, 60, 50),
                                             sf::Color(120, 50, 80, 0),
                                             sf::Color(150, 50, 80, 0),
                                             sf::Color(90, 40, 60, 0));

}

void SettingsState::updateButtons() {
    for (auto &button: this->buttons) {
        button.second->update(mousePosView);
    }

    if (this->buttons["BACK"]->isPressed()) {
        this->endState();
    }

    if (this->buttons["APPLY"]->isPressed()) {
        //TODO: ogni volta che faccio una selezione, active element dovrebbe essere sostituito con un nuovo bottone piuttosto che modificargli il testo.
        //Non c'è più bisogno di usare selectedElementId, possiamo usare activeElement.id
        short activeElementId = this->dropDownList["RESOLUTION"]->getSelectedElementId();
        this->window->create(this->videoModes[activeElementId], "test");
    }

    for (auto &ddl: this->dropDownList) {
        ddl.second->update(mousePosView);
    }
}

void SettingsState::initDropDownLists() {
    std::vector<std::string> videomodes_str;
    videomodes_str.reserve(this->videoModes.size());
    for (auto &i: this->videoModes) {
        videomodes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
    }
    this->dropDownList["RESOLUTION"] = new GUI::DropDownList(100, 100, 200, 50, font, videomodes_str,
                                                             0);
}

void SettingsState::initOptionsText() {
    this->optionsText.setFont(this->font);
    this->optionsText.setPosition(sf::Vector2f(50.f, 100.f));
    this->optionsText.setCharacterSize(30.f);
    this->optionsText.setFillColor(sf::Color(0, 0, 0, 255));
    this->optionsText.setString("Resolution \n\nFullscreen \n\nVsync \n\nAntialiasing");
}

void SettingsState::initVariables() {
    this->videoModes = sf::VideoMode::getFullscreenModes();
}
