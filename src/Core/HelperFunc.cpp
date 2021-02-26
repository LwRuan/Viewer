#include "HelperFunc.h"

std::vector<char> HF::readBinaryFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("failed to open file!");
    }

    size_t fileSize = (size_t) file.tellg();
    std::vector<char> buffer(fileSize);
    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();
    return buffer;
}

Matrix4f HF::lookAt(Vector3f eyePos, Vector3f centerPos, Vector3f upAxis){
    Vector3f z = (eyePos-centerPos).normalized();
    Vector3f x = upAxis.cross(z).normalized();
    Vector3f y = z.cross(x).normalized();
    Matrix4f Minv = Matrix4f::Identity();
    Matrix4f Tr   = Matrix4f::Identity();
    Tr.block<3,1>(0,3) = -eyePos;
    Minv.block<1,3>(0,0) = x.transpose();
    Minv.block<1,3>(1,0) = y.transpose();
    Minv.block<1,3>(2,0) = z.transpose();
    return Minv*Tr;
}

Matrix4f HF::perspective(float fovy, float aspect, float zNear, float zFar){
    float tanHalfFovy = std::tan(fovy/2);
    Matrix4f res = Matrix4f::Zero();
    res(0,0) = 1.0 / (aspect * tanHalfFovy);
    res(1,1) = 1.0 / (tanHalfFovy);
    res(2,2) = - (zFar + zNear) / (zFar - zNear);
    res(3,2) = - 1.0;
    res(2,3) = - (2.0 * zFar * zNear) / (zFar - zNear);
    return res;
}