#pragma once
#include "../config.hpp"
#include "../libs/sqlite/sqlite3.h"

class SqliteDatabase
{
public:
    // Direct initializer only
    explicit SqliteDatabase()
    {
        cerr << "SqliteDatabase Initialized" << endl;
    };
    ~SqliteDatabase()
    {
        closeConnection();
    };
    void init()
    {
        int resultConnection = openConnection();
        if (resultConnection != SQLITE_OK)
        {
            cerr << "Database Initialized!";
        }
    };
    int openConnection()
    {
        int resultConnection = sqlite3_open(DB_CONFIG::DATABASE_URI.c_str(), &this->db);
        if (resultConnection != SQLITE_OK)
        {
            cerr << "Failed to connect to database: ";
        }
        else
        {
            cerr << "Database connected!" << endl;
            initDatabase();
        }

        return resultConnection;
    };
    int closeConnection()
    {
        int resultConnection = sqlite3_close(this->db);
        if (resultConnection != SQLITE_OK)
        {
            cerr << "Failed to disconnect database: ";
        }
        cerr << "Database disconnected!";
        return resultConnection;
    };
    static SqliteDatabase &instance()
    {
        static SqliteDatabase instance;
        return instance;
    }
    sqlite3 *get() { return this->db; };
    // Remove copy initializer
    SqliteDatabase(const SqliteDatabase &) = delete;
    SqliteDatabase &operator=(const SqliteDatabase &) = delete;

private:
    sqlite3 *db;
    void initDatabase()
    {
        ifstream myfile;
        string line;
        string sql;
        myfile.open("db/init.sql");
        if (myfile.is_open())
        {
            while (getline(myfile, line))
            {
                sql.append(line);
                if (!line.empty())
                    sql.append(" ");
            }
            myfile.close();
        }
        char *errMsg = nullptr;
        int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
        cerr << sql.c_str() << endl;
        if (rc != SQLITE_OK)
        {
            cerr << "SQL exec error: " << rc << " - " << (errMsg ? errMsg : "") << endl;
            if (errMsg)
                sqlite3_free(errMsg);
        }
        else
        {
            cerr << "Init SQL executed successfully." << endl;
        }
    }
};