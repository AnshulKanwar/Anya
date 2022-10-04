#include "anya.h"

int main(int argc, const char **argv)
{
    Anya app;
    app.get('/');
    app.listen(7878);
}