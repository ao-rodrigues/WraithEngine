//
// IO.h
// WraithEngine
//
// Created by Andre Rodrigues on 08/12/2022.
//

#pragma once

#include <vector>
#include <string>
#include <fstream>

namespace Wraith::IO
{
    inline std::vector<char> ReadFile(const std::string& fileName)
    {
        std::ifstream file(fileName, std::ios::ate | std::ios::binary);
        if (!file.is_open())
        {
            throw std::runtime_error("Failed to open file!");
        }

        const size_t fileSize = static_cast<size_t>(file.tellg());
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);
        file.close();

        return buffer;
    }
}
