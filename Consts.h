#ifndef CONSTS_H
#define CONSTS_H

#include <string>

namespace Consts {
    inline const std::string FILE_OPEN_ERROR = "Failed to open file: ";
    inline const std::string FILE_READ_ERROR = "Read error: ";
    inline const std::string FILE_WRITE_ERROR = "Write error: ";
    inline const std::string FILE_MODE_ERROR = "Invalid mode: ";
    
    inline const std::string FILE_MODE_ERROR_WRITE_ONLY = "Write-only mode: cannot read.";
    inline const std::string FILE_MODE_ERROR_READ_ONLY = "Read-only mode: cannot write.";

    inline const std::string FILE_WRITE_FAILBIT = "Write failed (failbit set).";
    inline const std::string FILE_WRITE_BADBIT = "Write failed (badbit set).";

    inline const std::string FILE_READ_FAILBIT = "Read failed (failbit set).";
    inline const std::string FILE_READ_BADBIT = "Read failed (badbit set).";
}

#endif 
