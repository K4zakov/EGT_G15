/*
 * Game15BoardView.h
 *
 *  Created on: 13.11.2012
 *      Author: jorio
 */

#ifndef GAME15BOARDVIEW_H_
#	define GAME15BOARDVIEW_H_

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_gfxPrimitives.h"
#include "Game15.h"


class Game15BoardView
{
	Game15& game;
	SDL_Surface* screen;
	TTF_Font* font;
	enum { Error, Initialized, Game, Win} state;

public:
	Game15BoardView(Game15& _game);
	virtual ~Game15BoardView();

private:
	void OnLButton( unsigned int x, unsigned int y);

public:
	void RedrawAll()const;
	void Run();
};

#endif /* GAME15BOARDVIEW_H_ */
