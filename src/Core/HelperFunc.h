#pragma once

#include "Types.h"

#include <fstream>
#include <vector>

namespace HF
{
    std::vector<char> readBinaryFile(const std::string& filename);
    Matrix4f lookAt(Vector3f eyePos, Vector3f centerPos, Vector3f upAxis);
    Matrix4f perspective(float fovy, float aspect, float zNear, float zFar);
};