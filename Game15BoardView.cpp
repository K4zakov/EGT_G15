/*
 * Game15BoardView.cpp
 *
 *  Created on: 13.11.2012
 *      Author: jorio
 */

#include "Game15BoardView.h"
#include <stdio.h>
#include <iostream>
#include <sstream>


using namespace std;
		
#define CAPTION_NOT_WON				"Game 15 (SDL)"
#define CAPTION_GAME_OVER			"Game 15 (SDL)- Congratulations!"

Game15BoardView::Game15BoardView(Game15& _game) : game(_game)
{
	/* Initialize defaults, Video and Audio */
	if((SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)==-1)) {
		printf("Could not initialize SDL: %s.\n", SDL_GetError());
		state= Error;
	}
	state= Initialized;
	screen= SDL_SetVideoMode( 320, 240, 8, SDL_HWSURFACE|SDL_ANYFORMAT);
	if (!screen) {
		printf("Could not initialize SDL screen: %s.\n", SDL_GetError());
		state= Error;
	}
	SDL_SetAlpha( screen, SDL_SRCALPHA, 0);
	SDL_WM_SetCaption( CAPTION_NOT_WON, NULL);
	if(TTF_Init()) {
		printf("Could not initialize SDL TTF: %s.\n", SDL_GetError());
		state= Error;
	}
	font= TTF_OpenFont( "arial.ttf", 20);
	TTF_SetFontStyle( font, TTF_STYLE_BOLD);
}

Game15BoardView::~Game15BoardView()
{
	TTF_CloseFont(font);
	SDL_FreeSurface(screen);
	SDL_Quit();
}

void Game15BoardView::RedrawAll()const
{
	SDL_Color red= { 128, 0, 0, 0,}, white= { 255, 255, 255};
	SDL_Surface* text;
	stringstream sout;
	
	if (state==Win) {
		// clear screen
		SDL_FillRect( screen, NULL, SDL_MapRGB( screen->format, 0, 0, 0));
		//SDL_UpdateRect( screen, 0, 0, 0, 0);
		sout << "Solved in " << game.GetMoves() << " moves.";
		text= TTF_RenderText_Solid( font, sout.str().c_str(), white);
		SDL_Rect dest= { 160-text->w/2, 120, text->w, text->h}; // center horizontaly
		SDL_BlitSurface( text, NULL, screen, &dest);
	} else {
		// clear screen
		SDL_FillRect( screen, NULL, SDL_MapRGB( screen->format, 255, 255, 255));
		//SDL_UpdateRect( screen, 0, 0, 0, 0);
		for ( unsigned int y= 0; y < 4; ++y) {
			for ( unsigned int x= 0; x < 4; ++x) {
				const unsigned char& current= game._board[y][x];
				if(current) {
					sout << (unsigned int)current;
					text= TTF_RenderText_Solid( font, sout.str().c_str(), red);
					sout.str("");
					SDL_Rect dest= { 40+x*80-text->w/2, 30+y*60-text->h/2, text->w, text->h};
					SDL_BlitSurface( text, NULL, screen, &dest);
					//SDL_UpdateRects( screen, 1, &dest);
					SDL_FreeSurface(text);
				}
				lineColor( screen, x*80, 0, x*80, 240, 0xFF);
			}
			lineColor( screen, 0, y*60, 320, y*60, 0xFF);
		}
	}
	SDL_UpdateRect( screen, 0, 0, 0, 0);
}

void Game15BoardView::OnLButton( unsigned int x, unsigned int y)
{
	switch(state) {

	case Initialized:
		state= Game;

	case Game:
		if (game.Play( x/80, y/60)) {
			if (game.Finished()) {
				SDL_WM_SetCaption( CAPTION_GAME_OVER, NULL);
				state= Win;
			}
			RedrawAll();
		}
		break;

	case Win:
		game.Initialize();
		game.Randomize();
		SDL_WM_SetCaption( CAPTION_NOT_WON, NULL);
		state= Initialized;
		RedrawAll();
		break;

	case Error:
		cout << "Error!" << endl;
		break;
	}
}

void Game15BoardView::Run()
{
	if (state==Error) {
		return;
	}
	// wait for events
	SDL_Event event;
	while(SDL_WaitEvent(&event)) {
		switch(event.type) {

			case SDL_MOUSEBUTTONDOWN: {
				SDL_MouseButtonEvent mousebtn= event.button;
				if(mousebtn.type==SDL_MOUSEBUTTONDOWN &&
						mousebtn.button==SDL_BUTTON_LEFT &&
						mousebtn.state==SDL_PRESSED
				) {
					OnLButton( mousebtn.x, mousebtn.y);
				}
				break;
			}

			case SDL_KEYDOWN: {
				SDL_KeyboardEvent keybtn= event.key;
				if (keybtn.keysym.sym==SDLK_n) {
					game.Initialize();
					game.Randomize();
					SDL_WM_SetCaption( CAPTION_NOT_WON, NULL);
					state= Initialized;
					RedrawAll();
				}
				if (keybtn.keysym.sym==SDLK_a) {
					cout << "\"Game 15\" by  George Tabakov" << endl;
					cout << "2012, Distributed under GNU LGPL" << endl;
				}
				if (keybtn.keysym.sym==SDLK_ESCAPE || keybtn.keysym.sym==SDLK_q) {
					cout << "Good bye!" << endl;
					return;
				}
				break;
			}

			case SDL_QUIT:
				cout << "Good bye!" << endl;
				return;
		}
	}
}
