// main.cpp

#include "NameParser.h"
#include <iostream>

// main.cpp

#include "CSVProcessor.h"

int main() {
    // Specify input and output CSV file names
    std::string inputFileName = "input.csv";
    std::string outputFileName = "output.csv";

    // Process the CSV file
    CSVProcessor::processCSV(inputFileName, outputFileName);

    return 0;
}
