#pragma once
#include <Python.h>
#include <string>
#include <fstream>
#include <ctime>
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

