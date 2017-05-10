/*
Snake Game v1.3 (Release)
05/09/2017
*/
/* CHANGE LOG:
v1.3 (Release)
- Removed old commented out code.
- Added some comments to explain some of the code
*/

#include <iostream> 
#include <vector> //Needed for map and tail vectors.
#include "Windows.h" //Needed to be able to change the console text color and trigger the beep sound.
#include <conio.h> //Needed to check for key presses.
#include <sstream> //Needed to convert int to string
#include <cstdlib> //Needed to access the 'rand()' function
#include <ctime> //Needed to use the computers time to simulate true randomness

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //Handle used for changing text ouput color.

std::vector< std::vector <int> > tiles; //MultiDimenional vector to hold each tile of the map.

std::vector< std::vector <int> > tailCords; //MultiDimensional vector for the tail cordinates. Each element in the first dimension is a tail piece which is comprised of two int elements for the X and Y position.

bool gameOver = false; //Boolean that causes the main game loop to end after the game is over.

int headXPos; //Position of the head on the X axis.
int headYPos; //Position of the head on the Y axis.

int foodXPos; //Position of the food item on the X axis.
int foodYPos; //Position of the food item on the Y axis.

int score = 0; //The player's current score.
int highScore = 0; //The player's highest score.
int mapSize = 15; //The size of the map, both the X and Y axis size.


/* 
	Adds an appropriate amount of padding to the left and right of a string to make it appear centered in a column.
	If the string is too large for the text field it will cut off the end with an ellipses.
	@param string – A string.
	@param fieldsize – An integer.
	@return – A string the length of fieldsize containing the input string with spaces preceding and following it.
*/ 	
std::string centerString(std::string text, int fieldsize){
	if(text.length() == fieldsize){ //Check to see if the string length is the same size as the text field.
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

void updateTail(){ 
	//Adds new elements to the cords showing the lastest position of the head.
	//Higher index elements are closer to the head. [0] is the end of the tail.
	tailCords.resize(tailCords.size()+1); //Increase the amount of elements (amount of tail pieces)
	tailCords[tailCords.size()-1].push_back(headXPos); //Have the latest element have the lastest cordinate of the head.
	tailCords[tailCords.size()-1].push_back(headYPos); //Have the latest element have the lastest cordinate of the head.
	if (tailCords.size() > score+1){ //Check the score againt the tail size to see if the tail size has gotten too big.
		tailCords.erase(tailCords.begin()); //Remove the first element. This makes it look like the end of the tail is being pulled by the body.
	}
};

void input(){ // grabs the input w a s d and gives them a direction
	if (_kbhit())
	{
		switch (_getch())
		{
			case 'w':
				if(dir != DOWN){
				dir = UP;
				}
				break;
			case 's':
				if(dir != UP){
				dir = DOWN;
				}
				break;
			case 'a':
				if(dir != RIGHT){
				dir = LEFT;
				}
				break;
			case 'd':
				if(dir != LEFT){
				dir = RIGHT;
				}
				break;
		}
	}
}
	
void logic(){
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
	for(int b=0; b<tiles[0].size()+2; b++){ //Top Border - Repeat depending on how large the map is.
		std::cout << char(219) << char(219); //char(219) is a solid block
	}
	std::cout << std::endl;
	for(int i=0; i<tiles[0].size(); i++){ //Displays each row (X).
		std::cout << char(219) << char(219); //Left border.
		for(int i2=0; i2<tiles.size(); i2++){ //Displays each coloum piece in the row.
			bool tailTile = false; //Boolean to indicate if the current cell is a tail piece.
			for(int i3=0; i3<tailCords.size(); i3++){ //Go through each element of the tailCords vector.
				if(tailCords[i3][0] == i2 && tailCords[i3][1] == i){ //If the current element has cordinates matching the current tile being displayed...
					tailTile = true; //Set the boolean to true.
				}
			}
			if(headYPos == i && headXPos == i2){ //If the current cell being rendered is the same coordinates as the head.
				std::cout << char(237) << char(237); //Head
			}else if(foodYPos == i && foodXPos == i2){ //Current cell is where the food is.
				std::cout << char(235) << char(235); //Food Item
			}else if(tailTile == true){ //Current cell is where a tail should be.
				std::cout << char(177) << char(177); //Tail Piece
			}else{ //Empty space
				std::cout << "  "; 
			}	
		}
		std::cout << char(219) << char(219) << std::endl; //Right Border
	}
	//Bottom Border
	for(int b=0; b<tiles[0].size()+2; b++){ //Repeat depending on how large the map is.
		std::cout << char(219) << char(219);
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
	std::cout << std::endl << std::endl;
	std::cout << centerString("Press [Enter] to start.",46+leftBorder*2) << std::endl << std::endl;
	std::cout << centerString("(Use WASD keys to move)",46+leftBorder*2) << std::endl;

	bool enterPress = false;
	while(enterPress == false){ //Keep checking for the key press until the enter key is pressed.
		char key = _getch();
		if(key == '\r'){ //If the enter key is pressed
			enterPress = true;
		}
	}
};

bool tailFoodCheck(){ //Returns a boolean value if the food piece is on the same spot a tail piece is.
	for(int i=0; i<tailCords.size(); i++){
		if(tailCords[i][0] == foodXPos && tailCords[i][1] == foodYPos){
			return true;
		}
	}
}

//Generates random coordinates for a new food object. Checks to make sure it's not in a position where a head or tail piece is.
void randomFoodGenerator(){
	srand(time(0));
	//Generate a food item on a random tile
	foodXPos = 1+(rand() % ((tiles.size()-1)-1 + 1));
	foodYPos = 1+(rand() % ((tiles[0].size()-1)-1 + 1));
	
	while (foodXPos == headXPos && foodYPos == headYPos){ //Repeat the random generation while the food is at the same spot as the head.
		foodXPos = 1+(rand() % ((tiles.size()-1)-1 + 1));
		foodYPos = 1+(rand() % ((tiles[0].size()-1)-1 + 1));
	}
	while(tailFoodCheck() == true){ //Repeat the random generation while the food is at the same spot as any of the tail peices.
		foodXPos = 1+(rand() % ((tiles.size()-1)-1 + 1));
		foodYPos = 1+(rand() % ((tiles[0].size()-1)-1 + 1));
	}
};

//Generates a random position for the snake head within the map. 
void randomHeadGenerator(){ 
	headXPos = 1+(rand() % ((tiles.size()-1)-2 + 1));
	headYPos = 1+(rand() % ((tiles[0].size()-1)-2 + 1));
};

//Generates a random direction number and sets the moveDirection variable to the new number.
void randomDirectionGenerator(){
	int dirInt = rand() % 4;
	switch(dirInt){
		case 0:
			dir = UP;
			break;
		case 1:
			dir = DOWN;
			break;
		case 2:
			dir = LEFT;
			break;
		case 3:
			dir = RIGHT;
			break;
	}
};

//Game over screen that displays the user's score and the high score. Allows for the option to replay. 
void gameOverScreen(){
	system("CLS"); //Clear the terminal screen
	if(score > highScore){ //Update the high score if the current score is higher than the high score.
		highScore = score;
	}
	std::cout << std::endl << centerString("GAME OVER!",40) << std::endl;
	std::cout << centerString("Current Score:",40) << std::endl;
	//Convert the score integer into a string.
	std::ostringstream scoreStringStream;
    scoreStringStream << score;
    std::string scoreString = scoreStringStream.str();
	std::cout << centerString(scoreString,40) << std::endl; //Display the score at the bottom of the screen.
	std::cout << std::endl;
	std::cout << centerString("Previous High Score:",40) << std::endl;
	//Convert the high score integer into a string.
	std::ostringstream highScoreStringStream;
    highScoreStringStream << highScore;
    std::string highScoreString = highScoreStringStream.str();
	std::cout << centerString(highScoreString,40) << std::endl;
	std::cout << centerString("Press [Enter] to start a new game.",40) << std::endl;
	
	bool enterPress = false;
	while(enterPress == false){ //Keep checking for an enter key press
		char key = _getch();
		if(key == '\r'){ //If the enter key is pressed
			enterPress = true;
		}
	}
	gameOver = false;
};

int main(){
	tiles.resize(mapSize); //Sets the Y size for the map.
	for(int i=0; i<tiles.size(); i++){ //Sets the X size for the map.
		tiles[i].resize(mapSize);
	}
	startingScreen(); //Display the start screen.
	while(true){ //The main game loop.
		tailCords.resize(0); //Reset the tail corinates down to zero.
		score = 0; //Reset the score.
		randomHeadGenerator(); //Generate random head position
		randomDirectionGenerator(); //Generate a random starting direction for the head.
		randomFoodGenerator(); //Generate a random food position.
		while(gameOver == false){ //The game instance loop.
			updateTail(); //Update the tail by trimming or increasing it's size and updating it's position.
			displayMap(); //Display the game screen.
			input(); //Check for input
			logic(); //Change movement direction.
			Sleep(80); //Pause the program for a fraction of a second to prevent the game from running too fast.
			
			if(headXPos == foodXPos && headYPos == foodYPos){ //Check to see if the head hit the food item.
				score++; //Increase score
				Beep(900,50); //Make a beep sound
				randomFoodGenerator(); //Generate a new random position for the food item.
			}else if(headXPos < 0 || headYPos < 0 || headYPos >= tiles[0].size() || headXPos >= tiles.size()){ //Check to see if the head hit a wall.
				gameOver = true; //End the game instance.
			}else{
				for(int i=0; i<tailCords.size(); i++){ //Go though the tailCords vector
					if(tailCords[i][0] == headXPos && tailCords[i][1] == headYPos){ //Check to see if the head position is on a the current tail position being checked.
						gameOver = true; //End the game instance.
					}
				}
			}
		}
		gameOverScreen(); //Display the game over screen.
	}
	return 0;
}
