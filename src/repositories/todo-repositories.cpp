#pragma once
#include "../config.hpp"
#include "../db/sqlite-db.cpp"
#include "../dto/todo-dto.cpp"
#include "../models/todo-model.cpp"
#include "../exceptions/sqlite-exception.cpp"

class TodoRepository
{
private:
    SqliteDatabase &sqlite_db;

public:
    TodoRepository() : sqlite_db(SqliteDatabase::instance())
    {
        cerr << "Hello Repository Initialized" << endl;
        cerr << "Datbase repo address: " << sqlite_db.get() << endl;
    };
    ~TodoRepository() {};

    TodoModel createTodo(TodoCreateDto &payload)
    {
        // ---- Begin: Result
        TodoModel result;
        // ---- Setup db pointers
        sqlite3 *db = sqlite_db.get();
        sqlite3_stmt *stmt = nullptr;
        // ---- Setup sql
        const char *sql = "INSERT INTO todo(title, description) VALUES(?, ?) RETURNING *";
        if (payload.user_id != NULL)
        {
            sql = "INSERT INTO todo(title, description, user_id) VALUES(?, ?, ?) RETURNING *";
        }
        // ---- Compile sql
        int prepare_result = sqlite3_prepare(db, sql, -1, &stmt, NULL);
        if (prepare_result != SQLITE_OK)
        {
            throw SqliteException(prepare_result, sqlite3_errmsg(db));
        }
        sqlite3_bind_text(stmt, 1, payload.title.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, payload.description.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 3, payload.user_id);
        // ---- Evaluate compiled sql
        int step_result = sqlite3_step(stmt);
        while (step_result == SQLITE_ROW)
        {
            json j;
            j["id"] = sqlite3_column_int(stmt, 0);
            j["title"] = string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));
            j["description"] = string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));
            j["created_at"] = string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3)));
            j["updated_at"] = string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4)));
            j["user_id"] = sqlite3_column_int(stmt, 5);
            TodoModel::from_json(j, result);
            step_result = sqlite3_step(stmt);
        }
        // ---- Destroy prepare statement
        sqlite3_finalize(stmt);
        if (step_result != SQLITE_DONE)
        {
            throw SqliteException(step_result, sqlite3_errmsg(db));
        }
        // ----- End: Return result
        return result;
    };

    vector<TodoModel> getAllTodo()
    {
        vector<TodoModel> result;

        sqlite3 *db = sqlite_db.get();
        sqlite3_stmt *stmt = nullptr;

        const char *selectSql = "SELECT * FROM todo;";
        int prepare_result = sqlite3_prepare(db, selectSql, -1, &stmt, nullptr);
        if (prepare_result != SQLITE_OK)
        {
            throw SqliteException(prepare_result, sqlite3_errmsg(db));
        }

        int step_result = sqlite3_step(stmt);
        while (step_result == SQLITE_ROW)
        {
            json j;
            j["id"] = sqlite3_column_int(stmt, 0);
            j["title"] = string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));
            j["description"] = string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));
            j["created_at"] = string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3)));
            j["updated_at"] = string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4)));
            j["user_id"] = sqlite3_column_int(stmt, 5);
            TodoModel item;
            TodoModel::from_json(j, item);
            result.push_back(item);
            step_result = sqlite3_step(stmt);
        }

        sqlite3_finalize(stmt);
        if (step_result != SQLITE_DONE)
        {
            throw SqliteException(step_result, sqlite3_errmsg(db));
        }

        return result;
    };

    TodoModel getTodo(string id)
    {
        TodoModel result;

        sqlite3 *db = sqlite_db.get();
        sqlite3_stmt *stmt = nullptr;

        const char *selectSql = "SELECT * FROM todo WHERE id = ?;";
        int prepare_result = sqlite3_prepare(db, selectSql, -1, &stmt, nullptr);
        if (prepare_result != SQLITE_OK)
        {
            throw SqliteException(prepare_result, sqlite3_errmsg(db));
        }
        sqlite3_bind_text(stmt, 1, id.c_str(), -1, SQLITE_TRANSIENT);

        int step_result = sqlite3_step(stmt);
        if (step_result == SQLITE_DONE)
        {
            throw SqliteException(step_result, sqlite3_errmsg(db));
        }
        while (step_result == SQLITE_ROW)
        {
            json j;
            j["id"] = sqlite3_column_int(stmt, 0);
            j["title"] = string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));
            j["description"] = string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));
            j["created_at"] = string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3)));
            j["updated_at"] = string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4)));
            j["user_id"] = sqlite3_column_int(stmt, 5);
            TodoModel::from_json(j, result);
            step_result = sqlite3_step(stmt);
        }

        sqlite3_finalize(stmt);
        if (step_result != SQLITE_DONE)
        {
            throw SqliteException(step_result, sqlite3_errmsg(db));
        }

        return result;
    };

    string paginateTodo()
    {
        return "getAllTodo";
    };
    string updateTodo()
    {
        return "updateTodo";
    };
    string deleteTodo()
    {
        return "deleteTodo";
    };
};