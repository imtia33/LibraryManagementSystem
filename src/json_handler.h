#ifndef JSON_HANDLER_H
#define JSON_HANDLER_H

#include <string>
#include "../include/nlohmann/json.hpp"  // Corrected include path
#include <fstream>  // For file operations

class JsonHandler {
public:
    // Function to load JSON data from a file
    static nlohmann::json loadJson(const std::string& filePath);

    // Function to save JSON data to a file
    static void saveJson(const std::string& filePath, const nlohmann::json& jsonData);
};

#endif
