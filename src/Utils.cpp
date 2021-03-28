#include "Utils.hpp"
#include <fstream>
#include <sys/types.h>

Utils::CMD Utils::getCMD(const std::string &command)
{
    char buffer[2048];
    CMD ret;

    FILE *pipe = popen(command.c_str(), "r");
    if (!pipe)
        throw Utils::exception("Pipe error");
    while (!feof(pipe)) {
        if (fgets(buffer, 2048, pipe) != NULL)
            ret.output += buffer;
    }
    ret.returnValue = pclose(pipe);
    return ret;
}

std::string Utils::getFile(const std::string &path)
{
    std::string file_content;
    std::ifstream file_stream(path);

    if (!file_stream.is_open())
        throw Utils::exception("File [" + path + "] does not exist or is not readable");
    std::getline(file_stream, file_content, '\0');
    return file_content;
}

std::vector<std::string> Utils::stringToVector(const std::string &str, char separator, bool pushEmptyStrings)
{
    std::vector<std::string> array;
    std::string temp;
    size_t len = str.size();

    for (size_t i = 0; i < len; i++) {
        if (str[i] == separator) {
            if (pushEmptyStrings || !temp.empty()) {
                array.push_back(temp);
                temp.clear();
            }
        }
        else
            temp.push_back(str[i]);
    }
    if (pushEmptyStrings || !temp.empty())
        array.push_back(temp);
    return array;
}