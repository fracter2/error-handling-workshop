#include "pch.h"
#include <string>
#include <string_view>
#include "../demo/bad_config_loader.hpp"
using namespace std::string_literals;
using namespace std::string_view_literals;

DISABLE_WARNINGS_FROM_GTEST

// For now, these tests still use the bad API.
// Part of the exercise is to update the tests when you redesign the API.

TEST(ConfigLoader, LoadsKnownGoodFile){
	const std::string path = "data/config_ok.txt"s;
	bool ok = load_config(path);
	EXPECT_TRUE(ok); //we expect load_config to succeed for config_ok.txt
	EXPECT_EQ(1280, g_config.width);
	EXPECT_EQ(720, g_config.height);
	EXPECT_EQ("My Awesome Game"s, g_config.title);

	// In the refactored version you should no longer rely on g_config.
	// Adjust this test to work with your new API.	
}

TEST(ConfigLoader, HandlesMissingFile){
	const std::string path = "data/does_not_exist.txt"s;
	bool ok = load_config(path);
	EXPECT_FALSE(ok); //we expect load_config to fail for missing file
	
	// In the refactor, assert that the correct error code is returned, or that the correct exception is thrown.
}

TEST(ConfigLoader, HandlesMalformedFile){
	const std::string path = "data/config_malformed.txt"s;
	bool ok = load_config(path);
	EXPECT_FALSE(ok); // Expected load_config to fail for malformed file
	
	// After refactor: check that the error is ConfigError::ParseError.
}

TEST(ConfigLoader, HandlesMissingField){
	const std::string path = "data/config_missing_field.txt"s;
	bool ok = load_config(path);
	EXPECT_FALSE(ok);// Expected load_config to fail for missing field"
	// After refactor: check that the error is ConfigError::MissingField.
}

TEST(ConfigLoader, HandlesInvalidValues){
	const std::string path = "data/config_invalid_value.txt"s;
	bool ok = load_config(path);
	EXPECT_FALSE(ok); // "Expected load_config to fail for invalid value"
	
	// After refactor: check that the error is ConfigError::InvalidValue.
}

RESTORE_WARNINGS