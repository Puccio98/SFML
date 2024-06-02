#include "SettingsState.h"
#include "../ResourceFiles/PushButton.h"

SettingsState::SettingsState(StateData &stateData) : State(stateData) {
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
        target = this->stateData.window;
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
            sf::Vector2f(static_cast<float>(this->stateData.window->getView().getSize().x),
                         static_cast<float>(this->stateData.window->getView().getSize().y))
    );
    this->background.setFillColor(sf::Color::White);
}

void SettingsState::renderButtons(sf::RenderTarget &target) {
    for (auto &button: this->buttons) {
        button.second->render(target);
    }
}

void SettingsState::initButtons() {
    this->buttons["BACK"] = new GUI::PushButton(100, 400, 150, 50, this->stateData.font, "Back", 50,
                                                CssColor::ClassicText(), CssColor::ClassicButton());

    this->buttons["APPLY"] = new GUI::PushButton(300, 400, 150, 50, this->stateData.font, "Apply", 50,
                                                 CssColor::ClassicText(), CssColor::ClassicButton());
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

        // Recupera view originale, setta la dimensione della finestra e gli applica la view originale
        sf::View view = this->stateData.window->getView();
        this->stateData.window->setSize(
                sf::Vector2u(this->videoModes[activeElementId].width, this->videoModes[activeElementId].height));
        this->stateData.window->setView(view);

        auto desktop = sf::VideoMode::getDesktopMode();
        this->stateData.window->setPosition(sf::Vector2i(desktop.width / 2 - this->stateData.window->getSize().x / 2,
                                                         desktop.height / 2 - this->stateData.window->getSize().y / 2));

        //aggiorno la risoluzione nel file
        this->stateData.graphicsSettings->resolution = this->videoModes[activeElementId];
        this->stateData.graphicsSettings->save();
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

    int index = 0;
    sf::Vector2u currentVideoModeSize = this->stateData.window->getSize();
    for (int i = 0; i < this->videoModes.size(); i++) {
        if (this->videoModes[i].width == currentVideoModeSize.x &&
            this->videoModes[i].height == currentVideoModeSize.y) {
            index = i;
        }
    }
    this->dropDownList["RESOLUTION"] = new GUI::DropDownList(300, 100, 200, 50, *this->stateData.font, videomodes_str,
                                                             index);
}

void SettingsState::initOptionsText() {
    this->optionsText.setFont(*this->stateData.font);
    this->optionsText.setPosition(sf::Vector2f(50.f, 100.f));
    this->optionsText.setCharacterSize(30.f);
    this->optionsText.setFillColor(sf::Color(0, 0, 0, 255));
    this->optionsText.setString("Resolution \n\nFullscreen \n\nVsync \n\nAntialiasing");
}

void SettingsState::initVariables() {
    // Recuperiamo tutte le videomode accettate dal monitor
    //this->videoModes = sf::VideoMode::getFullscreenModes();
    //Scegliamo noi quali videomode rendere disponibili
    this->videoModes.emplace_back(1920, 1080);
    this->videoModes.emplace_back(1600, 900);
    this->videoModes.emplace_back(1366, 768);
    this->videoModes.emplace_back(1280, 720);
}
