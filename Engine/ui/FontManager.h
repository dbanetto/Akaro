#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include "Font.h"

#include <string>
#include <map>

namespace ui
{

	class FontManager
	{
		public:
			FontManager();
			virtual ~FontManager();

			bool exists(std::string name);
			bool load(std::string name, std::string fontPath );
			Font* get(std::string name);

			void unload (std::string name);
			void unloadAll();
		protected:
		private:
			std::map<std::string , Font*> fonts;
	};

}
#endif // FONTMANAGER_H
