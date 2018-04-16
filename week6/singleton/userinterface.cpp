#include "userinterface.h"

UserInterface::UserInterface(int height, int width)
    : m_height(height)
    , m_width(width)
{}

UserInterface& UserInterface::getInstance(int height, int width){
    static UserInterface ui(height, width);
    return ui;
}
