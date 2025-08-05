//
// Created by sohaibalam on 8/4/25.
//

#ifndef INPUT_H
#define INPUT_H

#include <mdcpp/input/keycodes.h>

#include "glm/vec2.hpp"

namespace mdcpp {
    class Input {
    public:
        static bool isKeyDown(KeyCode key);
        static bool isKeyPressed(KeyCode key);
        static bool isMouseButtonDown(MouseButton button);

        static glm::vec2 getMousePosition();
        static void setCursorMode(CursorMode mode);
    };
};

#endif //INPUT_H
