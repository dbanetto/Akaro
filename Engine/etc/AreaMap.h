/*
 * AreaMap.h
 *
 *  Created on: 20/09/2013
 *      Author: drb
 */

#ifndef AREAMAP_H_
#define AREAMAP_H_

#include "../graphics/drawable.h"
#include <vector>



namespace etc
{

	class AreaMap
	{
		public:
			AreaMap();
			AreaMap( SDL_Rect Area );
			AreaMap( AreaMap* Parent , SDL_Rect Area );
			virtual ~AreaMap();

			void insert( graphics::drawable* sp );

			void getSpritesFromArea ( SDL_Rect Area , std::vector<graphics::drawable*>* out );

			bool remove ( graphics::drawable* sp );

			void update ( graphics::drawable* sp );

			SDL_Rect getArea();

			void clear();

			int count();
			int getDepth();
		protected:
			SDL_Rect area;
			std::vector<graphics::drawable*>  sprites;
			std::vector<AreaMap> children;
			AreaMap* parent;
		private:
			void split();
			int depth;
	};

} /* etc namespace */

#endif /* AREAMAP_H_ */
