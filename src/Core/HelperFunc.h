#pragma once

#include <fstream>
#include <vector>

namespace HF
{
    std::vector<char> readBinaryFile(const std::string& filename);
};