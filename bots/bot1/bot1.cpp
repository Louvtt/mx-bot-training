#include "bot/types.hpp"

#include <iostream>

void update() {
    std::cout << "bot update\n";
}
REGISTER_UPDATE(update);
