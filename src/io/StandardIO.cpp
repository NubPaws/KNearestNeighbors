#include <string>
#include <iostream>

#include "DefaultIO.h"

std::string StandardIO::read() {
    std::string input;
    std::cin >> input;
    return input;
}

void StandardIO::write(const std::string& dataToWrite) {
    std::cout << dataToWrite << std::endl;
}
