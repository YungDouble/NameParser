#include "NameParser.h"
#include <sstream>
#include <vector>
#include <algorithm> // for std::transform

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

    std::istringstream iss(cleanedName);
    std::vector<std::string> nameParts;
    std::string part;

    while (std::getline(iss, part, ' ')) {
        // Trim leading and trailing spaces from each part
        trimSpaces(part);

        nameParts.push_back(part);
    }

    size_t namePartsSize = nameParts.size();

    // Set the last name as the leftmost part
    if (!nameParts.empty()) {
        lastName = nameParts.front();
        nameParts.erase(nameParts.begin()); // Remove the last name from the vector
        --namePartsSize;
    }

    // Extract and set the suffix
    extractSuffix(lastName);

    // If there is a suffix, set the first name and remove it from the vector
    if (!suffix.empty() && !nameParts.empty()) {
        firstName = nameParts.front();
        nameParts.erase(nameParts.begin()); // Remove the first name from the vector
        --namePartsSize;
    } else if (!nameParts.empty()) {
        // If there is no suffix, set the first name directly
        firstName = nameParts.front();
        nameParts.erase(nameParts.begin()); // Remove the first name from the vector
        --namePartsSize;
    }

   // Concatenate the remaining parts as the middle name
    std::ostringstream ossMiddle;
    for (const auto& part : nameParts) {
        ossMiddle << part << ' ';
    }

    // Check for suffix in middle name
    std::string middleNameString = ossMiddle.str();
    extractSuffix(middleNameString);

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
    // Convert the input string to lowercase for case-insensitive comparison
    std::transform(fullName.begin(), fullName.end(), fullName.begin(), ::tolower);

    // Check for common suffix patterns
    size_t jrPos = fullName.find("jr");
    size_t iiPos = fullName.find("ii");
    size_t iiiPos = fullName.find("iii");

    if (isValidSuffix(fullName, jrPos, 2)) {
        suffix = "Jr";
        fullName.erase(jrPos, 2); // Remove "Jr" from the string
    } else if (isValidSuffix(fullName, iiPos, 2)) {
        suffix = "II";
        fullName.erase(iiPos, 2); // Remove "II" from the string
    } else if (isValidSuffix(fullName, iiiPos, 3)) {
        suffix = "III";
        fullName.erase(iiiPos, 3); // Remove "III" from the string
    }
}

bool NameParser::isValidSuffix(const std::string& fullName, size_t pos, size_t length) {
    // Check if the suffix stands alone and is not part of a larger word
    if (pos != std::string::npos) {
        // Check the character before the suffix
        if (pos > 0 && isalpha(fullName[pos - 1])) {
            return false;
        }

        // Check the character after the suffix
        if (pos + length < fullName.length() && isalpha(fullName[pos + length])) {
            return false;
        }

        return true;
    }

    return false;
}

void NameParser::removeSingleDots(std::string& str) {
    size_t dotPos = str.find('.');
    if (dotPos != std::string::npos && dotPos == str.length() - 1) {
        str.pop_back();  // Remove the dot
    }
}
