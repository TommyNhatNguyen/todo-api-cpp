#pragma once
#include "iostream"
#include "filesystem"
#include "libs/cpp-httplib/httplib.h"
#include "libs/single_include/nlohmann/json.hpp"
#include "fstream"

using namespace std;
using namespace httplib;
using json = nlohmann::json;

namespace fs = std::filesystem;

inline const fs::path BASED_URL = fs::current_path();

namespace DB_CONFIG
{
    inline const fs::path DATABASE_NAME = fs::path("db/todo.db");
    inline const fs::path DATABASE_URI = BASED_URL / DATABASE_NAME;
};

namespace SERVER_CONFIG
{
    inline const string HOST = "0.0.0.0";
    inline const size_t PORT = 8080;
};
