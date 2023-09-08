#include<iostream>
#include<windows.h>//Contains declarations for all of the functions in the Windows API
#include<conio.h>//Cncludes inbuilt functions like getch()
#include <cstdlib>//Activates the rand()

using namespace std;

bool gameOver;
const int width = 20;//To set the width of the wall
const  int height = 20;//To seth the height of the wall

int x;
int y;
int fruitX;
int fruitY;

int score;

enum eDirection{STOP = 0, LEFT, RIGHT, UP, DOWN};//This helps to move the snake up,down,left,right
eDirection dir;//Hold the direction of the snake

//x coordinate of the tail
int xTail[100];
//y coordunate of the tail
int yTail[100];
//Length of the tail 
int nTail;

void Setup(){	
	gameOver = false;
	dir = STOP;//The snake will not move until we start the moving it
	
	//To set the snake head at the middle of the border
	x = width / 2;
	y = height /2;
	
	//Here the fruit will be placed in a random place
	fruitX = rand() % width;//rand() generates a random number 0 to (width - 1)
	fruitY = rand() % height;
	
	//Set the score as 0 at the begining of the game
	score = 0;
}

void Draw(){
	system("cls"); //cls and clear are terminal/command prompt commands used to clear the screen 
	
	//Set the top border of the map
	for(int i = 0; i < (width+2); ++i){
		cout << "#";
	}
	cout << endl;
	
	//Set the middle part of the map
	for(int i = 0; i < height; ++i){
		for(int j = 0; j < width; ++j){
			if(j == 0){
				cout << "#";
			}
			//Place the snake head at middle of the map
			if(i == y && j == x){
				cout << "O";
			}
			//Place the Fruit at random place of the map
			else if(i == fruitY && j == fruitX){
				cout << "F";
			}
			else{
				bool print = false;
				//Increase the tail length of the snake when it eats food
				for(int k = 0; k < nTail; ++k){
					if(xTail[k] == j && yTail[k] == i){
						cout << "o";
						print = true;
					}
				}
				if(!print){
					cout << " ";
				}					
			}					
			
			if(j == (width - 1)){
				cout << "#";
			}			
		}
		cout << endl;
	}
	
	//Set the bottom border of the map
	for(int  i = 0; i < (width+2); ++i){
		cout <<"#";
	}
	cout << endl;	
	cout << "Score: " << score << endl;
	cout << "Press 'x' to quit the game at any time." << endl;
}

void Input(){
	//_kbhit() return a positive value if a particular key is pressed
	if(_kbhit()){
		//_getch() -> Return the ASCII value off the enterd charcter
		switch(_getch()){
			case 'a':
				dir = LEFT;
				break;
			case 'd':
				dir = RIGHT;
				break;
			case 'w':
				dir = UP;
				break;
			case 's':
				dir = DOWN;
				break;
			case 'x':
				gameOver = true;
				break;
		}
	}
}

void Logic(){
	
	//prevX -> previous x coordinate of the tail
	//prevY -> previous y coordinate of the tail
	int prevX = xTail[0];
	int prevY = yTail[0];
	
	
	int prev2x;
	int prev2y;
	
	//Set the first elemet of the xTail and yTail to follow the head
	xTail[0] = x;
	yTail[0] = y;
	
	//To move the tail
	for(int i = 1; i < nTail; ++i){
		prev2x = xTail[i];
		prev2y = yTail[i];
		xTail[i] = prevX;
		yTail[i] = prevY;
		prevX = prev2x;
		prevY = prev2y;
	}
	
	//To move the snake head according to keyboard command
	switch(dir){
		case LEFT: 
			x--;
			break;
		case RIGHT:
		 	x++;
			break;
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
		default:
			break;
	}
	
//	//End the game if snake head exceed the limit of the border
//	if(x > width || x < 0 || y > height || y < 0){
//		gameOver = true;
//	}
	
	//Snake will not die if he go through the left & right border
	if(x >= width){
		x = 0;
	}
	else if(x < 0){
		x = width - 1;
	}
	
	//Snake will not die if he go through the top & bottom border
	if(y >= height){
		y = 0;
	}
	else if(y < 0){
		y = height - 1;
	}
	
	
	//When snake hit himself the game should over
	for(int i = 0; i < nTail; ++i){
		if (xTail[i] == x && yTail[i] == y){
			gameOver = true;
			cout << "Game is over!";
		}
	}
		
	if(x == fruitX && y == fruitY){
		//Increment the score by 10 if snake eats fruits
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		//Increment the tail when the snake eats the foods
		nTail++;
	}
}

// Function to display the main menu
void MainMenu() {
    system("cls");
    cout << "=== Snake Game Main Menu ===" << endl;
    cout << "1. Start Game" << endl;
    cout << "2. Instructions" << endl;
    cout << "3. Quit" << endl;
    cout << "Enter your choice: ";
}

int main(){
	
 int choice;
 bool quit = false;
    
    while (!quit) {
    	
    	//Call the MainMenu()
        MainMenu();
        cin >> choice;//Get the choice of the user through the keyboard
        
        switch (choice) {
            case 1:
                Setup();
                while (!gameOver) {
                    Draw();//Call the Draw() function
                    Input();//Call the Input() function
                    Logic();//Call the Logic() function
                    Sleep(200);//Cntrol the speed of the game
                }
                break;
            case 2:
                // Display instructions here
                
                system("cls");//cls and clear are terminal/command prompt commands used to clear the screen 
                cout << "=== Instructions ===" << endl;
                cout << "Use w(up), s(down), a(left), d(right) to control the snake's direction." << endl;
                cout << "Eat the fruit (F) to score points and grow longer." << endl;
                cout << "Avoid running into yourself." << endl;
                cout << "You can go through the walls." << endl;
                cout << "Press 'x' to quit the game at any time." << endl;
                cout << "Press any key to return to the main menu..." << endl;
                _getch();//When user clcik any other key user will go the main menu
                break;
            case 3:
                quit = true;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                _getch();//When user click any other key in the keyboard quit option will be executed
                break;
        }
    }
	
	return 0;
}


//Referenced notes
//Frequent Clearing of the Console: In your code, you are using system("cls") to clear the console at every frame of your game. 
//This frequent clearing and redrawing of the entire console can cause flickering. 
//Instead, you can clear the console only when necessary, 
//like when the game state changes, and update only the portions of the screen that have changed.