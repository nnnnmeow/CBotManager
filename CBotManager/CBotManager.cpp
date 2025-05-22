#include "UI.h"

int main(int argc, char* argv[])
{
    Py_Initialize();
    RenderUI();
    Py_Finalize();
    return 1;
}
