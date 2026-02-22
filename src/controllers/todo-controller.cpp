#pragma once
#include "../config.hpp"
#include "../services/todo-service.cpp"
#include "../dto/todo-dto.cpp"
#include "../exceptions/sqlite-exception.cpp"
#include <ctime>

class TodoController
{
private:
    TodoService service;

public:
    TodoController() : service() {};
    ~TodoController() {};
    void createTodo(const Request &req, Response &res)
    {
        try
        {
            json resultJson{};
            json reqBody = json::parse(req.body);

            TodoCreateDto payload{};
            TodoCreateDto::from_json(reqBody, payload);

            TodoModel result = service.createTodo(payload);
            TodoModel::to_json(result, resultJson);

            res.status = StatusCode::Created_201;
            res.set_content(resultJson.dump(), "application/json; charset=utf-8");
        }
        catch (const SqliteException &e)
        {
            json err{{"error", e.what()}, {"code", e.code}};
            res.status = e.isConstraintError() ? StatusCode::BadRequest_400 : StatusCode::InternalServerError_500;
            res.set_content(err.dump(), "application/json; charset=utf-8");
        }
    };
    void paginateTodo(const Request &req, Response &res)
    {
        auto result = service.paginateTodo();
        res.set_content(result, "application/json");
    };
    void getTodo(const Request &req, Response &res)
    {
        try
        {
            json resultJson{};
            string id = req.path_params.at("id");
            TodoModel result = service.getTodo(id);
            TodoModel::to_json(result, resultJson);
            res.status = StatusCode::OK_200;
            res.set_content(resultJson.dump(), "application/json; charset=utf-8");
        }
        catch (const SqliteException &e)
        {
            json err{{"error", e.what()}, {"code", e.code}};
            res.status = e.isConstraintError() ? StatusCode::BadRequest_400 : StatusCode::InternalServerError_500;
            res.set_content(err.dump(), "application/json; charset=utf-8");
        }
    };
    void getAllTodo(const Request &req, Response &res)
    {
        try
        {
            json resultJson = json::array();

            vector<TodoModel> result = service.getAllTodo();
            json jsonModel;
            for (int i = 0; i < result.size(); i++)
            {
                TodoModel::to_json(result[i], jsonModel);
                resultJson.push_back(jsonModel);
            }
            res.status = StatusCode::OK_200;
            res.set_content(resultJson.dump(), "application/json; charset=utf-8");
        }
        catch (const SqliteException &e)
        {
            json err{{"error", e.what()}, {"code", e.code}};
            res.status = e.isConstraintError() ? StatusCode::BadRequest_400 : StatusCode::InternalServerError_500;
            res.set_content(err.dump(), "application/json; charset=utf-8");
        }
    };
    void updateTodo(const Request &req, Response &res)
    {
        auto result = service.updateTodo();
        res.set_content(result, "application/json");
    };
    void deleteTodo(const Request &req, Response &res)
    {
        auto result = service.deleteTodo();
        res.set_content(result, "application/json");
    };
};
