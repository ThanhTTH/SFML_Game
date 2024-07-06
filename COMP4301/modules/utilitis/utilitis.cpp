#ifndef UTILITIS_HPP
#define UTILITIS_HPP
#include "utilitis.hpp"

namespace Utilitis {

std::string GetWorkingDirectory() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != nullptr) {
        return std::string(cwd) + "/";
    }
    return "";
}

}


#endif //UTILITIS_HPP