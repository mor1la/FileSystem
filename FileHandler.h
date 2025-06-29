#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <stdexcept>
#include <filesystem>

class FileHandler
{
    
public:
    enum class Mode {
        Read,
        Write,
        ReadWrite
    };

    FileHandler(const std::filesystem::path& filePath, Mode mode);

    void writeLine(const std::string& line);

    std::string readLine();

private:
    struct StreamDeleter
    {
        void operator()(std::fstream* stream) const;
    }; 

    void checkFileIsOpen();

    void checkMode(Mode expected) const;

    // Запрет копирования
    FileHandler(const FileHandler&) = delete;
    FileHandler& operator=(const FileHandler&) = delete;

    FileHandler(FileHandler&&) = default;
    FileHandler& operator=(FileHandler&&) = default;

    std::unique_ptr<std::fstream, StreamDeleter> stream;
    std::filesystem::path filePath;
    Mode openMode;  
};


#endif
