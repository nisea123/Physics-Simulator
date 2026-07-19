#pragma once

#include "Font.h"

#include <string>
#include <unordered_map>

class FontManager {
public:
	std::unordered_map<std::string,Font> fontStorage;

	void AddFont(const std::string& name,const char* path);
	void RemoveFont(const std::string& name);
	Font& GetFont(const std::string& name);
};