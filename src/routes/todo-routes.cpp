#pragma once
#include "../config.hpp"
#include "../controllers/todo-controller.cpp"

class TodoRoutes
{
private:
    Server &svr;
    TodoController controller;

    void createTodo()
    {
        svr.Post("/todo", [this](const Request &req, Response &res)
                 { controller.createTodo(req, res); });
    };
    void paginateTodo()
    {
        svr.Get("/todos", [this](const Request &req, Response &res)
                { controller.paginateTodo(req, res); });
    };
    void getTodo()
    {
        svr.Get("/todo/:id", [this](const Request &req, Response &res)
                { controller.getTodo(req, res); });
    };
    void getAllTodo()
    {
        svr.Get("/todos-all", [this](const Request &req, Response &res)
                { controller.getAllTodo(req, res); });
    };
    void updateTodo()
    {
        svr.Patch("/todo", [this](const Request &req, Response &res)
                  { controller.updateTodo(req, res); });
    };
    void deleteTodo()
    {
        svr.Delete("/todo", [this](const Request &req, Response &res)
                   { controller.deleteTodo(req, res); });
    };

public:
    TodoRoutes(Server &svr) : controller(), svr(svr) {};
    ~TodoRoutes() {};
    void init()
    {
        createTodo();
        paginateTodo();
        getTodo();
        getAllTodo();
        updateTodo();
        deleteTodo();
    };
};
