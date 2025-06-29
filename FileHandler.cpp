#include "FileHandler.h"
#include "FileException.h"

FileHandler::FileHandler (const std::filesystem::path& filePath, Mode mode) 
    : filePath(filePath), openMode(mode)
{
    std::ios_base::openmode openMode;
    switch (mode) 
    {
        case Mode::Read:
            openMode = std::ios::in;
            break;
        case Mode::Write:
            openMode  = std::ios::out;
            break;
        case Mode::ReadWrite:
            openMode = std::ios::in | std::ios::out;
            break;
    }
    
    stream = std::unique_ptr<std::fstream, StreamDeleter>(new std::fstream(
        filePath, openMode), StreamDeleter());

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
        throw FileModeException("Write-only mode: cannot read.");
    if (expected == Mode::Write && openMode == Mode::Read)
        throw FileModeException("Read-only mode: cannot write.");
}

void FileHandler::writeLine(const std::string& line)
{
    checkMode(Mode::Write);
    (*stream) << line << "\n";
    if (!(*stream))
    {
        throw FileWriteException("Unable to write line to file.");
    }
}

std::string FileHandler::readLine()
{
    checkMode(Mode::Read);
    
    std::string line;
    if (!std::getline(*stream, line)) 
    {
        if (stream->eof()) 
        {
            throw std::runtime_error("End of file reached");
        } else 
        {
            throw std::runtime_error("Failed to read from file");
        }
    }
    return line;
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