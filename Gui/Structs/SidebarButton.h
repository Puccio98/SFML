#pragma once

#include <string>
#include <utility>

struct SidebarButton {
    std::string key;
    std::string label;
    bool isSwitch;

    SidebarButton(std::string key, std::string label, bool isSwitch) : key(std::move(key)), label(std::move(label)),
                                                                       isSwitch(isSwitch) {}
};