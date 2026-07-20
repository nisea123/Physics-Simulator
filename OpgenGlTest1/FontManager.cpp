#include "FontManager.h"
#include "Font.h"*

#include <iostream>

void FontManager::AddFont(const std::string& name, const char* path) {
	if (!fontStorage.contains(name)) {
		fontStorage.emplace(name,Font(path));
	}
	else {
		std::cout << "Font named " << name << " has already been added to the fontStorage" << std::endl;
	}
}

void FontManager::RemoveFont(const std::string& name) {
	if (fontStorage.contains(name) ) {
		fontStorage.erase(name);
	}
	else {
		std::cout << "Font named " << name << " couldn't be found and removed" << std::endl;
	}
}

Font& FontManager::GetFont(const std::string& name) {
	if (fontStorage.contains(name)) {
		return fontStorage.at(name);
	}
	else {
		std::cout << "Font named " << name << " couldn't be found" << std::endl;
		std::cout << "Returning the default font" << std::endl;
		return fontStorage.at("Default");
	}
}

Font& FontManager::GetDefaultFont() {
	if (fontStorage.contains("Default")) {
		return fontStorage.at("Default");
	}
}