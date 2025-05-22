#include "UI.h"
#include <stdlib.h>

int KillPy()
{
    system("taskkill /IM python.exe /F");
    return 0;
}

int main(int argc, char* argv[])
{
    RenderUI();

    _onexit(KillPy);
    
    return 1;
}
