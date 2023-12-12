// NameParser.h

#ifndef NAMEPARSER_H
#define NAMEPARSER_H

#include <string>

class NameParser {
private:
    std::string firstName;
    std::string middleName;
    std::string lastName;

public:
    NameParser(const std::string& fullName);

    std::string getFirstName() const;
    std::string getMiddleName() const;
    std::string getLastName() const;

private:
    void parseFullName(const std::string& fullName);
    static void trimSpaces(std::string& str);
};

#endif // NAMEPARSER_H
