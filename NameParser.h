// NameParser.h
#ifndef NAMEPARSER_H
#define NAMEPARSER_H

#include <string>

class NameParser {
private:
    std::string firstName;
    std::string middleName;
    std::string lastName;
    std::string alias;

public:
    NameParser(const std::string& fullName);

    std::string getFirstName() const;
    std::string getMiddleName() const;
    std::string getLastName() const;
    std::string getAlias() const;

private:
    void parseFullName(const std::string& fullName);
    static void trimSpaces(std::string& str);
    static std::string extractAlias(const std::string& name);
};

#endif // NAMEPARSER_H
