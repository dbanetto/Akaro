#include "FontManager.h"

#include <iostream>

using namespace ui;

FontManager::FontManager()
{

}

FontManager::~FontManager()
{
	unloadAll();
}

void FontManager::unloadAll()
{
	for (auto& obj : this->fonts)
    {
        if (obj.second->isLoaded())
        {
            obj.second->unload();
        }
        delete obj.second;
    }
    this->fonts.clear();
}

void FontManager::unload (std::string name)
{
	if (this->exists(name))
	{
		this->fonts[name]->unload();
		this->fonts.erase(name);
	}
}

Font* FontManager::get(std::string name)
{
	if (this->exists(name))
	{
		return this->fonts[name];
	}
}

bool FontManager::exists(std::string name)
{
	return (this->fonts.find(name) != this->fonts.end());
}

bool FontManager::load (std::string name, std::string fontPath )
{
	if (!this->exists(name))
	{
		Font* ft = new Font();
        bool out = ft->load(fontPath);

        if (out) {
			this->fonts[name] = ft;
        }

        return out;
	} else {
		std::cout << "WARNING The font " << name << " (" << fontPath << ") failed to load." << std::endl;
		std::cout << name << " already exists" << std::endl;
		return false;
	}
}
