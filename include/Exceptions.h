#pragma once
#include <stdexcept>
#include <string>

class IndexOutOfRangeException : public std::out_of_range {
public:
    explicit IndexOutOfRangeException(const std::string& msg)
        : std::out_of_range("IndexOutOfRange: " + msg) {}
};

class FileOpenException : public std::runtime_error {
public:
    explicit FileOpenException(const std::string& filename)
        : std::runtime_error("FileOpen: не удалось открыть файл '" + filename + "'") {}
};

class InvalidArgumentException : public std::invalid_argument {
public:
    explicit InvalidArgumentException(const std::string& msg)
        : std::invalid_argument("InvalidArgument: " + msg) {}
};

class EmptyContainerException : public std::runtime_error {
public:
    explicit EmptyContainerException(const std::string& msg)
        : std::runtime_error("EmptyContainer: " + msg) {}
};