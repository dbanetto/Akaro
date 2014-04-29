#ifndef WORLDSTATE_H
#define WORLDSTATE_H

#include "Engine/states/GameState.h"
#include "Engine/states/GameStateManager.h"
#include "Engine/GameWindow.h"
#include "Engine/graphics/Sprite.h"
#include "Engine/map/Map.h"

#include "Engine/ui/Label.h"

class WorldState : public GameState
{
	public:
		/** Default constructor */
		WorldState( GameStateManager* Manager, GameWindow* gamewindow , Content* content );
		/** Default destructor */
		virtual ~WorldState();

		//Each frame
		void render ( const Ldouble& delta, SDL_Renderer* renderer , etc::Camera& camera );
		void update ( const Ldouble& delta );
		void event ( SDL_Event e , const Ldouble& delta );

		//Inital un/Load Assests
		void load   ();
		void unload ();
	protected:
	private:
		GameStateManager* manager;
		Content* content;
		GameWindow* window;

		map::Map* cur_map;
		ui::Label fps;
		bool is_loaded;
};

#endif // WORLDSTATE_H
