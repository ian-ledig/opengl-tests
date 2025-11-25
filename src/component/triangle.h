#pragma once

#include "component.h"

class Triangle : public Component {
public:
    Triangle();
    ~Triangle();

    void init() override;
    void draw() override;

private:
    GLuint _VAO;
};