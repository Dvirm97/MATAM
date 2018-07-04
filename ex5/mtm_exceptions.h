//
// Created by Yuri on 10/06/2018.
//

#ifndef EX5_MTM_EXCEPTIONS_H
#define EX5_MTM_EXCEPTIONS_H

#include <exception>

namespace mtm {

    // mtm::exception class
    class exception : public std::exception {};

    // Specific exceptions. Can be also caught as mtm::exceptions
    // or std::exceptions
    class InvalidParam : public mtm::exception {};
    class IllegalWeapon : public mtm::exception {};
    class NameAlreadyExists : public mtm::exception  {};
    class GameFull : public mtm::exception  {};
    class NameDoesNotExist : public mtm::exception  {};
}

#endif //EX5_MTM_EXCEPTIONS_H