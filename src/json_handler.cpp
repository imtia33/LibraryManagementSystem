#include "json_handler.h"

nlohmann::json JsonHandler::loadJson(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file) return nlohmann::json();  // Return an empty json object if file couldn't be opened
    nlohmann::json jsonData;
    file >> jsonData;  // Parse the file content into the jsonData object
    return jsonData;
}

void JsonHandler::saveJson(const std::string& filePath, const nlohmann::json& jsonData) {
    std::ofstream file(filePath);  // Open the file for writing
    file << jsonData.dump(4);  // Pretty-print JSON with 4 spaces of indentation
}
