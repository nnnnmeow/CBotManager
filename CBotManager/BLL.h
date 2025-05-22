#include "PyOperations.h"
#include <thread>
#include <map>

std::map<std::string, std::jthread> threads;

void StartPy(std::string Path)
{
    if (Path.empty()) return;
    threads.insert({Path, std::jthread([Path](std::stop_token stok)
    {
        PROCESS_INFORMATION pi = {0};

        std::atomic<bool> running = true;

        std::thread pyThread([&]
        {
            std::string cmd = "python \"" + Path + "\"";

            STARTUPINFOA si = {0};
            si.cb = sizeof(si);

            BOOL success = CreateProcessA(
                NULL,                   // No module name
                cmd.data(),             // Command line
                NULL,                   // Process handle not inheritable
                NULL,                   // Thread handle not inheritable
                FALSE,                  // Set handle inheritance to FALSE
                0,                      // No creation flags
                NULL,                   // Use parent's environment block
                NULL,                   // Use parent's starting directory 
                &si,                    // Pointer to STARTUPINFO structure
                &pi                     // Pointer to PROCESS_INFORMATION structure
            );
        });
        while (!stok.stop_requested() && running)
            std::this_thread::sleep_for(std::chrono::milliseconds(100));

        if (running)
        {
            TerminateProcess(pi.hProcess, 0);
            CloseHandle(pi.hThread);
            CloseHandle(pi.hProcess);
        }

        pyThread.join();
    })});
}

void StopPy(std::string Path)
{
    if (threads.find(Path)->second.request_stop())
    {
        std::cout << "thread stopped" << std::endl;
        threads.erase(Path);
    }
    else std::cout << "thread stop failed" << std::endl;
}