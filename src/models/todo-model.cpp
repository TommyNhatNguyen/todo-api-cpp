#pragma once
#include "../config.hpp"

class TodoModel
{
public:
    static void from_json(const json &j, TodoModel &data)
    {
        try
        {
            data.id = j.value("id", NULL);
            data.title = j.value("title", "");
            data.description = j.value("description", "");
            data.created_at = j.value("created_at", "");
            data.updated_at = j.value("updated_at", "");
            data.user_id = j.value("user_id", NULL);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    static void to_json(const TodoModel &data, json &j)
    {
        try
        {
            j = json{
                {"id", data.id},
                {"title", data.title},
                {"description", data.description},
                {"created_at", data.created_at},
                {"updated_at", data.updated_at},
                {"user_id", data.user_id},
            };
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    };

private:
    int id;
    string title;
    string description;
    string created_at;
    string updated_at;
    int user_id;
};
