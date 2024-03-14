// main.cpp

#include "Game15.h"
#include "Game15BoardView.h"



// Create instance of simple "Game 15" board
int main( int argc, char *argv[]) 
{

	std::cout << "argc = " << argc << std::endl;
    std::cout << "Lets see what is in argv[]" << std::endl;

    for (int i = 1; i < argc; i++) {
        std::cout << "argv[" << i << "] = " << argv[i] << std::endl;
    }
	// printf("argc =  %d\n", argc);
	// printf("Lets see what is in argv[]\n");

	// for(int i = 1; i < argc; i++){
	// 	printf("argv[%d] = %s\n", i, argv[i]);
	// }
	Game15 game= Game15();
	Game15BoardView view= Game15BoardView(game);
	view.RedrawAll();
	view.Run();
	return 0;
}
