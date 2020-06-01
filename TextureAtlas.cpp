#include "TextureAtlas.h"

TextureAtlas::TextureAtlas(int atlasWidthPx, int atlasHeightPx, int amountOfImagesInWidth, int amountOfImagesInHeight)
{
	this->atlasWidthPx = atlasWidthPx;
	this->atlasHeightPx = atlasHeightPx;
	this->amountOfImagesInWidth = amountOfImagesInWidth;
	this->amountOfImagesInHeight = amountOfImagesInHeight;
}

TextureAtlas::~TextureAtlas()
{
}

void TextureAtlas::updateTextureCoords(int image_col, int image_row)
{
	this->textureCoords[0] = glm::vec2((double)(	image_col - 1)	/	amountOfImagesInWidth, (double)		image_row		/ amountOfImagesInHeight);
	this->textureCoords[1] = glm::vec2((double)(	image_col - 1)	/	amountOfImagesInWidth, (double)(	image_row - 1)	/ amountOfImagesInHeight);
	this->textureCoords[2] = glm::vec2((double)		image_col		/	amountOfImagesInWidth, (double)(	image_row - 1)	/ amountOfImagesInHeight);
	this->textureCoords[3] = glm::vec2((double)		image_col		/	amountOfImagesInWidth, (double)		image_row		/ amountOfImagesInHeight);
}
