#pragma once
#include "Utils.h"

//const char* readFile(const std::string& filePath) {
//	std::ifstream file(filePath, std::ios::binary | std::ios::ate);  // Open in binary mode, set position at the end
//
//	if (!file.is_open()) {
//		std::cerr << "Error: Could not open file." << std::endl;
//		return nullptr;
//	}
//
//	std::streamsize fileSize = file.tellg();
//	file.seekg(0, std::ios::beg);  // Go back to the start of the file
//
//	// Use a vector to store the file contents with a null terminator
//	std::vector<char> buffer(fileSize + 1);
//	if (!file.read(buffer.data(), fileSize)) {
//		std::cerr << "Error: Could not read file." << std::endl;
//		return nullptr;
//	}
//
//	buffer[fileSize] = '\0';  // Null-terminate the buffer
//
//	// Allocate new memory for the result and copy the buffer contents
//	char* result = new char[buffer.size()];
//	std::copy(buffer.begin(), buffer.end(), result);
//
//	file.close();
//	return result;
//}

std::string readFile(const std::string& filePath) {
	std::ifstream file(filePath, std::ios::binary | std::ios::ate);

	if (!file.is_open()) {
		std::cerr << "Error: Could not open file." << std::endl;
		return "";
	}

	std::streamsize fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	std::string buffer(fileSize, '\0');
	if (!file.read(&buffer[0], fileSize)) {
		std::cerr << "Error: Could not read file." << std::endl;
		return "";
	}

	return buffer;
}
