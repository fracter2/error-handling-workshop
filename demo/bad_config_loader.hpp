#pragma once
#include <string>
#include <string_view>
#include <exception>

struct Config {
    int width;
    int height;
    std::string title;

    Config(const std::string& path); // Throws ConfigErr on fail
};

struct ConfigErr : public std::exception {
private:
    std::string message;
public:

    // Constructor accepting const char*
    ConfigErr(std::string_view msg) :
        message(msg) {
    }

    const char* what() const noexcept {
        return message.c_str();
    }
};

void load_config(const std::string& path, std::ifstream& stream); // Opens file with file reader, throws ConfigErr on exception


// todo sepparate ^ into helper funcs and use in constructor
// If error in load_conf, throw our custom exception
// Then fix cpp and adapt main with try catch  statements

int parse_int(std::ifstream& stream); // Throws curstom err on fail
std::string parse_string(std::ifstream& stream); // throws custom err on fail



// Config(filePath) {
//      std::inputstream stream;
//      load_config(filepath);
//      width = parse_int();
//      height = parse_int();
//      title = parse_string();
// }
