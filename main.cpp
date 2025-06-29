#include <iostream>
#include "FileHandler.h"
#include "FileException.h"

int main() {
    std::filesystem::path testFile = "test.txt";
    std::filesystem::path testFile1 = "test1.txt";

    // Попытка открыть несуществующий файл в режиме чтения
    try {
        FileHandler reader("nonexistent.txt", FileHandler::Mode::Read);
    } catch (const FileOpenException& e) {
        std::cerr << "[Error] " << e.what() << "\n";
    }

    // Нарушение режима: попытка записи в read-only
    try {
        FileHandler reader(testFile, FileHandler::Mode::Read);
        reader.writeLine("This should fail");
    } catch (const FileModeException& e) {
        std::cerr << "[Error] Mode violation (write in read-only): " << e.what() << "\n";
    }

    // Нарушение режима: попытка чтения в write-only
    try {
        FileHandler writer(testFile, FileHandler::Mode::Write);
        std::string line = writer.readLine();
        (void)line; // подавим unused warning
    } catch (const FileModeException& e) {
        std::cerr << "[Error] Mode violation (read in write-only): " << e.what() << "\n";
    }

    // Запись в файл
    try {
        FileHandler writer(testFile, FileHandler::Mode::Write);
        writer.writeLine("Line 1");
        writer.writeLine("Line 2");
        std::cout << "[OK] Lines written to file.\n";
    } catch (const FileException& e) {
        std::cerr << "[Error] Writing: " << e.what() << "\n";
    }

    // Чтение из файла
    try {
        FileHandler reader(testFile, FileHandler::Mode::Read);
        while (true) {
            std::string line = reader.readLine();    
            std::cout << "Read: " << line << "\n";
        }
    } catch (const std::runtime_error& e) {
        std::cerr << "[Info] Reading finished: " << e.what() << "\n";
    } catch (const FileException& e) {
        std::cerr << "[Error] Reading: " << e.what() << "\n";
    }


    return 0;
}
