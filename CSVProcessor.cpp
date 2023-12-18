// CSVProcessor.cpp

#include "CSVProcessor.h"
#include "NameParser.h"
#include <fstream>
#include <sstream>

void CSVProcessor::processCSV(const std::string& inputFileName, const std::string& outputFileName) {
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

        // Extract the Fullname column
        std::getline(iss, dirtyFullName, ',');

        // Clean up the full name by removing errant commas
        std::string cleanedFullName = cleanFullName(dirtyFullName);

        // Parse the cleaned name using NameParser
        NameParser nameParser(cleanedFullName);

        // Write the original line along with the parsed name components and alias
        outputFile << line << "," << nameParser.getLastName() << ","
                   << nameParser.getFirstName() << "," << nameParser.getMiddleName() << ","
                   << nameParser.getSuffix() << std::endl;
    }

    // Close files
    inputFile.close();
    outputFile.close();
}
