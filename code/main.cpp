/*
Snake Game v0.0.8
04/27/2017
*/
/* CHANGE LOG:
v0.0.8
- Added the start screen
- Modified the debug info shown above the map.
- Removed some old unused code.
- Fixed the food displaying on the wrong coordinates.
- Added wall and food collision
- Added score display.
*/

#include <iostream> 
#include <vector>
#include "Windows.h"
#include "MapTile.h"
#include <conio.h>
#include <sstream> // Needed to convert int to string

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //Handle used for changing text ouput color.

std::vector< std::vector <MapTile> > tiles;

bool gameOver = false; //Boolean that causes the main game loop to end after the game is over.

int headXPos = 4; //4 being a random starting position for now.
int headYPos = 4; //4 being a random starting position for now.

int foodXPos = 5; //5 being a random starting position for now.
int foodYPos = 7; //7 being a random starting position for now.

int score = 0;
int highscore = 0;

//vector for tail cordinates?

/* 
	Adds an appropriate amount of padding to the left and right of a string to make it appear centered in a column.
	If the string is too large for the text field it will cut off the end with an ellipses.
	@param string � A string.
	@param fieldsize � An integer.
	@return � A string the length of fieldsize containing the input string with spaces preceding and following it.
*/ 	
std::string centerString(std::string text, int fieldsize){
	if(text.length() == fieldsize){
		//No centering needs to be done because it fits perfectly.
		return text;
	}
	if(text.length() > fieldsize){
		//If the text is larger than the fieldsize, trim the length down to the fieldsize - 3 and add an ellipses to the end.
		text.erase(text.length() - ((text.length() - fieldsize) + 3), ((text.length() - fieldsize) + 3));
		text += "...";
		return text;
	}
	int leftpadding;
	int rightpadding;
	leftpadding = (fieldsize - text.length()) / 2;
	//Check to see if the fieldsize is even.
	if (fieldsize % 2 == 0){
		//If the text length is an odd amount and the field size is even then the rightpadding will have one less space due to a lost remainder.
		if(text.length() % 2 == 0){
			rightpadding = (fieldsize - text.length()) / 2;
		}else{
			rightpadding = (fieldsize - text.length()) / 2 + 1;
		} 
	}else {
		if(text.length() % 2 == 0){
			rightpadding = (fieldsize - text.length()) / 2 + 1;
		}else{
			rightpadding = (fieldsize - text.length()) / 2;
		} 
	}
	return std::string(leftpadding,' ') + text + std::string(rightpadding,' '); 
};


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

void displayMap(){
	system("cls");
	std::cout << "MapSize x: " << tiles.size() << std::endl;
	std::cout << "MapSize y: " << tiles[0].size() << std::endl;
	std::cout << "headXPos: " << headXPos << std::endl;
	std::cout << "headYPos: " << headYPos << std::endl;
	std::cout << "foodXPos: " << foodXPos << std::endl;
	std::cout << "foodYPos: " << foodYPos << std::endl;
	std::cout << "dir = " << dir << std::endl;
	std::cout << "score = " << score << std::endl;
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
			}else if(foodYPos == i && foodXPos == i2){ //Current cell is where the food is.
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
	std::cout << std::endl << std::endl;
	
	//Convert the points int to a string.
	std::ostringstream scoreStringStream;
    scoreStringStream << score;
    std::string scoreString = scoreStringStream.str();

	std::cout << centerString(scoreString,(tiles[0].size()+2)*2) << std::endl; //Display the score at the bottom of the screen.
};

void startingScreen(){
	int leftBorder = 5;
	//Length: 46
	std::cout << std::endl << std::endl;
	SetConsoleTextAttribute(hConsole, 15); std::cout << std::string( leftBorder, ' ' );
	SetConsoleTextAttribute(hConsole, 15); std::cout << "  "; SetConsoleTextAttribute(hConsole, 32); std::cout << "      "; 
	SetConsoleTextAttribute(hConsole, 15); std::cout << "  "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << "    "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << "    "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "   " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << "    "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << "    "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << " "; SetConsoleTextAttribute(hConsole, 32); std::cout << "        " << std::endl;
	SetConsoleTextAttribute(hConsole, 15);std::cout << std::string( leftBorder, ' ' );
	SetConsoleTextAttribute(hConsole, 15); std::cout << " "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << "    "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << " "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "   " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << "   "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << "   "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << " "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << "   "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << "   "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << "  "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " << std::endl;
	SetConsoleTextAttribute(hConsole, 15); std::cout << std::string( leftBorder, ' ' );
	SetConsoleTextAttribute(hConsole, 15); std::cout << " "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << "       "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "    " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << "  "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << "  "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << "   "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << "  "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << "  "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << "   "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " << std::endl;
	SetConsoleTextAttribute(hConsole, 15); std::cout << std::string( leftBorder, ' ' );
	SetConsoleTextAttribute(hConsole, 15); std::cout << "  "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "      " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << "  "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << " "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << " "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << " "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << "     "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << " "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "     " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << "    "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "      " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << "  "; SetConsoleTextAttribute(hConsole, 32); std::cout  << std::endl;
	SetConsoleTextAttribute(hConsole, 15); std::cout << std::string( leftBorder, ' ' );
	SetConsoleTextAttribute(hConsole, 15); std::cout << "       "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << " "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << "  "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "    " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << " "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "         " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << " "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << "  "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << "   "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " << std::endl;
	SetConsoleTextAttribute(hConsole, 15); std::cout << std::string( leftBorder, ' ' );
	SetConsoleTextAttribute(hConsole, 15); std::cout << " "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << "    "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << " "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << "   "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "   " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << " "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << "     "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << " "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << "   "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << "  "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " << std::endl;
	SetConsoleTextAttribute(hConsole, 15); std::cout << std::string( leftBorder, ' ' );
	SetConsoleTextAttribute(hConsole, 15); std::cout <<  "  "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "      " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << "  "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << "    "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << " "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << "     "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << " "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << "    "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "  " ;
	SetConsoleTextAttribute(hConsole, 15); std::cout << " "; SetConsoleTextAttribute(hConsole, 32); std::cout  << "        " << std::endl;
	SetConsoleTextAttribute(hConsole, 15); std::cout << std::endl << std::endl;
	
	std::cout << centerString("By:",46+leftBorder*2) << std::endl;
	std::cout << centerString("D'Metri Cortez",46+leftBorder*2) << std::endl;
	std::cout << centerString("Jacob Shannon",46+leftBorder*2) << std::endl;
		std::cout << centerString("Brittany Green",46+leftBorder*2) << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << centerString("Press [Enter] to start.",46+leftBorder*2) << std::endl;

	bool enterPress = false;
	while(enterPress == false){
		char key = _getch();
		if(key == '\r'){ //If the enter key is pressed
			enterPress = true;
		}
	}
};

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
	startingScreen();
	//The main game loop.
	while(gameOver == false){ //Keep looping this until the game is over / player loses.
		displayMap();
		input();
		logic();
		Sleep(140); //Pause the program for a fraction of a second to prevent the game from running too fast.
		if(headXPos < 0 || headYPos < 0 || headYPos >= tiles[0].size() || headXPos >= tiles.size()){ //Head hit a wall.
			gameOver = true;
		}
		if(headXPos == foodXPos && headYPos == foodYPos){ //Head hit some food. 
			score++;
		}
		// ~~If statement for tail collision.~~
		
		//.....
		
	}
	
	return 0;
}
