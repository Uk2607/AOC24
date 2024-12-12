#include "file_name.h"
#include <iostream>

std::string get_file_name(int argc, char* argv[], std::string default_input) {
    std::string file_name;
    if (argc > 1) file_name = argv[1];
    else {
        std::cout << "Enter file name: ";
        std::getline(std::cin, file_name);
        if (file_name.length() == 0) file_name = default_input;
    }
    return file_name;
}
