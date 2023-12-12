// NameParser.cpp

#include "NameParser.h"
#include <sstream>
#include <vector>
#include <iostream>

// Constructor
NameParser::NameParser(const std::string& fullName) {
    parseFullName(fullName);
}

// Getter functions
std::string NameParser::getFirstName() const {
    return firstName;
}

std::string NameParser::getMiddleName() const {
    return middleName;
}

std::string NameParser::getLastName() const {
    return lastName;
}

// Helper function to parse the full name

void NameParser::parseFullName(const std::string& fullName) {
    std::istringstream iss(fullName);
    std::vector<std::string> nameParts;
    std::string part;

    while (std::getline(iss, part, ' ')) {
        nameParts.push_back(part);
    }

    if (!nameParts.empty()) {
        lastName = nameParts.front();
        nameParts.erase(nameParts.begin());
    }

    if (!nameParts.empty()) {
        firstName = nameParts.front();
        nameParts.erase(nameParts.begin());
    }

    std::ostringstream oss;
    for (const auto& namePart : nameParts) {
        oss << namePart << ' ';
    }
    middleName = oss.str();

    trimSpaces(firstName);
    trimSpaces(middleName);
    trimSpaces(lastName);
}

// Helper function to remove leading and trailing spaces from a string
void NameParser::trimSpaces(std::string& str) {
    size_t start = str.find_first_not_of(' ');
    size_t end = str.find_last_not_of(' ');

    if (start != std::string::npos && end != std::string::npos) {
        str = str.substr(start, end - start + 1);
    } else {
        str.clear();
    }
}