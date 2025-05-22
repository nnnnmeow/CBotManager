#pragma once
#include <Python.h>
#include <string>
#include <fstream>
#include <ctime>
#include <Windows.h>
#include <tlhelp32.h>
#include <comdef.h>
#include <iostream>


class LogFile
{
public:
    void SendLog(std::string msg)
    {
        ;
        std::ofstream out(_Path, std::ios_base::app);
        tm newtime;
        time_t now = time(0);
        localtime_s(&newtime,&now);
        out << newtime.tm_mday << "/" << 1+newtime.tm_mon << "/" << 1900+newtime.tm_year << " ";
        out << newtime.tm_hour << ":" << newtime.tm_min << ":" << newtime.tm_sec << " " << msg << std::endl;
    }
private:
    std::string _Path = "Log.txt";
};

class PyOperations
{
public:
    PyOperations(std::string path)
    {
        this->_Path = path;
    }
    
    int StartPyFile()
    {
        LogFile log;
        Py_Initialize();
        FILE* file;
        errno_t err = fopen_s(&file, _Path.c_str(), "r");
        if (file == NULL) {
            log.SendLog("Error: can't open file: " + _Path);
            Py_Finalize();
            return 1;
        }
        
        try {
            PyGILState_STATE gstate;
            gstate = PyGILState_Ensure();
            PyRun_SimpleFile(file, _Path.c_str());
            fclose(file);
            std::cout << "python closed";
            PyGILState_Release(gstate);
        } catch (...) {
            log.SendLog("Error running Python script");
        }
        return 0;
    }
private:
    std::string _Path;
};

