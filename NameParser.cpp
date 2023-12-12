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

std::string NameParser::getAlias() const {
    return alias;
}

// Helper function to parse the full name
// Helper function to parse the full name
void NameParser::parseFullName(const std::string& fullName) {
    std::istringstream iss(fullName);
    std::vector<std::string> nameParts;
    std::string part;

    while (iss >> part) {
        nameParts.push_back(part);
    }

    size_t namePartsSize = nameParts.size();

    // Identify and preserve particles in the last name
    if (namePartsSize > 1) {
        size_t lastIdx = namePartsSize - 1;
        if (nameParts[lastIdx] == "De" || nameParts[lastIdx] == "Di" || nameParts[lastIdx] == "La" || nameParts[lastIdx] == "Al") {
            lastName = nameParts[lastIdx];
            nameParts.pop_back();
            --namePartsSize;
        }
    }

    // Set the last name
    if (!nameParts.empty()) {
        lastName = nameParts.front();
    }

    // Set the first name
    if (namePartsSize > 1) {
        firstName = nameParts[1];
    }

    // Concatenate the remaining parts as the middle name
    std::ostringstream ossMiddle;
    for (size_t i = 2; i < namePartsSize - 1; ++i) {
        if (nameParts[i].back() == '-') {
            ossMiddle << nameParts[i] << nameParts[i + 1] << ' ';
            ++i; // Skip the next part
        } else {
            ossMiddle << nameParts[i] << ' ';
        }
    }
    // Add the last part to the middle name
    if (namePartsSize > 2) {
        ossMiddle << nameParts.back();
    }
    middleName = ossMiddle.str();

    // Set the alias
    alias = extractAlias(fullName);

    // Trim spaces
    trimSpaces(firstName);
    trimSpaces(middleName);
    trimSpaces(lastName);
    trimSpaces(alias);
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

// Helper function to extract alias from a name part
std::string NameParser::extractAlias(const std::string& name) {
    std::string alias;

    // Check for common alias patterns
    if (name.find("Jr") != std::string::npos || name.find("jr") != std::string::npos ||
        name.find("Jr.") != std::string::npos || name.find("II") != std::string::npos ||
        name.find("III") != std::string::npos) {
        alias = name;
    }

    return alias;
}
