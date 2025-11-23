# Error Handling Workshop – Modern C++ and Best Practices

This workshop is about **designing and implementing an error handling strategy** for a small but realistic module: loading a game configuration from a file.

The starting code is deliberately messy. Your job is to:

1. Classify the different kinds of failures.
2. Design a consistent error policy for the module.
3. Refactor the implementation to follow that policy.
4. Handle errors at the call site.
5. Add tests for both success and failure cases.

The focus is not on the file format itself, but on **how the API signals failures** and how callers respond.

---

## File format

The configuration format is intentionally simple:

- First line: `width` (integer)
- Second line: `height` (integer)
- Third line: `title` (string, rest of line)

Example:

```
1280
720
My Awesome Game
```

### Sample files are in data/:

* config_ok.txt – valid config.
* config_missing_field.txt – missing or incomplete line.
* config_invalid_value.txt – values that should be rejected.
* config_malformed.txt – non-numeric where a number is expected.

## Learning goals

By the end of the workshop you should be able to:

* *Distinguish between:*
    * Programming bugs / invariant violations
    * Environmental or user errors (file missing, malformed input)
    * Expected failure as a normal branch (for example: config file not found and we fall back to defaults)
* *Choose appropriate mechanisms:*
    * Assertions / precondition checks
    * Exceptions
    * Optional / expected / error codes for recoverable failures
* Implement the chosen error handling strategy consistently across a small module.
* Write tests that cover both success and failure paths.

---

## Workshop Structure

### **Part 1 – Warm-up (Classification Exercise)**

In small groups, consider failures like:

- Config file does not exist.
- Config file exists but contains non-numeric width/height.
- Width or height is zero or negative.
- Title line is missing or empty.
- Internal logic later assumes `width > 0` and `height > 0` and crashes when this is violated.

For each case, decide:

- **Is this:**
    - A programming bug / invariant violation?
    - An environmental or user error?
    - An expected failure that the caller can branch on?

- **Which mechanism would you use:**
    - Assertion / contract check?
    - Exception?
    - Optional / expected / error code?

Be ready to explain your choices.

---

### **Part 2 – Design a Better Error API**

Look at `bad_config_loader.hpp` and `bad_config_loader.cpp`.

The current API is:

```cpp
struct Config {
    int width;
    int height;
    std::string title;
};

extern Config g_config;

bool load_config(const std::string& path);
```

#### Problems to notice (non-exhaustive):

* Uses a global g_config.
* Returns only bool, no information about what went wrong.
* Logs errors deep inside the loader.
* Mixes concerns: loading, validation, fallback defaults, logging.

#### Your task
* On paper (or in comments), design a new API for loading config:
* Decide what you want the public signature to be.

#### Example options:

**Exception-based:**

   `Config load_config(std::string_view path); // throws on error`

**Optional:**

  `std::optional<Config> load_config(std::string_view path);`

**Expected with an error type**
```
enum class ConfigError {
    FileNotFound,
    ParseError,
    MissingField,
    InvalidValue,
};

std::expected<Config, ConfigError> load_config(std::string_view path);
```

You can extend this if needed.

Decide what should be treated as an invariant (checked with assert or similar) versus a recoverable error that the caller must handle.

### **Part 3 – Refactor the Loader**

Refactor `bad_config_loader.cpp` so that:

- `g_config` is no longer used.
- The loader:
    - Reads the file.
    - Validates the contents.
    - Signals errors using your chosen API.
- The loader does **not** log or print errors. It only returns them.
- Invariants are documented and enforced with assertions or similar checks.

You may want to split the logic into helper functions, for example:

```cpp
auto parse_config(std::istream& in)
    -> ConfigResult; // or expected<Config, ConfigError>
```

---

### **Part 4 – Handle Errors at the Boundary**

Look at `main.cpp` in the demo project. Currently it uses the old API in a very naive way.

Update `main.cpp` to:

- Call your new `load_config` API.
- Handle success and failure explicitly.
- Decide what to do on failure:
    - Print a user-friendly message?
    - Fall back to default values?
    - Exit the program?

Make that decision explicit in the code.

---

### **Part 5 – Add Tests**

In `test/tests.cpp` you will find a Google Test harness.

Your tasks:
- Add tests that cover:
    - Loading `config_ok.txt` successfully.
    - Failing with the correct error for:
        - Missing file (e.g., `data/does_not_exist.txt`).
        - `config_malformed.txt`.
        - `config_missing_field.txt`.
        - `config_invalid_value.txt`.

It is important to tests both success and failure paths! Remember than you can test for asserts with `EXPECT_DEATH` and there are similar tests for exceptions too. Browse the Google Test Primer for inspiration.

---

### **Stretch Ideas (If You Finish Early)**

- Extend `Config` with more fields and adjust your error handling.
- Add a function to save config back to disk and decide how it reports errors.
- Add a thin `ConfigLoader` type that holds the path and has a `reload()` member, and decide how it reports and stores the last error.
