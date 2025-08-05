//
// Created by sohaibalam on 8/4/25.
//

#include <mdcpp/input/input.h>

#include "mdcpp/window.hpp"


namespace mdcpp {

    bool Input::isKeyPressed(KeyCode key) {
        GLFWwindow* window = Window::getActiveWindow().getWindow();
        int state = glfwGetKey(window, (int)key);
        return state == GLFW_PRESS;
    }

    bool Input::isKeyDown(KeyCode key) {
        GLFWwindow* window = Window::getActiveWindow().getWindow();
        int state = glfwGetKey(window, (int)key);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::isMouseButtonDown(MouseButton button) {
        GLFWwindow *windowHandle = Window::getActiveWindow().getWindow();
        int state = glfwGetMouseButton(windowHandle, (int)button);
        return state == GLFW_PRESS;
    }

    glm::vec2 Input::getMousePosition() {
        GLFWwindow* window = Window::getActiveWindow().getWindow();
        auto params = Window::getActiveWindow().getParams();
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        return glm::vec2((float)x - params.width * 0.5f, (float)y - params.height * 0.5f);
    }



    void Input::setCursorMode(CursorMode mode) {
        GLFWwindow* window = Window::getActiveWindow().getWindow();
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL + (int)mode);
    }



};
