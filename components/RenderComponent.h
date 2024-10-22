#pragma once
#include <string>

struct RenderComponent {
    std::string modelFile;

    RenderComponent() : modelFile("") {}

    RenderComponent(const std::string& model) : modelFile(model) {}
};