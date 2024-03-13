/*
 * Game15.cpp
 *
 *  Created on: 13.11.2012
 *      Author: jorio
 */

#include "Game15.h"
#include <stdlib.h>
#include <time.h>


using namespace std;

/**
 * Creates solved puzzle and if requested shakes it
 * @param randomize should the puzzle be randomized at it creation
 */
Game15::Game15(bool randomize)
{
	Initialize();
	if (randomize) {
		Randomize();
	}
	_moves= 0;
}

Game15::~Game15()
{
}

/**
 *  Fills board with sequence of numbers
 */
void Game15::Initialize()
{
	for ( unsigned int i= 0; i<16; ++i) {
		_board[i>>2][i%4]= (unsigned char) (i+1)%16;
	}
}

/**
 * Randomly shakes ordered board
 */
void Game15::Randomize()
{
	srandom(time(NULL));
	for ( unsigned int i= 0; i < 500; ++i) {
		Play( random()%4, random()%4);
	}
	_moves= 0;
}

/**
 * Test if neighbour is zero (empty) and if it is swaps both values
 */
bool Game15::TestAndSwap( unsigned char& current, unsigned char& neighbour)
{
	if (!neighbour) { // is zero
		neighbour= current;
		current= 0;
		++_moves;
		return true;
	}
	return false;
}

/**
 * Check if there is free tile just next to current and moves current tile
 *
 * @param x column index of current tile in matrix 
 * @param y row index of current tile in matrix 
 * @return true if there was move and false if can't move
 */
bool Game15::Play( const unsigned x, const unsigned y)
{
	unsigned _x, _y= y;
	unsigned char& current= _board[y][x];
	// left
	if (x) { // > 0
		_x= x-1;
		if (TestAndSwap( current, _board[_y][_x])) {
			return true;
		}
	}
	// right
	if (x!=3) {
		_x= x+1;
		if (TestAndSwap( current, _board[_y][_x])) {
			return true;
		}
	}

	_x= x;
	// above
	if (y) { // > 0
		_y= y-1;
		if (TestAndSwap( current, _board[_y][_x])) {
			return true;
		}
	}

	//below
	if (y!=3) {
		_y= y+1;
		return TestAndSwap( current, _board[_y][_x]); 
	}
	return false;
}

/**
 * Check if board is properly ordered
 * @return true if puzzle solved
 */
bool Game15::Finished() const
{
	const unsigned char* element= &_board[0][0];
	for ( unsigned int i= 0; i < 15; i++) { // neat trick
		if (*(element+i)==(i+1)) {
			continue;
		}
		return false;
	}
	return true;
}

/** 
 * @brief Get player's moves count 
 * @return moves counter
 */
unsigned int Game15::GetMoves() const
{
	return _moves;
}
