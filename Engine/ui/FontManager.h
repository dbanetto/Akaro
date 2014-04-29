#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include "Font.h"

#include <string>
#include <map>
#include <vector>
namespace ui
{

	class FontManager
	{
		public:
			FontManager();
			virtual ~FontManager();

			bool exists( std::string name );
			bool load( std::string name, std::string fontPath );
			Font* get( std::string name , int size);

			void unloadAll ( );
			void unload ( std::string name );

		protected:
		private:
			std::map<std::string , std::string> fonts;
			std::map<std::string , std::vector<Font*>> created_fonts;
	};

}
#endif // FONTMANAGER_H
