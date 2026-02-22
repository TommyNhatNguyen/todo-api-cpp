#include "config.hpp"
#include "routes/routes.cpp"
#include "db/sqlite-db.cpp"
using namespace std;
int main()
{
    // Initialize Database
    SqliteDatabase::instance().init();
    // Initialize Server
    Server svr;
    // Set default headers for all responses
    svr.set_default_headers({{"Cache-Control", "no-store"},
                             {"X-Content-Type-Options", "nosniff"}});
    // Register routes
    Routes::init(svr);
    // Listen on port
    svr.listen(SERVER_CONFIG::HOST, SERVER_CONFIG::PORT);
    return EXIT_SUCCESS;
}