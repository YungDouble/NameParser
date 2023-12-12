// CSVProcessor.h

#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <string>
#include <vector>

class CSVProcessor {
public:
    static void processCSV(const std::string& inputFileName, const std::string& outputFileName);
};

#endif // CSVPARSER_H
