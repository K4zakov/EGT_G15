// main.cpp

#include "Game15.h"
#include "Game15BoardView.h"



// Create instance of simple "Game 15" board
int main( int argc, char *argv[]) 
{

	Game15 game= Game15();
	Game15BoardView view= Game15BoardView(game);
	view.RedrawAll();
	view.Run();
	return 0;
}
