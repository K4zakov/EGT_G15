/*
 * Game15.h
 *
 *  Created on: 13.11.2012
 *      Author: jorio
 */

#ifndef GAME15_H_
#	define GAME15_H_

#include <iostream>
#include <iomanip>


// forward declaration of view class
class Game15BoardView;

class Game15
{
	friend class Game15BoardView;

private:
	unsigned char _board[4][4];
	unsigned int _moves;

public:
	Game15(bool randomize=true);
	virtual ~Game15();

private:
	bool TestAndSwap( unsigned char& current, unsigned char& neighbour);

public:
	void Initialize();
	void Randomize();
	bool Play( const unsigned x, const unsigned y);
	bool Finished() const;
	unsigned int GetMoves() const;
	void Dump() const
	{
		for ( unsigned int y= 0; y<4; ++y) {
			for ( unsigned int x= 0; x<4; ++x) {
					std::cout << std::setw(2) << std::setfill(' ') << (unsigned)_board[y][x] << " ";
			}
			std::cout << std::endl;
		}
	}
};

#endif /* GAME15_H_ */
