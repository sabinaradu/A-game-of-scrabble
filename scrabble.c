#include <stdio.h>
#include "util/scrabble.h"
#include "util/print_board.h"
#include <string.h>
#include <stdlib.h>

#define SHORT_INPUT 5
#define LINE_LEN 50
#define BONUS_LEN 2

void c1(char game_board[BOARD_SIZE][BOARD_SIZE]) {
	char *cuv, data[LINE_LEN], input[SHORT_INPUT];
	int x, y, dir, number;
	fgets(input, SHORT_INPUT, stdin);
    number = atoi(input);
	for(int i = 1; i <= number; i++) {
	    fgets(data, LINE_LEN, stdin);
	    y = atoi(strtok(data, " "));
	    x = atoi(strtok(NULL, " "));
    	dir = atoi(strtok(NULL, " "));
	   	cuv = strtok(NULL, "\n");

        if(dir == 0) { //scriere la dreapta
		    for(int j = x; j < x + (int)strlen(cuv); j++) {
			    game_board[y][j] = cuv[j - x];
    		}
    	} else { // scriere in jos
            for(int j = y; j < y + (int)strlen(cuv); j++) {
		    	game_board[j][x] = cuv[j - y];
		    }
		}
	}
	print_board(game_board);
}

void print_scores(int p1, int p2) {
    printf("Player 1: %d Points\n", p1);
    printf("Player 2: %d Points\n", p2);
}

void c2(int *points) {
	char *cuv, data[LINE_LEN], input[SHORT_INPUT];
	int number, score_p1 = 0, score_p2 = 0;
	fgets(input, SHORT_INPUT, stdin);
    number = atoi(input);
	for(int i = 1; i <= number; i++) {
	    fgets(data, LINE_LEN, stdin);
        cuv = strtok(data, " ");
        cuv = strtok(NULL, " ");
        cuv = strtok(NULL, " ");
	   	cuv = strtok(NULL, "\n");


        int letter_score, len = strlen(cuv);
        for(int j = 0; j < len; j++) {
            letter_score = points[cuv[j] - 'A'];
            if( i % 2 == 1 )
                score_p1 += letter_score;
            else
                score_p2 += letter_score;
        }
    }
    print_scores(score_p1, score_p2);
}

void c3(int *points) {
    char bonus1[SHORT_INPUT], bonus2[SHORT_INPUT];
	char *cuv, data[LINE_LEN], input[SHORT_INPUT];
	int number, x, y, dir; 
    int score_p1 = 0, score_p2 = 0;
    fgets(bonus1, SHORT_INPUT, stdin);
    fgets(bonus2, SHORT_INPUT, stdin);
    bonus1[BONUS_LEN] = 0;
    bonus2[BONUS_LEN] = 0;
	fgets(input, SHORT_INPUT, stdin);
    number = atoi(input);
	for(int i = 1; i <= number; i++) {
	    fgets(data, LINE_LEN, stdin);
        y = atoi(strtok(data, " "));
        x = atoi(strtok(NULL, " "));
        dir = atoi(strtok(NULL, " "));
	   	cuv = strtok(NULL, "\n");

        int multi_score = 1, word_score = 0;
        int letter_score, bonus_pts, len = strlen(cuv);
        int letter_x, letter_y;
        int has_bonus1 = strstr(cuv, bonus1) ? 1 : 0;
        int has_bonus2 = ((int)(strstr(cuv, bonus2) - cuv) == ((int)(strlen(cuv) - BONUS_LEN))) ? 1 : 0;

        for(int j = 0; j < len; j++) {
            letter_x = x;
            letter_y = y;
            if( dir == 0 )
                letter_x += j;
            else
                letter_y += j;

            letter_score = points[cuv[j] - 'A'];
            bonus_pts = bonus_board[letter_y][letter_x];
            if( bonus_pts == 1 && has_bonus1 )
                multi_score *= 2;
            else if( bonus_pts == 2 && has_bonus2 )
                multi_score *= 3;

            word_score += letter_score;
            
        }
        
        if( i % 2 == 1 )
            score_p1 += word_score * multi_score;
        else
            score_p2 += word_score * multi_score;
    }
    print_scores(score_p1, score_p2);
}

int main() {
    int points[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 
        10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
	
    char game_board[BOARD_SIZE][BOARD_SIZE];
	for(int i = 0; i < BOARD_SIZE; i++) 
		for(int j = 0; j < BOARD_SIZE; j++)
			game_board[i][j] = '.';
	
    char task_char[SHORT_INPUT];
    int task_no;
    fgets(task_char, SHORT_INPUT, stdin);
    task_no = atoi(task_char);
    switch(task_no) {
        case 0:
            print_board(game_board);
            break;
        case 1:
            c1(game_board);
            break;
        case 2:
            c2(points);
            break;
        case 3:
            c3(points);
            break;
    }

}
