#include "PyOperations.h"
#include <thread>


std::jthread tr;

void StartPy(std::string Path)
{
    if (Path.empty()) return;
    tr = std::jthread([Path](std::stop_token stok)
    {
        PyOperations *py = new PyOperations(Path);
            if (!stok.stop_requested())
            {
                    py->StartPyFile();
            }
    });
}

void StopPy()
{
    if (tr.request_stop()) std::cout << "thread stopped" << std::endl;
    else std::cout << "thread stop failed" << std::endl;
}