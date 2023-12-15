#include "NameParser.h"
#include <sstream>
#include <vector>

NameParser::NameParser(const std::string& fullName) {
    parseFullName(fullName);
}

std::string NameParser::getFirstName() const {
    return firstName;
}

std::string NameParser::getMiddleName() const {
    return middleName;
}

std::string NameParser::getLastName() const {
    return lastName;
}

std::string NameParser::getSuffix() const {
    return suffix;
}

void NameParser::parseFullName(const std::string& fullName) {
    // Remove leading and trailing spaces, dots, and dashes
    std::string cleanedName = fullName;
    trimSpaces(cleanedName);
    removeSingleDots(cleanedName);
    // removeDashes(cleanedName);

    std::istringstream iss(cleanedName);
    std::vector<std::string> nameParts;
    std::string part;

    while (std::getline(iss, part, ' ')) {
        // Trim leading and trailing spaces from each part
        trimSpaces(part);

        nameParts.push_back(part);
    }

    size_t namePartsSize = nameParts.size();

    // Extract and set the suffix
    extractSuffix(cleanedName);

    // Set the last name as the leftmost part
    if (!nameParts.empty()) {
        lastName = nameParts.front();
        nameParts.erase(nameParts.begin()); // Remove the last name from the vector
        --namePartsSize;
    }

    // Set the first name
    if (!nameParts.empty()) {
        firstName = nameParts.front();
        nameParts.erase(nameParts.begin()); // Remove the first name from the vector
        --namePartsSize;
    }

    // Concatenate the remaining parts as the middle name
    std::ostringstream ossMiddle;
    for (const auto& part : nameParts) {
        ossMiddle << part << ' ';
    }

    middleName = ossMiddle.str();

    // Remove single dots after letters in the middle name
    removeSingleDots(middleName);

    // Trim spaces
    trimSpaces(firstName);
    trimSpaces(middleName);
    trimSpaces(lastName);
}

void NameParser::trimSpaces(std::string& str) {
    size_t start = str.find_first_not_of(' ');
    size_t end = str.find_last_not_of(' ');

    if (start != std::string::npos && end != std::string::npos) {
        str = str.substr(start, end - start + 1);
    } else {
        str.clear();
    }
}
void NameParser::extractSuffix(std::string& fullName) {
    // Check for common suffix patterns
    size_t jrPos = fullName.find("Jr");
    size_t iiPos = fullName.find("II");
    size_t iiiPos = fullName.find("III");

    if (jrPos != std::string::npos) {
        suffix = "Jr";
        fullName.erase(jrPos, 2); // Remove "Jr" from the string
    } else if (iiPos != std::string::npos) {
        suffix = "II";
        fullName.erase(iiPos, 2); // Remove "II" from the string
    } else if (iiiPos != std::string::npos) {
        suffix = "III";
        fullName.erase(iiiPos, 3); // Remove "III" from the string
    }
}

void NameParser::removeSingleDots(std::string& str) {
    size_t dotPos = str.find('.');
    if (dotPos != std::string::npos && dotPos == str.length() - 1) {
        str.pop_back();  // Remove the dot
    }
}
