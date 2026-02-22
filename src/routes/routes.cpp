#pragma once
#include "../config.hpp"
#include "todo-routes.cpp"
class Routes
{
public:
    static void init(Server &svr)
    {
        static TodoRoutes todo_routes(svr);
        todo_routes.init();
    }
};