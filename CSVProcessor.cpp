#include "CSVProcessor.h"
#include "NameParser.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

// Helper function to clean full name by removing commas
std::string cleanFullName(const std::string& dirtyFullName) {
    std::string cleanedFullName = dirtyFullName;

    // To remove instances of " - " with just "-"
    size_t dashPos = cleanedFullName.find(" - ");
    while (dashPos != std::string::npos) {
        cleanedFullName.replace(dashPos, 3, "-");
        dashPos = cleanedFullName.find(" - ");
    }

    // Use std::remove_if with a lambda function
    cleanedFullName.erase(std::remove_if(cleanedFullName.begin(), cleanedFullName.end(),
                                         [](char c) { 
                                            // adding additional characters to clean up
                                            return (c == ','|| c == '(' || c == ')' || c == '*');
                                        }),
                          cleanedFullName.end());

    return cleanedFullName;
}

// Helper function to capitalize the first letter of each string
std::string capitalizeFirstLetter(const std::string& str) {
    std::string result = str;
    if (!result.empty()) {
        result[0] = std::toupper(result[0]);
    }
    return result;
}

void CSVProcessor::processCSV(const std::string& inputFileName, const std::string& outputFileName, int fullNameColumnIndex) {
    std::ifstream inputFile(inputFileName);
    std::ofstream outputFile(outputFileName);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        // Handle error
        return;
    }

    // Read the header
    std::string header;
    std::getline(inputFile, header);

    // Write the new header
    outputFile << header << ",LastName,FirstName,MiddleName,Alias" << std::endl;

    // Process each line in the CSV
    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string dirtyFullName;

        // Extract the specified Fullname column
        for (int i = 0; i < fullNameColumnIndex; ++i) {
            if (!std::getline(iss, dirtyFullName, ',')) {
                // Handle the case where the specified column index is out of bounds
                std::cerr << "Error: Specified column index is out of bounds." << std::endl;
                return;
            }
        }

        // Clean up the full name by removing errant commas
        std::string cleanedFullName = cleanFullName(dirtyFullName);

        // Parse the cleaned name using NameParser
        NameParser nameParser(cleanedFullName);

        // Capitalize first letter of each component
        std::string lastName = capitalizeFirstLetter(nameParser.getLastName());
        std::string firstName = capitalizeFirstLetter(nameParser.getFirstName());
        std::string middleName = capitalizeFirstLetter(nameParser.getMiddleName());
        std::string suffix = capitalizeFirstLetter(nameParser.getSuffix());

        // Write the original line along with the parsed name components and suffix
        outputFile << line << "," << lastName << ","
                   << firstName << "," << middleName << ","
                   << suffix << std::endl;
    }

    // Close files
    inputFile.close();
    outputFile.close();
}
