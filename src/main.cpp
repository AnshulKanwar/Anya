#include "anya.h"

#include <spdlog/spdlog.h>

int main(int argc, const char **argv)
{
    spdlog::info("Starting App");

    Anya app;
    app.get('/');
    app.listen(7878);
}