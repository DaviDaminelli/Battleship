#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

bool computer_ship_grid[10][10], user_ship_grid[10][10], ship_grid[10][10], user_hit_grid[10][10], computer_hit_grid[10][10], placement=false, pregame=false, match=false, c=false;
int r, xi, yi, xf, yf, user_hit_counter = 0, computer_hit_counter = 0;

//start menu
void start_menu(){
	printf("\n\t\t\t    Welcome to:");
	printf("\n");
	printf("\n ===================================================================");
	printf("\n| ####    #   ##### ##### #     #     #####  #### #   #   #   ####  |");
	printf("\n| #   #  # #    #     #   #     #     #     #     #   #       #   # |");
	printf("\n| ####  #   #   #     #   #     #     ####   ###  #####   #   ####  |");
	printf("\n| #   # #---#   #     #   #     #     #         # #   #   #   #     |");
	printf("\n| #   # #   #   #     #   #     #     #         # #   #   #   #     |");
	printf("\n| ####  #   #   #     #   ##### ##### ##### ####  #   #   #   #     |");
	printf("\n ===================================================================");
	printf("\n");
	printf("\n\t\t\tpress any key to start");
	if(!kbhit()){
	getch();
	}
	fflush(stdin);
}

//set all spaces in the array false
void initialize2DArray(bool arr[][10]){
	for(int i = 0; i < 10; i++){
    	for(int j = 0; j < 10; j++){
        	arr[i][j] = false;
    	}
	}
}

//used to print the grid on the following function
void vertical_grid_sidebar(int i){
   	int a;
       		a=i;
       		a++;
       		if(a==10){
       			printf("%d | ", a);
			}
       		else {
       			printf("%d  | ", a);
			}
	}

void print2DArray(bool arr[][10]){
	printf("Grid:\n\n");
	printf("     1  2  3  4  5  6  7  8  9  10\n");
	printf("     -  -  -  -  -  -  -  -  -  - \n");
	for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
        	if(j == 0){
        		vertical_grid_sidebar(i);
			}
        	if(arr[i][j]==true){
        		printf("#  ");
			}
            else{
			printf("%d  ", arr[i][j]);
			}
        }
        printf("\n\n");
    }
}

void place_ship_2_horizontally(){
	
}

//pass the information of ship_grid one array to another
//define the array that you want the information of ship_grid to be transfered
void connect_grid(bool arr[10][10]){
    for(int i = 0; i < 10; i++){
    	for(int j = 0; j < 10; j++){
        	if(ship_grid[i][j] == true){
        	    arr[i][j]=true;
    	    }
	    }
    }    
}

//return a pseudorandom number from the nanosecond at the moment.
int random_number(){
	struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return (ts.tv_nsec)%10;
}

void auto_place_ship2_horizontally(){
	//assign random nubers to generate coordinates
	int rgn1 = random_number(), rgn2 = random_number();
	xi = rgn1;
	yi = rgn2;
	
	//if they start on one limit, it won't go beyond it in this direction
	if(xi == 0){
		xf = xi + 1;
		ship_grid[yi][xi]=true;
		ship_grid[yi][xf]=true;
	}
	//if they start on one limit, it won't go beyond it in this direction
	else if(xi == 9){
		xf = xi - 1;
		ship_grid[yi][xi]=true;
		ship_grid[yi][xf]=true;
	}
	else {
		//generate number again to decide how the ship will be placed
		rgn1 = random_number();
		//the ship will be placed left to right if the new generated number is odd
		else if(rgn1 % 2 == 1){
			xf = xi + 1;
			ship_grid[yi][xi]=true;
			ship_grid[yi][xf]=true;
		}
		//the ship will be placed right to left if new generated number is evem
		else if(rgn1 % 2 == 0){
			xf = xi - 1;
			ship_grid[yi][xi]=true;
			ship_grid[yi][xf]=true;
		}
	}
}

void auto_place_ship2_vertically(){
	//assign random nubers to generate coordinates
	int rgn1 = random_number(), rgn2 = random_number();
	xi = rgn1;
	yi = rgn2;
	//if they start on one limit, it won't go beyond it in this direction
	if(yi == 0){
		yf = yi + 1;
		ship_grid[yi][xi]=true;
		ship_grid[yf][xi]=true;
	}
	//if they start on one limit, it won't go beyond it in this direction
	else if(yi == 9){
		yf = yi - 1;
		ship_grid[yi][xi]=true;
		ship_grid[yf][xi]=true;
	}
	else{
		//generate number again to decide how the ship will be placed
		rgn1 = random_number();
		//the ship will be placed top to down if the new generated number is odd
		else if(rgn1 % 2 == 1){
			yf= yi + 1;
			ship_grid[yi][xi]=true;
			ship_grid[yf][xi]=true;
		}
		//the ship will be placed down to top if the new generated number is even
		else if(rgn1 % 2 == 0){
			yf = yi - 1;
			ship_grid[yi][xi]=true;
			ship_grid[yf][xi]=true;
		}
	}
}

void auto_place_ship2(){
	//get random generated number
	int rgn = random_number();
	//if the number is even
	if(rgn % 2 == 0){	
		auto_place_ship2_horizontally();
	}
	//if the number is odd
	if(rgn % 2 == 1){
		auto_place_ship2_vertically();
	}
}

void auto_place_ship3_1_horizontally(){
	//assign random nubers to generate coordinates
	int rgn1 = random_number(), rgn2 = random_number();
	xi = rgn1;
	yi = rgn2;
	//generate number again to decide how the ship will be placed
	rgn1 = random_number();
	//check if there already is a ship placed on the coordinates generated
	if(ship_grid[yi][xi]==true){
	    if(c==true){
	    	//avoid the pseudorandom number to be the same every time, therefore avoiding an infinite loop
	        sleep(0.307);
	    }
	    //avoid the pseudorandom number to be the same every time, therefore avoiding an infinite loop. It will be used repeatedely from now on in the code
	    sleep(1.004);
		auto_place_ship3_1_horizontally();
		c=true;
		return;
	}
	//if they start on one limit, it won't go beyond it in this direction
	else if(xi == 0|| xi == 1){
		xf = xi + 2;
		//check the space
		int j = xi;
		for(j; xf >= j; j++){
			if(ship_grid[yi][j]==true){
			    sleep(0.303);
				auto_place_ship3_1_horizontally();
				return;
			}
		}
		//set ship in space
		for(xi; xf >= xi; xi++){
			ship_grid[yi][xi] = true;
		}
	}
	//if they start on one limit, it won't go beyond it in this direction
	else if(xi == 9 || xi == 8){
		xf = xi - 2;
		//check
		int j = xi;
		for(j; xf <= j; j--){
			if(ship_grid[yi][j]==true){
			    sleep(0.303);
				auto_place_ship3_1_horizontally();
				return;
			}
		}
		//set
		for(xi; xf <= xi; xi--){
			ship_grid[yi][xi] = true;
		}
	}
	//the ship will be placed left to right if the new generated number is odd
	else if(rgn1 % 2 == 1){
		xf = xi + 2;
		//check
		int j = xi;
		for(j; xf >= j; j++){
			if(ship_grid[yi][j]==true){
			    sleep(0.303);
			    auto_place_ship3_1_horizontally();
			    return;
			}
		}
		//set
		for(xi; xf >= xi; xi++){
			ship_grid[yi][xi] = true;
		}
	}
	//the ship will be placed right to left if the new generated number is even
	else if(rgn1 % 2 == 0){
		xf = xi - 2;
		//check
		int j = xi;
		for(j; xf <= j; j--){
			if(ship_grid[yi][j]==true){
			    sleep(0.303);
				auto_place_ship3_1_horizontally();
				return;
			}
		}
		//set
		for(xi; xf <= xi; xi--){
			ship_grid[yi][xi] = true;
		}
	}
}

void auto_place_ship3_1_vertically(){
	//assign random nubers to generate coordinates
	int rgn1 = random_number(), rgn2 = random_number();
	xi = rgn1;
	yi = rgn2;
	//generate number again to decide how the ship will be placed
	rgn1 = random_number();
	//check if there already is a ship placed on the coordinates generated
	if(ship_grid[yi][xi]==true){
	        if(c==true){
	            sleep(0.307);
	        }
	        sleep(1.004);
			auto_place_ship3_1_vertically();
			c=true;
			return;
	}
	//if they start on one limit, it won't go beyond it in this direction
	else if(yi == 0|| yi == 1){
		yf = yi + 2;
		//check
		int i = yi;
		for(i; yf >= i; i++){
			    if(ship_grid[i][xi]==true){
			    sleep(0.303);
				auto_place_ship3_1_vertically();
				return;
			}
		}
		//set
		for(yi; yf >= yi; yi++){
			ship_grid[yi][xi] = true;
		}
	}
	//if they start on one limit, it won't go beyond it in this direction
	else if(yi == 9 || yi == 8){
		yf = yi - 2;
		//check
		int i = yi;
		for(i; yf <= i; i--){
			if(ship_grid[i][xi]==true){
			    sleep(0.303);
				auto_place_ship3_1_vertically();
				return;
			}
		}
		//set
		for(yi; yf <= yi; yi--){
			ship_grid[yi][xi] = true;
		}
	}
	//the ship will be placed top to down if the new generated number is odd
	else if(rgn1 % 2 == 1){
		yf = yi + 2;
		//check
		int i = yi;
		for(i; yf >= i; i++){
			if(ship_grid[i][xi]==true){
			    sleep(0.303);
			    auto_place_ship3_1_vertically();
			    return;
		}
	}
		//set
		for(yi; yf >= yi; yi++){
			ship_grid[yi][xi] = true;
		}
	}
	//the ship will be placed down to top if the new generated number is even
	else if(rgn1 % 2 == 0){
		yf = yi - 2;
		//check
		int i = yi;
		for(i; yf <= i; i--){
			if(ship_grid[i][xi]==true){
			    sleep(0.303);
				auto_place_ship3_1_vertically();
				return;
			}
		}
		//set
		for(yi; yf <= yi; yi--){
			ship_grid[yi][xi] = true;
		}
	}
}

void auto_place_ship3_1(){
    //get random generated number
	int rgn = random_number();
	//if the number is even
	if(rgn % 2 == 0){	
		auto_place_ship3_1_horizontally();
	}
	//if the number is odd
	if(rgn % 2 == 1){
		auto_place_ship3_1_vertically();
	}
}

void auto_place_ship3_2_horizontally(){
	//assign random nubers to generate coordinates
	int rgn1 = random_number(), rgn2 = random_number();
	xi = rgn1;
	yi = rgn2;
	//generate number again to decide how the ship will be placed
	rgn1 = random_number();
	//check if there already is a ship placed on the coordinates generated
	if(ship_grid[yi][xi]==true){
	    if(c==true){
	        sleep(0.307);
	    }
	    sleep(1.004);
		auto_place_ship3_2_horizontally();
		c=true;
		return;
	}
	//if they start on one limit, it won't go beyond it in this direction
	else if(xi == 0|| xi == 1){
		xf = xi + 2;
		//check the space
		int j = xi;
		for(j; xf >= j; j++){
			if(ship_grid[yi][j]==true){
			    sleep(0.303);
				auto_place_ship3_2_horizontally();
				return;
			}
		}
		//set ship in space
		for(xi; xf >= xi; xi++){
			ship_grid[yi][xi] = true;
		}
	}
	//if they start on one limit, it won't go beyond it in this direction
	else if(xi == 9 || xi == 8){
		xf = xi - 2;
		//check
		int j = xi;
		for(j; xf <= j; j--){
			if(ship_grid[yi][j]==true){
			    sleep(0.303);
				auto_place_ship3_2_horizontally();
				return;
			}
		}
		//set
		for(xi; xf <= xi; xi--){
			ship_grid[yi][xi] = true;
		}
	}

	//the ship will be placed left to right if the new generated number is odd
	else if(rgn1 % 2 == 1){
		xf = xi + 2;
		//check
		int j = xi;
		for(j; xf >= j; j++){
			if(ship_grid[yi][j]==true){
			    sleep(0.303);
			    auto_place_ship3_2_horizontally();
			    return;
			}
		}
		//set
		for(xi; xf >= xi; xi++){
			ship_grid[yi][xi] = true;
		}
	}
	//the ship will be placed right to left if the new generated number is even
	else if(rgn1 % 2 == 0){
		xf = xi - 2;
		//check
		int j = xi;
		for(j; xf <= j; j--){
			if(ship_grid[yi][j]==true){
			    sleep(0.303);
				auto_place_ship3_2_horizontally();
				return;
			}
		}
		//set
		for(xi; xf <= xi; xi--){
			ship_grid[yi][xi] = true;
		}
	}
}

void auto_place_ship3_2_vertically(){
	//assign random nubers to generate coordinates
	int rgn1 = random_number(), rgn2 = random_number();
	xi = rgn1;
	yi = rgn2;
	//generate number again to decide how the ship will be placed
	rgn1 = random_number();
	//check if there already is a ship placed on the coordinates generated
	if(ship_grid[yi][xi]==true){
	        if(c==true){
	            sleep(0.307);
	        }
	        sleep(1.004);
			auto_place_ship3_2_vertically();
			c=true;
			return;
	}
	//if they start on one limit, it won't go beyond it in this direction
	else if(yi == 0|| yi == 1){
		yf = yi + 2;
		//check
		int i = yi;
		for(i; yf >= i; i++){
			    if(ship_grid[i][xi]==true){
			    sleep(0.303);
				auto_place_ship3_1_vertically();
				return;
			}
		}
		//set
		for(yi; yf >= yi; yi++){
			ship_grid[yi][xi] = true;
		}
	}
	//if they start on one limit, it won't go beyond it in this direction
	else if(yi == 9 || yi == 8){
		yf = yi - 2;
		//check
		int i = yi;
		for(i; yf <= i; i--){
			if(ship_grid[i][xi]==true){
			    sleep(0.303);
				auto_place_ship3_2_vertically();
				return;
			}
		}
		//set
		for(yi; yf <= yi; yi--){
			ship_grid[yi][xi] = true;
		}
	}
	//the ship will be placed top to down if the new generated number is odd
	else if(rgn1 % 2 == 1){
		yf = yi + 2;
		//check
		int i = yi;
		for(i; yf >= i; i++){
			if(ship_grid[i][xi]==true){
			    sleep(0.303);
			    auto_place_ship3_2_vertically();
			    return;
		}
	}
		//set
		for(yi; yf >= yi; yi++){
			ship_grid[yi][xi] = true;
		}
	}
	//the ship will be placed down to top if the new generated number is even
	else if(rgn1 % 2 == 0){
		yf = yi - 2;
		//check
		int i = yi;
		for(i; yf <= i; i--){
			if(ship_grid[i][xi]==true){
			    sleep(0.303);
				auto_place_ship3_2_vertically();
				return;
			}
		}
		//set
		for(yi; yf <= yi; yi--){
			ship_grid[yi][xi] = true;
		}
	}
}

void auto_place_ship3_2(){
    //get random generated number
	int rgn = random_number();
	//if the number is even
	if(rgn % 2 == 0){	
		auto_place_ship3_2_horizontally();
	}
	//if the number is odd
	if(rgn % 2 == 1){
		auto_place_ship3_2_vertically();
	}
}

void auto_place_ship4_horizontally(){
	//assign random nubers to generate coordinates
	int rgn1 = random_number(), rgn2 = random_number();
	xi = rgn1;
	yi = rgn2;
	//generate number again to decide how the ship will be placed
	rgn1 = random_number();
	//check if there already is a ship placed on the coordinates generated
	if(ship_grid[yi][xi]==true){
	    if(c==true){
	        sleep(0.307);
	    }
	    sleep(1.004);
		auto_place_ship4_horizontally();
		c=true;
		return;
	}
	//if they start on one limit, it won't go beyond it in this direction
	else if(xi == 0|| xi == 1 || xi ==2){
		xf = xi + 3;
		//check the space
		int j = xi;
		for(j; xf >= j; j++){
			if(ship_grid[yi][j]==true){
			    sleep(0.303);
				auto_place_ship4_horizontally();
				return;
			}
		}
		//set ship in space
		for(xi; xf >= xi; xi++){
			ship_grid[yi][xi] = true;
		}
	}
	//if they start on one limit, it won't go beyond it in this direction
	else if(xi == 9 || xi == 8 || xi == 7){
		xf = xi - 3;
		//check
		int j = xi;
		for(j; xf <= j; j--){
			if(ship_grid[yi][j]==true){
			    sleep(0.303);
				auto_place_ship4_horizontally();
				return;
			}
		}
		//set
		for(xi; xf <= xi; xi--){
			ship_grid[yi][xi] = true;
		}
	}
	//the ship will be placed left to right if the new generated number is odd
	else if(rgn1 % 2 == 1){
		xf = xi + 3;
		//check
		int j = xi;
		for(j; xf >= j; j++){
			if(ship_grid[yi][j]==true){
			    sleep(0.303);
			    auto_place_ship4_horizontally();
			    return;
			}
		}
		//set
		for(xi; xf >= xi; xi++){
			ship_grid[yi][xi] = true;
		}
	}
	//the ship will be placed right to left if the new generated number is even
	else if(rgn1 % 2 == 0){
		xf = xi - 3;
		//check
		int j = xi;
		for(j; xf <= j; j--){
			if(ship_grid[yi][j]==true){
			    sleep(0.303);
				auto_place_ship4_horizontally();
				return;
			}
		}
		//set
		for(xi; xf <= xi; xi--){
			ship_grid[yi][xi] = true;
		}
	}
}

void auto_place_ship4_vertically(){
	//assign random nubers to generate coordinates
	int rgn1 = random_number(), rgn2 = random_number();
	xi = rgn1;
	yi = rgn2;
	//generate number again to decide how the ship will be placed
	rgn1 = random_number();
	//check if there already is a ship placed on the coordinates generated
	if(ship_grid[yi][xi]==true){
	        if(c==true){
	            sleep(0.307);
	        }
	        sleep(1.004);
			auto_place_ship4_vertically();
			c=true;
			return;
	}
	//if they start on one limit, it won't go beyond it in this direction
	else if(yi == 0|| yi == 1 || yi == 2){
		yf = yi + 3;
		//check
		int i = yi;
		for(i; yf >= i; i++){
			    if(ship_grid[i][xi]==true){
			    sleep(0.303);
				auto_place_ship4_vertically();
				return;
			}
		}
		//set
		for(yi; yf >= yi; yi++){
			ship_grid[yi][xi] = true;
		}
	}
	//if they start on one limit, it won't go beyond it in this direction
	else if(yi == 9 || yi == 8 || yi == 7){
		yf = yi - 3;
		//check
		int i = yi;
		for(i; yf <= i; i--){
			if(ship_grid[i][xi]==true){
			    sleep(0.303);
				auto_place_ship4_vertically();
				return;
			}
		}
		//set
		for(yi; yf <= yi; yi--){
			ship_grid[yi][xi] = true;
		}
	}
	//the ship will be placed top to down if the new generated number is odd
	else if(rgn1 % 2 == 1){
		yf = yi + 3;
		//check
		int i = yi;
		for(i; yf >= i; i++){
			if(ship_grid[i][xi]==true){
			    sleep(0.303);
			    auto_place_ship4_vertically();
			    return;
		}
	}
		//set
		for(yi; yf >= yi; yi++){
			ship_grid[yi][xi] = true;
		}
	}
	//the ship will be placed down to top if the new generated number is even
	else if(rgn1 % 2 == 0){
		yf = yi - 3;
		//check
		int i = yi;
		for(i; yf <= i; i--){
			if(ship_grid[i][xi]==true){
			    sleep(0.303);
				auto_place_ship4_vertically();
				return;
			}
		}
		//set
		for(yi; yf <= yi; yi--){
			ship_grid[yi][xi] = true;
		}
	}
}

void auto_place_ship4(){
    //get random generated number
	int rgn = random_number();
	//if the number is even
	if(rgn % 2 == 0){	
		auto_place_ship4_horizontally();
	}
	//if the number is odd
	if(rgn % 2 == 1){
		auto_place_ship4_vertically();
	}
}

void auto_place_ship5_horizontally(){
	//assign random nubers to generate coordinates
	int rgn1 = random_number(), rgn2 = random_number();
	xi = rgn1;
	yi = rgn2;
	//generate number again to decide how the ship will be placed
	rgn1 = random_number();
	//check if there already is a ship placed on the coordinates generated
	if(ship_grid[yi][xi]==true){
	    if(c==true){
	        sleep(0.307);
	    }
	    sleep(1.004);
		auto_place_ship5_horizontally();
		c=true;
		return;
	}
	//if they start on one limit, it won't go beyond it in this direction
	else if(xi == 0|| xi == 1 || xi == 2 || xi == 3){
		xf = xi + 4;
		//check the space
		int j = xi;
		for(j; xf >= j; j++){
			if(ship_grid[yi][j]==true){
			    sleep(0.303);
				auto_place_ship5_horizontally();
				return;
			}
		}
		//set ship in space
		for(xi; xf >= xi; xi++){
			ship_grid[yi][xi] = true;
		}
	}
	//if they start on one limit, it won't go beyond it in this direction
	else if(xi == 9 || xi == 8 || xi == 7 || xi == 6){
		xf = xi - 4;
		//check
		int j = xi;
		for(j; xf <= j; j--){
			if(ship_grid[yi][j]==true){
			    sleep(0.303);
				auto_place_ship5_horizontally();
				return;
			}
		}
		//set
		for(xi; xf <= xi; xi--){
			ship_grid[yi][xi] = true;
		}
	}
	//the ship will be placed left to right if the new generated number is odd
	else if(rgn1 % 2 == 1){
		xf = xi + 4;
		//check
		int j = xi;
		for(j; xf >= j; j++){
			if(ship_grid[yi][j]==true){
			    sleep(0.303);
			    auto_place_ship5_horizontally();
			    return;
			}
		}
		//set
		for(xi; xf >= xi; xi++){
			ship_grid[yi][xi] = true;
		}
	}
	//the ship will be placed right to left if the new generated number is even
	else if(rgn1 % 2 == 0){
		xf = xi - 4;
		//check
		int j = xi;
		for(j; xf <= j; j--){
			if(ship_grid[yi][j]==true){
			    sleep(0.303);
				auto_place_ship5_horizontally();
				return;
			}
		}
		//set
		for(xi; xf <= xi; xi--){
			ship_grid[yi][xi] = true;
		}
	}
}

void auto_place_ship5_vertically(){
	//assign random nubers to generate coordinates
	int rgn1 = random_number(), rgn2 = random_number();
	xi = rgn1;
	yi = rgn2;
	//generate number again to decide how the ship will be placed
	rgn1 = random_number();
	//check if there already is a ship placed on the coordinates generated
	if(ship_grid[yi][xi]==true){
	        if(c==true){
	            sleep(0.307);
	        }
	        sleep(1.004);
			auto_place_ship5_vertically();
			c=true;
			return;
	}
	//if they start on one limit, it won't go beyond it in this direction
	else if(yi == 0|| yi == 1 || yi == 2 || yi == 3){
		yf = yi + 4;
		//check
		int i = yi;
		for(i; yf >= i; i++){
			    if(ship_grid[i][xi]==true){
			    sleep(0.303);
				auto_place_ship5_vertically();
				return;
			}
		}
		//set
		for(yi; yf >= yi; yi++){
			ship_grid[yi][xi] = true;
		}
	}
	//if they start on one limit, it won't go beyond it in this direction
	else if(yi == 9 || yi == 8 || yi == 7 || yi == 6){
		yf = yi - 4;
		//check
		int i = yi;
		for(i; yf <= i; i--){
			if(ship_grid[i][xi]==true){
			    sleep(0.303);
				auto_place_ship5_vertically();
				return;
			}
		}
		//set
		for(yi; yf <= yi; yi--){
			ship_grid[yi][xi] = true;
		}
	}
	//the ship will be placed top to down if the new generated number is odd
	else if(rgn1 % 2 == 1){
		yf = yi + 4;
		//check
		int i = yi;
		for(i; yf >= i; i++){
			if(ship_grid[i][xi]==true){
			    sleep(0.303);
			    auto_place_ship5_vertically();
			    return;
		}
	}
		//set
		for(yi; yf >= yi; yi++){
			ship_grid[yi][xi] = true;
		}
	}
	//the ship will be placed down to top if the new generated number is even
	else if(rgn1 % 2 == 0){
		yf = yi - 4;
		//check
		int i = yi;
		for(i; yf <= i; i--){
			if(ship_grid[i][xi]==true){
			    sleep(0.303);
				auto_place_ship5_vertically();
				return;
			}
		}
		//set
		for(yi; yf <= yi; yi--){
			ship_grid[yi][xi] = true;
		}
	}
}

void auto_place_ship5(){
    //get random generated number
	int rgn = random_number();
	//if the number is even
	if(rgn % 2 == 0){	
		auto_place_ship5_horizontally();
	}
	//if the number is odd
	if(rgn % 2 == 1){
		auto_place_ship5_vertically();
	}
}

void auto_place_computer_ships(){
    initialize2DArray(ship_grid);
    initialize2DArray(computer_ship_grid);
    auto_place_ship2();
    auto_place_ship3_1();
    c=false;
    auto_place_ship3_2();
    c=false;
    printf("\n\nAlmost there...\n");
    auto_place_ship4();
    c=false;
    auto_place_ship5();
    c=false;
    connect_grid(computer_ship_grid);
    initialize2DArray(ship_grid);
}

void auto_place_user_ships(){
	printf("\e[1;1H\e[2J");
	printf("Your ships are being calculated and will be displayed here. This can take a few seconds...");
    initialize2DArray(ship_grid);
    initialize2DArray(user_ship_grid);
    auto_place_ship2();
    auto_place_ship3_1();
    c=false;
    auto_place_ship3_2();
    c=false;
    printf("\n\nAlmost there...\n");
    auto_place_ship4();
    c=false;
    auto_place_ship5();
    c=false;//*/
    connect_grid(user_ship_grid);
    initialize2DArray(ship_grid);
    printf("\n\nYour ships have been placed!\n");
    print2DArray(user_ship_grid);
    printf("\n\nPress any key to continue:\n");
    if(!kbhit()){
	getch();
	}
	fflush(stdin);
}


void place_ship2(){
	printf("Place the Destroyer (2-coordinate ship # # ):\nHorizontally(press 1) or vertically(press 2)?\n");
	if(!kbhit()){
	r = getch();
	}
	fflush(stdin);
	if(r == 49){
		//do this do place horizontally
		printf("\n- You returned 1\n");
		printf("\nThe ship of size 2 will be placed horizontally.");
		printf("\nType coordinates X & Y of one edge of your 2-coordinate ship and click enter: \n");
		scanf("%d %d", &xi, &yi);
		fflush(stdin);
		printf("\n- You have entered X = %d, Y = %d\n", xi, yi);
		//condition to check boundaries on first input
		if(xi >= 11 || yi >= 11 || xi <= 0 || yi <= 0){
			printf("\nThe coordinates of X and Y have to be within the range of 10 , 10. Try again:\n\n\n");
			place_ship2();
			return;
		}
		printf("\nType only coordinate X of the other edge of your 2-coordinate ship and click enter: \n");
		scanf("%d", &xf);
		fflush(stdin);
		printf("\n- You have entered X = %d", xf);
		//condition to check boundaries on second input
		if(xf >= 11 || xf <= 0){
			printf("\nThe coordinates of X have to be within the range of 10 , 10. Try again:\n\n\n");
			place_ship2();
			return;
		}
			//condition to check if the coordinates are the same
		else if(xi == xf){
			printf("\nThe coordinates cant be the same, try again:\n\n\n");
			place_ship2();
			return;
		}
		//condition to check if the gap between the two edges of the inputs match that of the ship
		else if(xf-xi != 1 && xi-xf != 1){
			printf("\nThe edges are either too long apart, or too short apart, try again:\n\n\n");
			place_ship2();
			return;
		}
		printf("\n\nYour ship is here:\n\n");
		//since arrays start at position 0 and the user won't use coordinate zero, it is necessary to reduce 1 number from user input to match the true position in the array
		yi--;
		xi--;
		xf--;
		//aplying user input into the array and printing it
		ship_grid[yi][xi]=true;
		ship_grid[yi][xf]=true;
		print2DArray(ship_grid);
		printf("\n\nPress any key to proceed to the next ship");
		if(!kbhit()){
		getch();
		}
		fflush(stdin);
		return;
	}
	else if(r == 50){
		//do this to place vertically
		printf("\n- You returned 2\n");
		printf("\nThe ship of size 2 will be placed vertically.");
		printf("\nType coordinates X & Y of one edge of your 2-coordinate ship and click enter: \n");
		scanf("%d %d", &xi, &yi);
		fflush(stdin);
		printf("\n- You have entered X = %d, Y = %d\n", xi, yi);
		//condition to check boundaries on first input
		if(xi >= 11 || yi >= 11 || xi <= 0 || yi <= 0){
			printf("\nThe coordinates of X and Y have to be within the range of 10 , 10. Try again:\n\n\n");
			place_ship2();
			return;
			}
		printf("\nType only coordinate Y of the other edge of your 2-coordinate ship and click enter: \n");
		scanf("%d", &yf);
		fflush(stdin);
		printf("\n- You have entered Y = %d", yf);
		//condition to check boundaries on second input
		if(yf >= 11 || yf <= 0){
			printf("\nThe coordinates of Y have to be within the range of 10 , 10. Try again:\n\n\n");
			place_ship2();
			return;
		}
		//condition to check if the coordinates are the same
		else if(yi == yf){
			printf("\nThe coordinates cant be the same, try again:\n\n\n");
			place_ship2();
			return;
		}
		//condition to check if the gap between the two edges of the inputs match that of the ship
		else if(yf-yi != 1 && yi-yf != 1){
			printf("\nThe edges are either too long apart, or too short apart, try again:\n\n\n");
			place_ship2();
			return;
		}
		printf("\n\nYour ship is here:\n\n");
		//since arrays start at position 0 and the user won't use coordinate zero, it is necessary to reduce 1 number from user input to match the true position in the array
		xi--;
		yi--;
		yf--;
		//aplying user input into the array and printing it
		ship_grid[yi][xi]=true;
		ship_grid[yf][xi]=true;
		print2DArray(ship_grid);
		printf("\n\nPress any key to proceed to the next ship");
		if(!kbhit()){
		getch();
		}
		fflush(stdin);
		return;
	}
	else {
		printf("\n-Yout typed an invalid input.");
		printf("\nReturn a valid option:\n\n\n");
		place_ship2();
		return;
		}
}
	

void place_ship3_1(){
	//printf("\e[1;1H\e[2J");
	printf("Place the Submarine (3-coordinate submarine # # # ); horizontally(press 1) or vertically(press 2)?\n");
	if(!kbhit()){
	r = getch();
	}
	if(r == 49){
		//do this do place horizontally
		printf("\n- You returned 1\n");
		printf("\nThe submarine of size 3 will be placed horizontally.");
		printf("\nType coordinates X & Y of one edge of your 3-coordinate submarine and click enter: ");
		scanf("%d %d", &xi, &yi);
		fflush(stdin);
		printf("\n- You have entered X = %d, Y = %d\n", xi, yi);
		//condition to check boundaries on first input
		if(xi >= 11 || yi >= 11 || xi <= 0 || yi <= 0){
			printf("\nThe coordinates of X and Y have to be within the range of 10 , 10. Try again:\n\n\n");
			place_ship3_1();
			return;
		}
		//Since arrays start at position 0 and the user won't use coordinate zero, it is necessary to reduce 1 number from user input to match the true position in the array
		//this action has been brought forward from here onwards in the code because of the condition to check for other ships on the grid.
		yi--;
		xi--;
		if(ship_grid[yi][xi]==true){
			printf("\nThere is a ship already placed here. Place it again:\n");
			place_ship3_1();
			return;
		}
		yi++;
		xi++;
		printf("\nType only coordinate X of the other edge of your 3-coordinate submarine and click enter: \n");
		scanf("%d", &xf);
		fflush(stdin);
		printf("\n- You have entered X = %d", xf);
		//condition to check boundaries on second input
		if(xf >= 11 || xf <= 0){
			printf("\nThe coordinates of X have to be within the range of 10 , 10. Try again:\n\n\n");
			place_ship3_1();
			return;
		}
		//condition to check if the coordinates are the same
		else if(xi == xf){
			printf("\nThe coordinates cant be the same, try again:\n\n\n");
			place_ship3_1();
			return;
		}
		//xf-- also has been brought forward because it is needed for the following check
		yi--;
		xi--;
		xf--;
		if(ship_grid[yi][xf]==true){
			printf("\nThere is a ship already placed here. Place it again:\n");
			place_ship3_1();
			return;
		}
		//condition to check if the gap between the two edges of the inputs match that of the ship
		else if(xf-xi != 2 && xi-xf != 2){
			printf("\nThe edges are either too long apart, or too short apart, try again:\n\n\n");
			place_ship3_1();
			return;
		}
		//condition to check if there are any ships already placed in the board inside the path of the coordinates if second input is greater than the first
		if(xf>xi){
			//xf > xi
			int j = xi;
			//checking
			for(j; xf >= j; j++){
			if(ship_grid[yi][j]==true){
				//returning the values as they were delivered
				yi++;
				xi++;
				xf++;
				j++;
				printf("\nThere is a ship already placed between the edges %d,%d & %d,%d at coordinate %d,%d. Place it again:\n\n", xi, yi, xf, yi, j, yi);
				yi--;
				xi--;
				xf--;
				j--;
				//matching their value for the array indexes again
				place_ship3_1();
				return;
				}
			}
		}
		//condition to check if there are any ships already placed in the board inside the path of the coordinates if first input is greater than the second
		else if(xf<xi){
			//xf < xi
			int j = xi;
			//checking
			for(j; xf <= j; j--){
			if(ship_grid[yi][j]==true){
				//returning the values as they were delivered
				yi++;
				xi++;
				xf++;
				j++;
				printf("\nThere is a ship already placed between the edges %d,%d & %d,%d at coordinate %d,%d. Place it again:\n\n ", xf, yi, xi, yi, j, yi);
				yi--;
				xi--;
				xf--;
				j--;
				//matching their value for the array indexes  again
				place_ship3_1();
				return;
				}
			}
		}
		printf("\n\nYour ship is here:\n\n");
		//aplying user input into the array and printing it
		if(xf>xi){
			for(xi; xf >= xi; xi++){
				ship_grid[yi][xi] = true;
			}
		}
		else if(xf<xi){
			for(xi; xf <= xi; xi--){
				ship_grid[yi][xi] = true;
			}
		}
		print2DArray(ship_grid);
		printf("\n\nPress any key to proceed to the next ship");
		if(!kbhit()){
		getch();
		}
		fflush(stdin);
		return;
	}
	else if(r == 50){
		//do this to place vertically
		printf("\n- You returned 2\n");
		printf("\nThe submarine of size 3 will be placed vertically.");
		printf("\nType coordinates X & Y of one edge of your 3-coordinate ship and click enter: ");
		scanf("%d %d", &xi, &yi);
		fflush(stdin);
		printf("\n- You have entered X = %d, Y = %d\n", xi, yi);
		//condition to check boundaries on first input
		if(xi >= 11 || yi >= 11 || xi <= 0 || yi <= 0){
			printf("\nThe coordinates of X and Y have to be within the range of 10 , 10. Try again:\n\n\n");
			place_ship3_1();
			return;
			}
		//Since arrays start at position 0 and the user won't use coordinate zero, it is necessary to reduce 1 number from user input to match the true position in the array
		yi--;
		xi--;
		if(ship_grid[yi][xi]==true){
			printf("\nThere is a ship already placed here. Place it again:\n");
			place_ship3_1();
			return;
		}
		yi++;
		xi++;
		printf("\nType only coordinate Y of the other edge of your 3-coordinate ship and click enter: \n");
		scanf("%d", &yf);
		fflush(stdin);
		printf("\n- You have entered Y = %d", yf);
		//condition to check boundaries on second input
		if(yf >= 11 || yf <= 0){
			printf("\nThe coordinates of Y have to be within the range of 10 , 10. Try again:\n\n\n");
			place_ship3_1();
			return;
		}
		//condition to check if the coordinates are the same
		else if(yi == yf){
			printf("\nThe coordinates cant be the same, try again:\n\n\n");
			place_ship3_1();
			return;
		}
		xi--;
		yi--;
		yf--;
		if(ship_grid[yi][xf]==true){
			printf("\nThere is a ship already placed here. Place it again:\n");
			place_ship3_1();
			return;
		}
		//condition to check if the gap between the two edges of the inputs match that of the ship
		else if(yf-yi != 2 && yi-yf != 2){
			printf("\nThe edges are either too long apart, or too short apart, try again:\n\n\n");
			place_ship3_1();
			return;
		}
		//condition to check if there are any ships already placed in the board inside the path of the coordinates if second input is greater than the first
		if(yf>yi){
			//yf > yi
			int i = yi;
			//checking
			for(i; yf >= i; i++){
			if(ship_grid[i][xi]==true){
				//returning the values as they were delivered
				xi++;
				yi++;
				yf++;
				i++;
				printf("\nThere is a ship already placed between the edges %d,%d & %d,%d at coordinate %d,%d. Place it again:\n\n", xi, yi, xi, yf, xi, i);
				xi--;
				yi--;
				yf--;
				i--;
				//matching their value for the array indexes again
				place_ship3_1();
				return;
				}
			}
		}
		//condition to check if there are any ships already placed in the board inside the path of the coordinates if first input is greater than the second
		else if(yf<yi){
			//yf < yi
			int i = yi;
			//checking
			for(i; yf <=i; i--){
			if(ship_grid[i][xi]==true){
				//returning the values as they were delivered
				xi++;
				yi++;
				yf++;
				i++;
				printf("\nThere is a ship already placed between the edges %d,%d & %d,%d at coordinate %d,%d. Place it again:\n\n ", xi, yi, xi, yf, xi, i);
				xi--;
				yi--;
				yf--;
				i--;
				//matching their value for the array indexes  again
				place_ship3_1();
				return;
				}
			}
		}
		printf("\n\nYour ship is here:\n\n");
		//aplying user input into the array and printing it
		if(yf>yi){
			for(yi; yf >= yi; yi++){
				ship_grid[yi][xi] = true;
			}
		}
		else if(yf<yi){
			for(yi; yf <= yi; yi--){
				ship_grid[yi][xi] = true;
			}
		}
		print2DArray(ship_grid);
		printf("\n\nPress any key to proceed to the next ship");
		if(!kbhit()){
		getch();
		}
		fflush(stdin);
		return;
	}
	else {
		printf("\n-Yout typed an invalid input.");
		printf("\nReturn a valid option:\n\n\n");
		place_ship3_1();
		return;
		}
}

void place_ship3_2(){
	//printf("\e[1;1H\e[2J");
	printf("Place the Cuiser (3-coordinate ship # # # ); horizontally(press 1) or vertically(press 2)?\n");
	if(!kbhit()){
	r = getch();
	}
	if(r == 49){
		//do this do place horizontally
		printf("\n- You returned 1\n");
		printf("\nThe ship of size 3 will be placed horizontally.");
		printf("\nType coordinates X & Y of one edge of your 3-coordinate ship and click enter: ");
		scanf("%d %d", &xi, &yi);
		fflush(stdin);
		printf("\n- You have entered X = %d, Y = %d\n", xi, yi);
		//condition to check boundaries on first input
		if(xi >= 11 || yi >= 11 || xi <= 0 || yi <= 0){
			printf("\nThe coordinates of X and Y have to be within the range of 10 , 10. Try again:\n\n\n");
			place_ship3_2();
			return;
		}
		//Since arrays start at position 0 and the user won't use coordinate zero, it is necessary to reduce 1 number from user input to match the true position in the array
		yi--;
		xi--;
		if(ship_grid[yi][xi]==true){
			printf("\nThere is a ship already placed here. Place it again:\n");
			place_ship3_2();
			return;
		}
		yi++;
		xi++;
		printf("\nType only coordinate X of the other edge of your 3-coordinate ship and click enter: \n");
		scanf("%d", &xf);
		fflush(stdin);
		printf("\n- You have entered X = %d", xf);
		//condition to check boundaries on second input
		if(xf >= 11 || xf <= 0){
			printf("\nThe coordinates of X have to be within the range of 10 , 10. Try again:\n\n\n");
			place_ship3_2();
			return;
		}
		//condition to check if the coordinates are the same
		else if(xi == xf){
			printf("\nThe coordinates cant be the same, try again:\n\n\n");
			place_ship3_2();
			return;
		}
		//xf-- also has been brought forward because it is needed for the following check
		yi--;
		xi--;
		xf--;
		if(ship_grid[yi][xf]==true){
			printf("\nThere is a ship already placed here. Place it again:\n");
			place_ship3_2();
			return;
		}
		//condition to check if the gap between the two edges of the inputs match that of the ship
		else if(xf-xi != 2 && xi-xf != 2){
			printf("\nThe edges are either too long apart, or too short apart, try again:\n\n\n");
			place_ship3_2();
			return;
		}
		//condition to check if there are any ships already placed in the board inside the path of the coordinates if second input is greater than the first
		if(xf>xi){
			//xf > xi
			int j = xi;
			//checking
			for(j; xf >= j; j++){
			if(ship_grid[yi][j]==true){
				//returning the values as they were delivered
				yi++;
				xi++;
				xf++;
				j++;
				printf("\nThere is a ship already placed between the edges %d,%d & %d,%d at coordinate %d,%d. Place it again:\n\n", xi, yi, xf, yi, j, yi);
				yi--;
				xi--;
				xf--;
				j--;
				//matching their value for the array indexes again
				place_ship3_2();
				return;
				}
			}
		}
		//condition to check if there are any ships already placed in the board inside the path of the coordinates if first input is greater than the second
		else if(xf<xi){
			//xf < xi
			int j = xi;
			//checking
			for(j; xf <= j; j--){
			if(ship_grid[yi][j]==true){
				//returning the values as they were delivered
				yi++;
				xi++;
				xf++;
				j++;
				printf("\nThere is a ship already placed between the edges %d,%d & %d,%d at coordinate %d,%d. Place it again:\n\n ", xf, yi, xi, yi, j, yi);
				yi--;
				xi--;
				xf--;
				j--;
				//matching their value for the array indexes  again
				place_ship3_2();
				return;
				}
			}
		}
		printf("\n\nYour ship is here:\n\n");
		//aplying user input into the array and printing it
		if(xf>xi){
			for(xi; xf >= xi; xi++){
				ship_grid[yi][xi] = true;
			}
		}
		else if(xf<xi){
			for(xi; xf <= xi; xi--){
				ship_grid[yi][xi] = true;
			}
		}
		print2DArray(ship_grid);
		printf("\n\nPress any key to proceed to the next ship");
		if(!kbhit()){
		getch();
		}
		fflush(stdin);
		return;
	}
	else if(r == 50){
		//do this to place vertically
		printf("\n- You returned 2\n");
		printf("\nThe ship of size 3 will be placed vertically.");
		printf("\nType coordinates X & Y of one edge of your 3-coordinate ship and click enter: ");
		scanf("%d %d", &xi, &yi);
		fflush(stdin);
		printf("\n- You have entered X = %d, Y = %d\n", xi, yi);
		//condition to check boundaries on first input
		if(xi >= 11 || yi >= 11 || xi <= 0 || yi <= 0){
			printf("\nThe coordinates of X and Y have to be within the range of 10 , 10. Try again:\n\n\n");
			place_ship3_2();
			return;
			}
		//Since arrays start at position 0 and the user won't use coordinate zero, it is necessary to reduce 1 number from user input to match the true position in the array
		yi--;
		xi--;
		if(ship_grid[yi][xi]==true){
			printf("\nThere is a ship already placed here. Place it again:\n");
			place_ship3_2();
			return;
		}
		yi++;
		xi++;
		printf("\nType only coordinate Y of the other edge of your 3-coordinate ship and click enter: \n");
		scanf("%d", &yf);
		fflush(stdin);
		printf("\n- You have entered Y = %d", yf);
		//condition to check boundaries on second input
		if(yf >= 11 || yf <= 0){
			printf("\nThe coordinates of Y have to be within the range of 10 , 10. Try again:\n\n\n");
			place_ship3_2();
			return;
		}
		//condition to check if the coordinates are the same
		else if(yi == yf){
			printf("\nThe coordinates cant be the same, try again:\n\n\n");
			place_ship3_2();
			return;
		}
		xi--;
		yi--;
		yf--;
		if(ship_grid[yi][xf]==true){
			printf("\nThere is a ship already placed here. Place it again:\n");
			place_ship3_2();
			return;
		}
		//condition to check if the gap between the two edges of the inputs match that of the ship
		else if(yf-yi != 2 && yi-yf != 2){
			printf("\nThe edges are either too long apart, or too short apart, try again:\n\n\n");
			place_ship3_2();
			return;
		}
		//condition to check if there are any ships already placed in the board inside the path of the coordinates if second input is greater than the first
		if(yf>yi){
			//yf > yi
			int i = yi;
			//checking
			for(i; yf >= i; i++){
			if(ship_grid[i][xi]==true){
				//returning the values as they were delivered
				xi++;
				yi++;
				yf++;
				i++;
				printf("\nThere is a ship already placed between the edges %d,%d & %d,%d at coordinate %d,%d. Place it again:\n\n", xi, yi, xi, yf, xi, i);
				xi--;
				yi--;
				yf--;
				i--;
				//matching their value for the array indexes again
				place_ship3_2();
				return;
				}
			}
		}
		//condition to check if there are any ships already placed in the board inside the path of the coordinates if first input is greater than the second
		else if(yf<yi){
			//yf < yi
			int i = yi;
			//checking
			for(i; yf <=i; i--){
			if(ship_grid[i][xi]==true){
				//returning the values as they were delivered
				xi++;
				yi++;
				yf++;
				i++;
				printf("\nThere is a ship already placed between the edges %d,%d & %d,%d at coordinate %d,%d. Place it again:\n\n ", xi, yi, xi, yf, xi, i);
				xi--;
				yi--;
				yf--;
				i--;
				//matching their value for the array indexes  again
				place_ship3_2();
				return;
				}
			}
		}
		printf("\n\nYour ship is here:\n\n");
		//aplying user input into the array and printing it
		if(yf>yi){
			for(yi; yf >= yi; yi++){
				ship_grid[yi][xi] = true;
			}
		}
		else if(yf<yi){
			for(yi; yf <= yi; yi--){
				ship_grid[yi][xi] = true;
			}
		}
		print2DArray(ship_grid);
		printf("\n\nPress any key to proceed to the next ship");
		if(!kbhit()){
		getch();
		}
		fflush(stdin);
		return;
	}
	else {
		printf("\n-Yout typed an invalid input.");
		printf("\nReturn a valid option:\n\n\n");
		place_ship3_2();
		return;
		}
}

void place_ship4(){
	//printf("\e[1;1H\e[2J");
	printf("Place the Battleship (4-coordinate ship # # # # ); horizontally(press 1) or vertically(press 2)?\n");
	if(!kbhit()){
	r = getch();
	}
	if(r == 49){
		//do this do place horizontally
		printf("\n- You returned 1\n");
		printf("\nThe submarine of size 4 will be placed horizontally.");
		printf("\nType coordinates X & Y of one edge of your 4-coordinate ship and click enter: ");
		scanf("%d %d", &xi, &yi);
		fflush(stdin);
		printf("\n- You have entered X = %d, Y = %d\n", xi, yi);
		//condition to check boundaries on first input
		if(xi >= 11 || yi >= 11 || xi <= 0 || yi <= 0){
			printf("\nThe coordinates of X and Y have to be within the range of 10 , 10. Try again:\n\n\n");
			place_ship4();
			return;
		}
		//Since arrays start at position 0 and the user won't use coordinate zero, it is necessary to reduce 1 number from user input to match the true position in the array
		yi--;
		xi--;
		if(ship_grid[yi][xi]==true){
			printf("\nThere is a ship already placed here. Place it again:\n");
			place_ship4();
			return;
		}
		yi++;
		xi++;
		printf("\nType only coordinate X of the other edge of your 4-coordinate ship and click enter: \n");
		scanf("%d", &xf);
		fflush(stdin);
		printf("\n- You have entered X = %d", xf);
		//condition to check boundaries on second input
		if(xf >= 11 || xf <= 0){
			printf("\nThe coordinates of X have to be within the range of 10 , 10. Try again:\n\n\n");
			place_ship4();
			return;
		}
		//condition to check if the coordinates are the same
		else if(xi == xf){
			printf("\nThe coordinates cant be the same, try again:\n\n\n");
			place_ship4();
			return;
		}
		//xf-- also has been brought forward because it is needed for the following check
		yi--;
		xi--;
		xf--;
		if(ship_grid[yi][xf]==true){
			printf("\nThere is a ship already placed here. Place it again:\n");
			place_ship4();
			return;
		}
		//condition to check if the gap between the two edges of the inputs match that of the ship
		else if(xf-xi != 3 && xi-xf != 3){
			printf("\nThe edges are either too long apart, or too short apart, try again:\n\n\n");
			place_ship4();
			return;
		}
		//condition to check if there are any ships already placed in the board inside the path of the coordinates if second input is greater than the first
		if(xf>xi){
			//xf > xi
			int j = xi;
			//checking
			for(j; xf >= j; j++){
			if(ship_grid[yi][j]==true){
				//returning the values as they were delivered
				yi++;
				xi++;
				xf++;
				j++;
				printf("\nThere is a ship already placed between the edges %d,%d & %d,%d at coordinate %d,%d. Place it again:\n\n", xi, yi, xf, yi, j, yi);
				yi--;
				xi--;
				xf--;
				j--;
				//matching their value for the array indexes again
				place_ship4();
				return;
				}
			}
		}
		//condition to check if there are any ships already placed in the board inside the path of the coordinates if first input is greater than the second
		else if(xf<xi){
			//xf < xi
			int j = xi;
			//checking
			for(j; xf <= j; j--){
			if(ship_grid[yi][j]==true){
				//returning the values as they were delivered
				yi++;
				xi++;
				xf++;
				j++;
				printf("\nThere is a ship already placed between the edges %d,%d & %d,%d at coordinate %d,%d. Place it again:\n\n ", xf, yi, xi, yi, j, yi);
				yi--;
				xi--;
				xf--;
				j--;
				//matching their value for the array indexes  again
				place_ship4();
				return;
				}
			}
		}
		printf("\n\nYour ship is here:\n\n");
		//aplying user input into the array and printing it
		if(xf>xi){
			for(xi; xf >= xi; xi++){
				ship_grid[yi][xi] = true;
			}
		}
		else if(xf<xi){
			for(xi; xf <= xi; xi--){
				ship_grid[yi][xi] = true;
			}
		}
		print2DArray(ship_grid);
		printf("\n\nPress any key to proceed to the next ship");
		if(!kbhit()){
		getch();
		}
		fflush(stdin);
		return;
	}
	else if(r == 50){
		//do this to place vertically
		printf("\n- You returned 2\n");
		printf("\nThe ship of size 4 will be placed vertically.");
		printf("\nType coordinates X & Y of one edge of your 4-coordinate ship and click enter: ");
		scanf("%d %d", &xi, &yi);
		fflush(stdin);
		printf("\n- You have entered X = %d, Y = %d\n", xi, yi);
		//condition to check boundaries on first input
		if(xi >= 11 || yi >= 11 || xi <= 0 || yi <= 0){
			printf("\nThe coordinates of X and Y have to be within the range of 10 , 10. Try again:\n\n\n");
			place_ship4();
			return;
			}
		//Since arrays start at position 0 and the user won't use coordinate zero, it is necessary to reduce 1 number from user input to match the true position in the array
		yi--;
		xi--;
		if(ship_grid[yi][xi]==true){
			printf("\nThere is a ship already placed here. Place it again:\n");
			place_ship4();
			return;
		}
		yi++;
		xi++;
		printf("\nType only coordinate Y of the other edge of your 4-coordinate ship and click enter: \n");
		scanf("%d", &yf);
		fflush(stdin);
		printf("\n- You have entered Y = %d", yf);
		//condition to check boundaries on second input
		if(yf >= 11 || yf <= 0){
			printf("\nThe coordinates of Y have to be within the range of 10 , 10. Try again:\n\n\n");
			place_ship4();
			return;
		}
		//condition to check if the coordinates are the same
		else if(yi == yf){
			printf("\nThe coordinates cant be the same, try again:\n\n\n");
			place_ship4();
			return;
		}
		xi--;
		yi--;
		yf--;
		if(ship_grid[yi][xf]==true){
			printf("\nThere is a ship already placed here. Place it again:\n");
			place_ship4();
			return;
		}
		//condition to check if the gap between the two edges of the inputs match that of the ship
		else if(yf-yi != 3 && yi-yf != 3){
			printf("\nThe edges are either too long apart, or too short apart, try again:\n\n\n");
			place_ship4();
			return;
		}
		//condition to check if there are any ships already placed in the board inside the path of the coordinates if second input is greater than the first
		if(yf>yi){
			//yf > yi
			int i = yi;
			//checking
			for(i; yf >= i; i++){
			if(ship_grid[i][xi]==true){
				//returning the values as they were delivered
				xi++;
				yi++;
				yf++;
				i++;
				printf("\nThere is a ship already placed between the edges %d,%d & %d,%d at coordinate %d,%d. Place it again:\n\n", xi, yi, xi, yf, xi, i);
				xi--;
				yi--;
				yf--;
				i--;
				//matching their value for the array indexes again
				place_ship4();
				return;
				}
			}
		}
		//condition to check if there are any ships already placed in the board inside the path of the coordinates if first input is greater than the second
		else if(yf<yi){
			//yf < yi
			int i = yi;
			//checking
			for(i; yf <=i; i--){
			if(ship_grid[i][xi]==true){
				//returning the values as they were delivered
				xi++;
				yi++;
				yf++;
				i++;
				printf("\nThere is a ship already placed between the edges %d,%d & %d,%d at coordinate %d,%d. Place it again:\n\n ", xi, yi, xi, yf, xi, i);
				xi--;
				yi--;
				yf--;
				i--;
				//matching their value for the array indexes  again
				place_ship4();
				return;
				}
			}
		}
		printf("\n\nYour ship is here:\n\n");
		//aplying user input into the array and printing it
		if(yf>yi){
			for(yi; yf >= yi; yi++){
				ship_grid[yi][xi] = true;
			}
		}
		else if(yf<yi){
			for(yi; yf <= yi; yi--){
				ship_grid[yi][xi] = true;
			}
		}
		print2DArray(ship_grid);
		printf("\n\nPress any key to proceed to the next ship");
		if(!kbhit()){
		getch();
		}
		fflush(stdin);
		return;
	}
	else {
		printf("\n-Yout typed an invalid input.");
		printf("\nReturn a valid option:\n\n\n");
		place_ship4();
		return;
		}
}
void place_ship5(){
	//printf("\e[1;1H\e[2J");
	printf("Place the Carrier (5-coordinate ship # # # # # ); horizontally(press 1) or vertically(press 2)?\n");
	if(!kbhit()){
	r = getch();
	}
	if(r == 49){
		//do this do place horizontally
		printf("\n- You returned 1\n");
		printf("\nThe ship of size 5 will be placed horizontally.");
		printf("\nType coordinates X & Y of one edge of your 5-coordinate ship and click enter: ");
		scanf("%d %d", &xi, &yi);
		fflush(stdin);
		printf("\n- You have entered X = %d, Y = %d\n", xi, yi);
		//condition to check boundaries on first input
		if(xi >= 11 || yi >= 11 || xi <= 0 || yi <= 0){
			printf("\nThe coordinates of X and Y have to be within the range of 10 , 10. Try again:\n\n\n");
			place_ship5();
			return;
		}
		//Since arrays start at position 0 and the user won't use coordinate zero, it is necessary to reduce 1 number from user input to match the true position in the array
		yi--;
		xi--;
		if(ship_grid[yi][xi]==true){
			printf("\nThere is a ship already placed here. Place it again:\n");
			place_ship5();
			return;
		}
		yi++;
		xi++;
		printf("\nType only coordinate X of the other edge of your 5-coordinate ship and click enter: \n");
		scanf("%d", &xf);
		fflush(stdin);
		printf("\n- You have entered X = %d", xf);
		//condition to check boundaries on second input
		if(xf >= 11 || xf <= 0){
			printf("\nThe coordinates of X have to be within the range of 10 , 10. Try again:\n\n\n");
			place_ship5();
			return;
		}
		//condition to check if the coordinates are the same
		else if(xi == xf){
			printf("\nThe coordinates cant be the same, try again:\n\n\n");
			place_ship5();
			return;
		}
		//xf-- also has been brought forward because it is needed for the following check
		yi--;
		xi--;
		xf--;
		if(ship_grid[yi][xf]==true){
			printf("\nThere is a ship already placed here. Place it again:\n");
			place_ship5();
			return;
		}
		//condition to check if the gap between the two edges of the inputs match that of the ship
		else if(xf-xi != 4 && xi-xf != 4){
			printf("\nThe edges are either too long apart, or too short apart, try again:\n\n\n");
			place_ship5();
			return;
		}
		//condition to check if there are any ships already placed in the board inside the path of the coordinates if second input is greater than the first
		if(xf>xi){
			//xf > xi
			int j = xi;
			//checking
			for(j; xf >= j; j++){
			if(ship_grid[yi][j]==true){
				//returning the values as they were delivered
				yi++;
				xi++;
				xf++;
				j++;
				printf("\nThere is a ship already placed between the edges %d,%d & %d,%d at coordinate %d,%d. Place it again:\n\n", xi, yi, xf, yi, j, yi);
				yi--;
				xi--;
				xf--;
				j--;
				//matching their value for the array indexes again
				place_ship5();
				return;
				}
			}
		}
		//condition to check if there are any ships already placed in the board inside the path of the coordinates if first input is greater than the second
		else if(xf<xi){
			//xf < xi
			int j = xi;
			//checking
			for(j; xf <= j; j--){
			if(ship_grid[yi][j]==true){
				//returning the values as they were delivered
				yi++;
				xi++;
				xf++;
				j++;
				printf("\nThere is a ship already placed between the edges %d,%d & %d,%d at coordinate %d,%d. Place it again:\n\n ", xf, yi, xi, yi, j, yi);
				yi--;
				xi--;
				xf--;
				j--;
				//matching their value for the array indexes  again
				place_ship5();
				return;
				}
			}
		}
		printf("\n\nYour ship is here:\n\n");
		//aplying user input into the array and printing it
		if(xf>xi){
			for(xi; xf >= xi; xi++){
				ship_grid[yi][xi] = true;
			}
		}
		else if(xf<xi){
			for(xi; xf <= xi; xi--){
				ship_grid[yi][xi] = true;
			}
		}
		print2DArray(ship_grid);
		printf("\n\nPress any key to proceed to the next ship");
		if(!kbhit()){
		getch();
		}
		fflush(stdin);
		return;
	}
	else if(r == 50){
		//do this to place vertically
		printf("\n- You returned 2\n");
		printf("\nThe ship of size 5 will be placed vertically.");
		printf("\nType coordinates X & Y of one edge of your 5-coordinate ship and click enter: ");
		scanf("%d %d", &xi, &yi);
		fflush(stdin);
		printf("\n- You have entered X = %d, Y = %d\n", xi, yi);
		//condition to check boundaries on first input
		if(xi >= 11 || yi >= 11 || xi <= 0 || yi <= 0){
			printf("\nThe coordinates of X and Y have to be within the range of 10 , 10. Try again:\n\n\n");
			place_ship5();
			return;
			}
		//Since arrays start at position 0 and the user won't use coordinate zero, it is necessary to reduce 1 number from user input to match the true position in the array
		yi--;
		xi--;
		if(ship_grid[yi][xi]==true){
			printf("\nThere is a ship already placed here. Place it again:\n");
			place_ship5();
			return;
		}
		yi++;
		xi++;
		printf("\nType only coordinate Y of the other edge of your 5-coordinate ship and click enter: \n");
		scanf("%d", &yf);
		fflush(stdin);
		printf("\n- You have entered Y = %d", yf);
		//condition to check boundaries on second input
		if(yf >= 11 || yf <= 0){
			printf("\nThe coordinates of Y have to be within the range of 10 , 10. Try again:\n\n\n");
			place_ship5();
			return;
		}
		//condition to check if the coordinates are the same
		else if(yi == yf){
			printf("\nThe coordinates cant be the same, try again:\n\n\n");
			place_ship5();
			return;
		}
		xi--;
		yi--;
		yf--;
		if(ship_grid[yi][xf]==true){
			printf("\nThere is a ship already placed here. Place it again:\n");
			place_ship5();
			return;
		}
		//condition to check if the gap between the two edges of the inputs match that of the ship
		else if(yf-yi != 4 && yi-yf != 4){
			printf("\nThe edges are either too long apart, or too short apart, try again:\n\n\n");
			place_ship5();
			return;
		}
		//condition to check if there are any ships already placed in the board inside the path of the coordinates if second input is greater than the first
		if(yf>yi){
			//yf > yi
			int i = yi;
			//checking
			for(i; yf >= i; i++){
			if(ship_grid[i][xi]==true){
				//returning the values as they were delivered
				xi++;
				yi++;
				yf++;
				i++;
				printf("\nThere is a ship already placed between the edges %d,%d & %d,%d at coordinate %d,%d. Place it again:\n\n", xi, yi, xi, yf, xi, i);
				xi--;
				yi--;
				yf--;
				i--;
				//matching their value for the array indexes again
				place_ship5();
				return;
				}
			}
		}
		//condition to check if there are any ships already placed in the board inside the path of the coordinates if first input is greater than the second
		else if(yf<yi){
			//yf < yi
			int i = yi;
			//checking
			for(i; yf <=i; i--){
			if(ship_grid[i][xi]==true){
				//returning the values as they were delivered
				xi++;
				yi++;
				yf++;
				i++;
				printf("\nThere is a ship already placed between the edges %d,%d & %d,%d at coordinate %d,%d. Place it again:\n\n ", xi, yi, xi, yf, xi, i);
				xi--;
				yi--;
				yf--;
				i--;
				//matching their value for the array indexes  again
				place_ship5();
				return;
				}
			}
		}
		printf("\n\nYour ship is here:\n\n");
		//aplying user input into the array and printing it
		if(yf>yi){
			for(yi; yf >= yi; yi++){
				ship_grid[yi][xi] = true;
			}
		}
		else if(yf<yi){
			for(yi; yf <= yi; yi--){
				ship_grid[yi][xi] = true;
			}
		}
		print2DArray(ship_grid);
		printf("\n\nPress any key to proceed to the next ship");
		if(!kbhit()){
		getch();
		}
		fflush(stdin);
		return;
	}
	else {
		printf("\n-Yout typed an invalid input.");
		printf("\nReturn a valid option:\n\n\n");
		place_ship5();
		return;
		}
}

//pregame function
void user_place_ship(){
	printf("\e[1;1H\e[2J");
	initialize2DArray(ship_grid);
	printf("\n");
	print2DArray(ship_grid);
	printf("\n");
	place_ship2();
	printf("\e[1;1H\e[2J");
	printf("\n");
	print2DArray(ship_grid);
	printf("\n");
	place_ship3_1();
	printf("\e[1;1H\e[2J");
	printf("\n");
	print2DArray(ship_grid);
	printf("\n");
	place_ship3_2();
	printf("\e[1;1H\e[2J");
	printf("\n");
	print2DArray(ship_grid);
	printf("\n");
	place_ship4();
	printf("\e[1;1H\e[2J");
	printf("\n");
	print2DArray(ship_grid);
	printf("\n");
	place_ship5();
	printf("\n\nPress any key to continue:\n");
	printf("\n");
	connect_grid(user_ship_grid);
	initialize2DArray(ship_grid);
	if(!kbhit()){
	getch();
	fflush(stdin);
	return;
	}
}

void print_user_board(){
	//computer will strike here:
	//uses --> computer_hit_grid
	printf("\n\nYour board:\n\n");
	printf("     1  2  3  4  5  6  7  8  9  10\n");
	printf("     -  -  -  -  -  -  -  -  -  - \n");
	for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
        	if(j == 0){
        		vertical_grid_sidebar(i);
			}
			//if computer input strikes a coordinate that has a ship, 1 will be printed
			if(user_ship_grid[i][j]==true && computer_hit_grid[i][j]==true){
				printf("1  ");
			}
			//prints user ships on the board
        	else if(user_ship_grid[i][j]==true){
        		printf("#  ");
			}
			//prints where the computer already striked
			else if(computer_hit_grid[i][j]==true){
				printf("*  ");
			}
			//rest of the coordinates
            else{
			printf("%d  ", computer_hit_grid[i][j]);
			}
        }
        printf("\n\n");
    }
}

void print_computer_board(){
	//user will strike here:
	//uses --> user_hit_grid
	printf("\n\nComputer's board:\n\n");
	printf("     1  2  3  4  5  6  7  8  9  10\n");
	printf("     -  -  -  -  -  -  -  -  -  - \n");
	for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
        	if(j == 0){
        		vertical_grid_sidebar(i);
			}
			//if user input strikes a coordinate that has a ship, 1 will be printed
			if(computer_ship_grid[i][j]==true && user_hit_grid[i][j]==true){
				printf("1  ");
			}
        	/*
        	//prints computer ships on the board
			else if(computer_ship_grid[i][j]==true){
        		printf("#  ");
			}
			*/
			//prints where the user already striked
			else if(/*computer_ship_grid[i][j]==false*/user_hit_grid[i][j]==true){
				printf("*  ");
			}
			//rest of the coordinates
            else{
			printf("%d  ", user_hit_grid[i][j]);
			}
        }
        printf("\n\n");
    }
}

void user_turn(){
	printf("\nType coordinates X , Y of your strike:");
	//get coordinates
	scanf("%d %d", &xi, &yi);
	fflush(stdin);
	xi--;
	yi--;
	//condition to not strike twice in the same coordinate
	if(user_hit_grid[yi][xi]==true){
		printf("\n\nYou already striked here. Enter a coordinate you have not already striked.");
		user_turn();
		return;
	}
	user_hit_grid[yi][xi]=true;
	if(user_hit_grid[yi][xi]==true && computer_ship_grid[yi][xi]==true){
		user_hit_counter++;
	}
	xi++;
	yi++;
	//return where user striked
	printf("\n-You striked at X: %d , Y:%d  at computer's board:", xi, yi);
	//-- from coordinates and aply them to user_hit_grid
	print_computer_board();
	printf("\nYour succesful strikes: %d\n", user_hit_counter);
}

void computer_turn(){
	//reasoning
	xi = random_number();
	sleep(1.003);
	yi = random_number();
	if(computer_hit_grid[yi][xi]==true){
		computer_turn();
		return;
	}
	computer_hit_grid[yi][xi]=true;
	if(computer_hit_grid[yi][xi]==true && user_ship_grid[yi][xi]==true){
		computer_hit_counter++;
	}
	printf("\n-Computer striked at X: %d , Y: %d  at yout board:", xi, yi);
	print_user_board();
	printf("\nComputer's succesful strikes: %d\n", computer_hit_counter);
}

void matchf(){
	initialize2DArray(user_hit_grid);
	initialize2DArray(computer_hit_grid);
	printf("\e[1;1H\e[2J");
	printf("\n\tMatch start");
	printf("\n\n1 = a strike hit a ship; * a strike did not hit a ship. If the computer succesfully strikes your ship, it will turn from # to 1.");
	print_computer_board();
	printf("-  -  -  -  -  -  -  -  -  -  -  -  -  - ");
	print_user_board();
	if( r == 49){
		while(match == true){
			printf("\n\nYour turn");
			user_turn();
			if(user_hit_counter==17){
				match=false;
			}
			printf("-  -  -  -  -  -  -  -  -  -  -  -  -  - ");
			printf("\n\nComputer's turn");
			computer_turn();
			if(computer_hit_counter==17){
				match=false;
			}
		}
	}
	else if( r==50){
		while(match == true){
			printf("\n\nComputer's turn");
			computer_turn();
			if(computer_hit_counter==17){
				match=false;
			}
			printf("-  -  -  -  -  -  -  -  -  -  -  -  -  - ");
			printf("\n\nYour turn");
			user_turn();
			if(user_hit_counter==17){
				match=false;
			}
		}
	}
	printf("\n\n\tGame over");
	//you won / computer won
	if(user_hit_counter==17){
		printf("\n\nYou won! Computer lost.");
	}
	else/*if(user_hit_counter==17)*/{
		printf("\n\nComputer won! You lost.");
	}
	//play again? yes{pregamef(); return;} else{thanks for playing! credits: davi talone}
}

void set_turn(){
	printf("\e[1;1H\e[2J");
	printf("\n\t\t\t    Match:\n\n");
	printf("Choose your turn and the game will start:\n");
	fflush(stdin);
	printf("\n1. You start.\t2. Computer starts.\t3. Random.\n");
	if(!kbhit()){
	r = getch();
	}
	fflush(stdin);
	if(r==51){
		//r = random_number();
		r=1;
		if(r % 2 == 1){r = 49;}
		else{r = 50;}
		printf("\n-You chose random.\n");
		sleep(1);
	}
	if(r==49){
	printf("\n-You will start the game.");
	}
	else if(r==50){
	printf("\n-The computer will start the game");
	}
	else{
		printf("\n\n-Yout typed an invalid input.");
		printf("\nReturn a valid option:\n\n\n");
		matchf();
		return;
	}
	printf("\n\nMatch starts in 3...");
	sleep(1);
	printf("2...");
	sleep(1);
	printf("1...");
	sleep(1);
	match=true;
}

void set_computer_ships(){
	printf("\e[1;1H\e[2J");
	printf("Computer's ships are being calculated. This can take a few seconds...");
	auto_place_computer_ships();
	printf("\n\nDone\n");
}

void pregamef(){
	printf("\e[1;1H\e[2J");
	printf("\n\t\t\t    Pre-game:\n\n");
	printf("1. Press 1 to place your ships manually;\n");
	printf("\n\t\t\t       or\n");
	printf("\n2. Press 2 to let the computer place your ships randomly.");
	if(!kbhit()){
	r = getch();
	}
	fflush(stdin);
	if(r == 49){
		printf("\n\n-You returned 1.");
		user_place_ship();
	}
	else if(r == 50){
		printf("\n\n-You returned 2.");
		auto_place_user_ships();
	}
	else{
		printf("\n\n-You typed an invalid input.");
		printf("\nReturn a valid option:\n\n\n");
		pregamef();
		return;
	}
	sleep(0.2);
	set_computer_ships();
	set_turn();
}
int main() {
	start_menu();
	pregamef();
	matchf();
  return 0;
}