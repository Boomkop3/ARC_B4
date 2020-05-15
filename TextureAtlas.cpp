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
	this->textureCoords[0] = glm::vec2(image_col * (1. / this->amountOfImagesInWidth) * (1. / this->amountOfImagesInWidth), image_row * (1. / this->amountOfImagesInHeight) * .5); // i.p.v. *.5 bij de start params 1./amountOfImagesInWidth/Height pakken.
	this->textureCoords[1] = glm::vec2(image_col * (1. / this->amountOfImagesInWidth) * (1. / this->amountOfImagesInWidth), image_row * (1. / this->amountOfImagesInHeight));
	this->textureCoords[2] = glm::vec2(image_col * (1. / this->amountOfImagesInWidth), image_row * (1. / this->amountOfImagesInHeight));
	this->textureCoords[3] = glm::vec2(image_col * (1. / this->amountOfImagesInWidth), image_row * (1. / this->amountOfImagesInHeight) * .5);
}
