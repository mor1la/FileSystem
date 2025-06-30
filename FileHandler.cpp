#include "FileHandler.h"
#include "FileExceptions.h"

FileHandler::FileHandler (const std::filesystem::path& filePath, Mode mode) 
    : filePath(filePath), openMode(mode)
{
    std::ios_base::openmode stdOpenMode;
    switch (mode) 
    {
        case Mode::Read:
            stdOpenMode = std::ios::in;
            break;
        case Mode::Write:
            stdOpenMode  = std::ios::out;
            break;
        case Mode::ReadWrite:
            stdOpenMode = std::ios::in | std::ios::out;
            break;
    }
    
    stream = std::unique_ptr<std::fstream, StreamDeleter>(new std::fstream(
        filePath, stdOpenMode), StreamDeleter());
    
    checkFileIsOpen();       
}

void FileHandler::checkFileIsOpen() 
{
    if (!stream || !stream->is_open())
    {
        throw FileOpenException(filePath.string());
    }
}

void FileHandler::checkMode(Mode expected) const
{
    if (expected == Mode::Read && openMode == Mode::Write)
        throw FileModeException(Consts::FILE_MODE_ERROR_WRITE_ONLY);
    if (expected == Mode::Write && openMode == Mode::Read)
        throw FileModeException(Consts::FILE_MODE_ERROR_READ_ONLY);
}

void FileHandler::writeLine(const std::string& line)
{
    checkMode(Mode::Write);
    
    (*stream) << line << '\n';

    if (stream->fail())
    {
        throw FileWriteException(Consts::FILE_WRITE_FAILBIT);
    }

    if (stream->bad())
    {
        throw FileWriteException(Consts::FILE_WRITE_BADBIT);
    }
}


std::optional<std::string> FileHandler::readLine()
{
    checkMode(Mode::Read);

    std::string line;

    if (std::getline(*stream, line)) 
    {
        return line;
    }

    if (stream->eof()) 
    {
        return std::nullopt; 
    }

    if (stream->fail()) 
    {
        throw FileReadException(Consts::FILE_READ_FAILBIT);
    }

    if (stream->bad()) 
    {
        throw FileReadException(Consts::FILE_READ_BADBIT);
    }

    return std::nullopt;
}


void FileHandler::StreamDeleter::operator()(std::fstream* stream) const 
{
    if (stream)
    {
        if (stream->is_open()) 
        {
            stream->close();
        }
        delete stream;
    }
}