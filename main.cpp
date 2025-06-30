#include <iostream>
#include "FileHandler.h"
#include "FileExceptions.h"

int main() {
    std::filesystem::path testFile = "test.txt";


    // Попытка открыть несуществующий файл в режиме чтения
    try {
        FileHandler badReader("nonexistent_file.txt", FileHandler::Mode::Read);
    } catch (const FileOpenException& e) {
        std::cerr << "Expected file open error: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Unexpected error opening nonexistent file: " << e.what() << "\n";
    }

    // Нарушение режима: попытка записи в read-only
    try {
        FileHandler reader(testFile, FileHandler::Mode::Read);
        reader.writeLine("This should trigger an exception");
    } catch (const FileModeException& e) {
        std::cerr << "Expected file mode error (write on read-only): " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Unexpected error during write on read-only file: " << e.what() << "\n";
    }

    // Нарушение режима: попытка чтения в write-only
    try {
        FileHandler writer(testFile, FileHandler::Mode::Write);
        auto line = writer.readLine();
    } catch (const FileModeException& e) {
        std::cerr << "Expected file mode error (read on write-only): " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Unexpected error during read on write-only file: " << e.what() << "\n";
    }

    // Запись в файл
    try {
        FileHandler writer(testFile, FileHandler::Mode::Write);
        writer.writeLine("First line");
        writer.writeLine("Second line");
        writer.writeLine("Third line");
        std::cout << "File successfully written.\n";
    } catch (const FileModeException& e) {
        std::cerr << "File mode error (read on write-only)" << e.what() << "\n";
    } catch (const FileWriteException& e) {
        std::cerr << "Error during writing: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error during writing: " << e.what() << "\n";
    }


    // Чтение в файл
    try {
        FileHandler reader(testFile, FileHandler::Mode::Read);
        std::optional<std::string> line;
        while ((line = reader.readLine())) {
            std::cout << "Read: " << *line << "\n";
        }
        std::cout << "Finished reading file.\n";
    } catch (const FileModeException& e) {
        std::cerr << "File mode error (write on read-only): " << e.what() << "\n";
    } catch (const FileReadException& e) {
        std::cerr << "Error during reading: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error during reading: " << e.what() << "\n";
    }

    // Файл был удален при открытии
    try {
        FileHandler reader(testFile, FileHandler::Mode::Read);

        if (std::filesystem::remove(testFile)) {
            std::cout << "File deleted from filesystem after opening.\n";
        } else {
            std::cerr << "Failed to delete the file.\n";
        }

        auto line = reader.readLine();
        if (line) {
            std::cout << "Read: " << *line << "\n";
        } else {
            std::cout << "End of file or no data.\n";
        }

    } catch (const FileReadException& e) {
        std::cerr << "Error during reading after file deletion: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Unexpected error after file deletion: " << e.what() << "\n";
    }


    return 0;
}
