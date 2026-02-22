#pragma once
#include "../config.hpp"
#include "../repositories/todo-repositories.cpp"
#include "../dto/todo-dto.cpp"
#include "../models/todo-model.cpp"
class TodoService : public TodoRepository
{
private:
    TodoRepository repo;

public:
    TodoService() : repo() {};
    ~TodoService() {};
    TodoModel createTodo(TodoCreateDto &payload)
    {
        return repo.createTodo(payload);
    };
    string paginateTodo()
    {
        auto result = repo.paginateTodo();
        return result;
    };
    TodoModel getTodo(string id)
    {
        return repo.getTodo(id);
    };
    vector<TodoModel> getAllTodo()
    {
        return repo.getAllTodo();
    };
    string updateTodo()
    {
        auto result = repo.updateTodo();
        return result;
    };
    string deleteTodo()
    {
        auto result = repo.deleteTodo();
        return result;
    };
};
