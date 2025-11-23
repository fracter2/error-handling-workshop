#pragma once
#include <string>

struct Config {
    int width;
    int height;
    std::string title;
};

// Global configuration object used by the bad implementation.
// Part of the exercise is to get rid of this.
extern Config g_config;

// Loads configuration from a text file.
//
// Returns true on success, false on failure.
// On success, g_config is updated.
// On failure, g_config may be modified or left with default values.
bool load_config(const std::string& path);
