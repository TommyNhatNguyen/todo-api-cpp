#pragma once
#include "../config.hpp"

class TodoCreateDto
{
public:
    string title;
    string description;
    int user_id;

    static void from_json(const json &j, TodoCreateDto &data)
    {
        try
        {
            data.title = j.value("title", "");
            data.description = j.value("description", "");
            data.user_id = j.value("user_id", NULL);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    static void to_json(const TodoCreateDto &data, json &j)
    {
        try
        {
            j = json{
                {"title", data.title},
                {"description", data.description},
                {"user_id", data.user_id},
            };
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    };
};