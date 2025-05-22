#pragma once
#include <vector>
#include <string>

class Config
{
public:
    Config(): Name({""}), Path({""}) {}
    std::vector<std::string> Name;
    std::vector<std::string> Path;
    static Config* Instance();

private:
    static Config* _Instance;
};
