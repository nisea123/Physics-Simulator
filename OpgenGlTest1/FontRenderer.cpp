#include <iostream>
#include "TextRenderer.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include <string>
#include <map>

Font::Font(const char* txt)
{
	FT_Library ft;

	if (FT_Init_FreeType(&ft)) {
		std::cout << "Failed to initialize FreeType" << std::endl;
	}

	FT_Face face;

	if (FT_New_Face(ft, txt, 0, &face)) {
		std::cout << "Failed to load font" << std::endl;
	}

	FT_Set_Pixel_Sizes(face, 0, 48);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	int atlasWidth = 1024;
	int atlasHeight = 1024;

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, atlasWidth, atlasHeight, 0, GL_RED, GL_UNSIGNED_BYTE, nullptr);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	int x = 0;
	int y = 0;
	int rowHeight = 0;

	for (unsigned char c = 32; c < 128; c++) {
		FT_Load_Char(face, c, FT_LOAD_RENDER);

		FT_Bitmap bitmap = face->glyph->bitmap;

		if (x + bitmap.width > atlasWidth) {
			x = 0;
			y += rowHeight + 1;
			rowHeight = 0;
		}

		glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, bitmap.width, bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, bitmap.buffer);

		rowHeight = std::max(rowHeight, (int)bitmap.rows);

		Character chr;
		chr.UV1 = { (float)x / atlasWidth,(float)(y + bitmap.rows) / atlasHeight };
		chr.UV2 = { (float)(x + bitmap.width) / atlasWidth,(float)y / atlasHeight };
		

		chr.Size = { (signed)bitmap.width,(signed)bitmap.rows };
		chr.Bearing = { face->glyph->bitmap_left,face->glyph->bitmap_top };
		chr.Advance = face->glyph->advance.x;
		lineHeight = face->size->metrics.height >> 6;

		Characters[c] = chr;

		x += bitmap.width + 1;
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}