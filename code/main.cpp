/*
Snake Game v0.0.7
04/27/2017
*/
/* CHANGE LOG:
v0.0.7
- changed some names of objects
- created the input and logic functions to allow snake movement
*/

#include <iostream> 
#include <vector>
#include "Windows.h"
#include "MapTile.h"
#include <conio.h>

std::vector< std::vector <MapTile> > tiles;

bool gameOver = false; //Boolean that causes the main game loop to end after the game is over.

int moveDirection; //Integer that tells which direction the snake is moving towards.

int headXPos = 4; //4 being a random starting position for now.
int headYPos = 4; //4 being a random starting position for now.

int foodXPos = 5; //5 being a random starting position for now.
int foodYPos = 7; //7 being a random starting position for now.

int score = 0;
int highscore = 0;

//vector for tail cordinates?

void displayMap(){
	system("cls");
	std::cout << "MapSize x: " << tiles.size() << std::endl;
	std::cout << "MapSize y: " << tiles[0].size() << std::endl;
	std::cout << "headXPos: " << headXPos << std::endl;
	std::cout << "headYPos: " << headYPos << std::endl;
	std::cout << "foodXPos: " << foodXPos << std::endl;
	std::cout << "foodYPos: " << foodYPos << std::endl;
	std::cout << "moveDirection = " << moveDirection << std::endl;
	//Top Border
	for(int b=0; b<tiles[0].size()+2; b++){
		std::cout << "[]";
	}
	std::cout << std::endl;
	for(int i=0; i<tiles[0].size(); i++){	
		//Left Border	
		std::cout << "[]";
		
		for(int i2=0; i2<tiles.size(); i2++){
			if(headYPos == i && headXPos == i2){ //If the current cell being rendered is the same coordinates as the head.
				std:: cout << " O";              //Switched the headYPos and headXPos since they were backwards and changing the X value would move it along the Y axis
			}else if(foodXPos == i && foodYPos == i2){ //Current cell is where the food is.
				std::cout << " *";
			}else if(tiles[i][i2].getMoveable() == false){ //Unmoveable space. We actually probably don't need this unless we want to make obsticales in the middle of the map.
				std::cout << "[]";
			}else if(tiles[i][i2].getMoveable() == true){ //Empty space.
				std::cout << "  ";
			/*
			}else if(  ~~Check to see if part of the tail is here~~ ){
				std::cout << "~~";
			*/
			}else{ //SOMETHING WENT WRONG!
				std::cout << "??"; 
			}
			
		}
		//Right Border
		std::cout << "[]" << std::endl;
	}
	//Bottom Border
	for(int b=0; b<tiles[0].size()+2; b++){
		std::cout << "[]";
	}
	std::cout << std::endl;
	
}

//Checks for key presses and returns a number 1-4 depending on which key pressed.
enum direction { UP, DOWN, LEFT, RIGHT} snake;
	direction dir;


 // auto gives UP, DOWN, LEFT, and RIGHT the values 0-3
		/*std::cout << sdirection(UP) << std::endl;
		std::cout << sdirection(DOWN) << std::endl;
		std::cout << sdirection(LEFT) << std::endl;
		std::cout << sdirection(RIGHT) << std::endl;
		Checked this out and it prints out 0 - 3 like it should */
void input(){ // grabs the input w a s d and gives them a direction
	if (_kbhit())
	{
		switch (_getch())
		{
			case 'w':
				dir = UP;
				break;
			case 's':
				dir = DOWN;
				break;
			case 'a':
				dir = LEFT;
				break;
			case 'd':
				dir = RIGHT;
				break;
		}
	}
}		
void logic(){                 // HELL YEAH GOT THIS TO WORK
	switch (dir)
	{
		case UP:
			headYPos--;
			break;
		case DOWN:
			headYPos++;
			break;
		case LEFT:
			headXPos--;
			break;
		case RIGHT:
			headXPos++;
			break;
			
	}
}
//Generates random coordinates for a new food object. Checks to make sure it's not in a position where a head or tail piece is.
void randomFoodGenerator(){
	// ???
};

//Generates a random position for the snake head within the map. Avoid making it to close to the border.
void randomHeadGenerator(){
	// ???
};

//Generates a random direction number and sets the moveDirection variable to the new number.
void randomDirectionGenerator(){
	// ???
};

//Game over screen that displays the user's score and the high score. Allows for the option to replay. 
void gameOverScreen(){
	// ???
};

// ~~Function for logging player's previous positions / tail trail?~~

int main(){
	//Sets the size for the map.
	tiles.resize(10);
	for(int i=0; i<tiles.size(); i++){
		tiles[i].resize(10);
	}
	
	//The main game loop.
	while(gameOver == false){ //Keep looping this until the game is over / player loses.
		displayMap();
		input();
		logic();
		Sleep(140); //Pause the program for a fraction of a second to prevent the game from running too fast.
		
		int keyReturn = direction();
		if(keyReturn != 0){ //Check to see if the keyReturn changed because of a key press.
			moveDirection = keyReturn; //Set the moveDirection to the key return int.
			keyReturn = 0; //Return keyReturn to it's default state.
		}
		
		// ~~If statements for each direction.~~
	
		// ~~If statement for wall collision.~~
		
		//.....
		
	}
	
	return 0;
}
