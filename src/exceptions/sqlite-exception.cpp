#pragma once
#include <stdexcept>
#include <string>
#include "../libs/sqlite/sqlite3.h"

class SqliteException : public std::runtime_error
{
public:
    const int code;

    SqliteException(int sqliteCode, const char *sqliteMessage)
        : std::runtime_error(buildMessage(sqliteCode, sqliteMessage)),
          code(sqliteCode)
    {
    }

    /** True for constraint violations (e.g. foreign key, unique) — typically 400. */
    bool isConstraintError() const
    {
        return code == SQLITE_CONSTRAINT || code == SQLITE_CONSTRAINT_FOREIGNKEY ||
               code == SQLITE_CONSTRAINT_UNIQUE || code == SQLITE_CONSTRAINT_NOTNULL;
    }

private:
    static std::string buildMessage(int sqliteCode, const char *sqliteMessage)
    {
        std::string msg = "[SQLite] code=" + std::to_string(sqliteCode);
        if (sqliteMessage && *sqliteMessage)
        {
            msg += " ";
            msg += sqliteMessage;
        }
        return msg;
    }
};
