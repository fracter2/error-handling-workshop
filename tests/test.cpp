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
	const std::string path = "../data/config_ok.txt"s;
	try {
		Config conf(path);
		EXPECT_EQ(1280, conf.width);
		EXPECT_EQ(720, conf.height);
		EXPECT_EQ("My Awesome Game"s, conf.title);
	}
	catch (std::exception e) {
		FAIL();
	}
}

TEST(ConfigLoader, HandlesMissingFile){
	const std::string path = "../data/does_not_exist.txt"s;

	EXPECT_THROW(Config conf(path), std::exception);
	
	// In the refactor, assert that the correct error code is returned, or that the correct exception is thrown.
}
/*
TEST(ConfigLoader, HandlesMalformedFile){
	const std::string path = "../data/config_malformed.txt"s;
	bool ok = load_config(path);
	EXPECT_FALSE(ok); // Expected load_config to fail for malformed file
	
	// After refactor: check that the error is ConfigError::ParseError.
}

TEST(ConfigLoader, HandlesMissingField){
	const std::string path = "../data/config_missing_field.txt"s;
	bool ok = load_config(path);
	EXPECT_FALSE(ok);// Expected load_config to fail for missing field"
	// After refactor: check that the error is ConfigError::MissingField.
}

TEST(ConfigLoader, HandlesInvalidValues){
	const std::string path = "../data/config_invalid_value.txt"s;
	bool ok = load_config(path);
	EXPECT_FALSE(ok); // "Expected load_config to fail for invalid value"
	
	// After refactor: check that the error is ConfigError::InvalidValue.
}
*/
RESTORE_WARNINGS