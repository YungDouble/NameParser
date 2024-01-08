// NameParser.h
#ifndef NAMEPARSER_H
#define NAMEPARSER_H

#include <string>

class NameParser {
private:
    std::string firstName;
    std::string middleName;
    std::string lastName;
    std::string suffix;

public:
    NameParser(const std::string& fullName);

    std::string getFirstName() const;
    std::string getMiddleName() const;
    std::string getLastName() const;
    std::string getSuffix() const;

private:
    void parseFullName(const std::string& fullName);
    static void trimSpaces(std::string& str);
    void extractSuffix(std::string& fullName);
    bool isValidSuffix(const std::string& fullName, size_t pos, size_t legnth);
    void removeSingleDots(std::string& str);
};

#endif // NAMEPARSER_H
