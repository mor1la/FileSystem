#ifndef FILEEXCEPTION_H
#define FILEEXCEPTION_H
#include <stdexcept>
#include "Consts.h"

class FileException : public std::runtime_error {
public:
    explicit FileException(const std::string& message) : std::runtime_error(message) {}
};

class FileOpenException : public FileException {
public:
    explicit FileOpenException(const std::string& path)
        : FileException(Consts::FILE_OPEN_ERROR + path) {}
};

class FileReadException : public FileException {
public:
    explicit FileReadException(const std::string& msg)
        : FileException(Consts::FILE_READ_ERROR + msg) {}
};

class FileWriteException : public FileException {
public:
    explicit FileWriteException(const std::string& msg)
        : FileException(Consts::FILE_WRITE_ERROR + msg) {}
};

class FileModeException : public FileException {
public:
    explicit FileModeException(const std::string& msg)
        : FileException(Consts::FILE_MODE_ERROR + msg) {}
};


#endif