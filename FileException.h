#ifndef FILEEXCEPTION_H
#define FILEEXCEPTION_H
#include <stdexcept>


class FileException : public std::runtime_error {
public:
    explicit FileException(const std::string& message) : std::runtime_error(message) {}; 
}; 

class FileOpenException : public FileException {
    public:
        explicit FileOpenException(const std::string& path)
            : FileException("Failed to open file: " + path) {}
    };
    
class FileReadException : public FileException {
public:
    explicit FileReadException(const std::string& msg)
        : FileException("Read error: " + msg) {}
};

class FileWriteException : public FileException {
public:
    explicit FileWriteException(const std::string& msg)
        : FileException("Write error: " + msg) {}
};

class FileModeException : public FileException {
public:
    explicit FileModeException(const std::string& msg)
        : FileException("Invalid mode: " + msg) {}
};




#endif