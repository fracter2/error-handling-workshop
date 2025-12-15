#include "bad_config_loader.hpp"
#include <string>
#include <fstream>
#include <iostream>


int parse_int(std::ifstream& stream) { 
    int value = 0;
    int min = 0;
    int max = 8192;
    stream >> value;
    if (value < min || value > max) { // TODO Consider checking if stream is bad or endofline
        throw ConfigErr("Resolution out of range");
    }
    return value;
}
    
std::string parse_string(std::ifstream& stream) {
    // Consume the end of line and then read the title line.
    std::string value = {};
    std::getline(stream, value);         // consume rest of line after height
    std::getline(stream, value);         // actual title line
    if (value.empty()) {
        throw ConfigErr("Title is empty");
    }
    return value;
}

void load_config(const std::string& path, std::ifstream& stream) {
    if (!path.find(".txt")) {
        throw ConfigErr("Wrong file extension, expected .txt");
    }

    stream.open(path);
    if (!stream.is_open()) {
        throw ConfigErr("Could not open file, missing or lacking permission");
    }

    if (stream.eof()) {
        throw ConfigErr("file is empty");
    }

    if (!stream.good()) {
        throw ConfigErr("Could not open file");
    }

}

Config::Config(const std::string& path) {
    std::ifstream stream = {};
    load_config(path, stream);
    width = parse_int(stream);
    height = parse_int(stream);
    title = parse_string(stream);
}

// Very naive, intentionally poor implementation.
// - Uses a global Config.
// - Returns only bool, no info about the error.
// - Logs to std::cerr inside the loader.
// - Mixes loading, validation, defaults, and logging.
// - Minor nits: takes string, should prefer std::string_view
//      or even std::filesystem::path
//bool load_config(const std::string& path)
//{
//    //std::ifstream in(path);
//    //if (!in) {
//    //    std::cerr << "Failed to open config file: " << path << "\n";
//    //    g_config = Config{800, 600, "Default Title"};
//    //    return false;
//    //}
//
//    //int width = 0;
//    //int height = 0;
//    //std::string title;
//
//    // Try to read width and height.
//    // We do almost no error checking here on purpose.
//    //in >> width;
//    //in >> height;
//
//    if (!in) {
//        std::cerr << "Failed to read width/height from config file: " << path << "\n";
//        g_config = Config{800, 600, "Default Title"};
//        return false;
//    }
//
//    // Consume the end of line and then read the title line.
//    std::getline(in, title);         // consume rest of line after height
//    std::getline(in, title);         // actual title line
//
//    if (!in) {
//        std::cerr << "Failed to read title from config file: " << path << "\n";
//        g_config = Config{800, 600, "Default Title"};
//        return false;
//    }
//
//    // Minimal validation (also intentionally weak).
//    if (width <= 0 || height <= 0) {
//        std::cerr << "Invalid resolution in config file: "
//                  << width << "x" << height << "\n";
//        // Still returns false, but we also silently overwrite with defaults.
//        g_config = Config{800, 600, "Default Title"};
//        return false;
//    }
//
//    if (title.empty()) {
//        std::cerr << "Empty title in config file\n";
//        // Arbitrary choice: still treat it as success but fix the title.
//        title = "Untitled Game";
//    }
//
//    g_config.width = width;
//    g_config.height = height;
//    g_config.title = title;
//
//    return true;
//}