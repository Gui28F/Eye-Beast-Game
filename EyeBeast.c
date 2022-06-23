/*
max width = 80 columns
tab = 4 spaces
01234567890123456789012345678901234567890123456789012345678901234567890123456789
*/

/*	Linguagens e Ambientes de Programação - Projeto de 2021/2022

	Eye Beast

	Program written in C/C ++ over the wxWidget platform.
	The wxWidget platform runs on Windows, MacOS and Linux.

	This file is only a starting point fo your work. The entire file can
	be changed, starting with this comment.


 AUTHORS IDENTIFICATION
	Student 1: 60045, Guilherme Cruz Fernandes
	Student 2: 60182, Guilherme Filipe Santana Pinto Santana

Comments:

Extra functionality:
	our extra functionality is a candy that runs from hero and when hero "eat"
	the candy it will removes a non trapped monster 
*/

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/* IDENTIFICATION */

#define APP_NAME	"Eye Beast"

#define AUTHOR1		"Guilherme Fernandes (60045)"
#define AUTHOR2		"Guilherme Santana (60182)"

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/* INCLUDES */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "wxTiny.h"


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/* STRINGS */

#define MAX_STRING	256
#define MAX_LINE	1024

typedef char String[MAX_STRING];
typedef char Line[MAX_LINE];


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/* IMAGES */

/******************************************************************************
 * The images are specified in the XPM format [http://en.wikipedia.org/wiki/X_PixMap]
 * After created, each image is represented by an integer in the wxTiny library.
 ******************************************************************************/

typedef int Image;

static Image emptyImg, heroImg, chaserImg, blockImg, boundaryImg, invalidImg, candyImg;

/* XPM */
static tyImage empty_xpm = {
"16 16 2 1",
"   c None",
".  c #FFFFFF",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................"};

/* XPM */
static tyImage hero_xpm = {
"16 16 3 1",
"   c None",
".  c #FFFFFF",
"+  c #000000",
"................",
"...+++...+++....",
"..+...+.+...+...",
".+.....+.....+..",
".+...+++++...+..",
".+...+++++...+..",
".+...+++++...+..",
".+.....+.....+..",
"..+...+.+...+...",
"...+++...+++....",
"................",
".....+++++......",
"....+.....+.....",
"................",
"................",
"................"};


/* XPM */
static tyImage chaser_xpm = {
"16 16 3 1",
"   c None",
".  c #FFFFFF",
"+  c #000000",
"................",
"...+++...+++....",
"..++.++.+.+++...",
".+..+++++++..+..",
".+...+++++...+..",
".+...+++++...+..",
".+...+++++...+..",
"..+...+.+...+...",
"...+++...+++....",
"................",
"................",
"....+++++++.....",
"................",
"................",
"................",
"................"};

/* XPM */
static tyImage block_xpm = {
"16 16 3 1",
"   c None",
".  c #000000",
"+  c #FFFFFF",
"................",
"................",
"..............+.",
"....+.+.+.+.+...",
"...+.+.+.+.+..+.",
"....+.+.+.+.+...",
"...+.+.+.+.+..+.",
"....+.+.+.+.+...",
"...+.+.+.+.+..+.",
"....+.+.+.+.+...",
"...+.+.+.+.+..+.",
"....+.+.+.+.+...",
"...+.+.+.+.+..+.",
"................",
"..+.+.+.+.+.+.+.",
"................"};

/* XPM */
static tyImage boundary_xpm = {
"16 16 3 1",
"   c None",
".  c #000000",
"+  c #FFFFFF",
"................",
"................",
"..............+.",
"....+.+.+.+.+...",
"...+.+.+.+.+..+.",
"....+.+.+.+.+...",
"...+.+.+.+.+..+.",
"....+.+.+.+.+...",
"...+.+.+.+.+..+.",
"....+.+.+.+.+...",
"...+.+.+.+.+..+.",
"....+.+.+.+.+...",
"...+.+.+.+.+..+.",
"................",
"..+.+.+.+.+.+.+.",
"................"};

/* XPM */
static tyImage invalid_xpm = {
"16 16 2 1",
"   c None",
".  c #FFFFFF",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................",
"................"};

/* XPM */
static tyImage candy_xpm = {
	"16 16 3 1",
"   c None",
".  c #FFFFFF",
"+  c #000000",
"................",
".......++.......",
".......++++.....",
".......++++.....",
".......++.......",
"....+++++++++...",
"..++...++....++.",
"++............++",
"++............++",
"++............++",
"++............++",
".++.........++..",
".++....++...++..",
"...+++...+++....",
"...+++...+++....",
"................"};


/******************************************************************************
 * imagesCreate - Converts all the XPM images to the type Image
 ******************************************************************************/
void imagesCreate(void)
{
	emptyImg = tyCreateImage(empty_xpm);
	heroImg = tyCreateImage(hero_xpm);
	chaserImg = tyCreateImage(chaser_xpm);
	blockImg = tyCreateImage(block_xpm);
	boundaryImg = tyCreateImage(boundary_xpm);
	invalidImg = tyCreateImage(invalid_xpm);
	candyImg = tyCreateImage(candy_xpm);

}


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/* ACTORS */

/******************************************************************************
 * Constants, types and functions for all kinds of actors
 ******************************************************************************/

#define ACTOR_PIXELS_X		16
#define ACTOR_PIXELS_Y		16
#define UPDATE_MONSTER 		12
#define UPDATE_CANDY		2
#define CANDY_RANGE_MOVE	2
#define CHASER_RANGE_MOVE	1


typedef enum {
	EMPTY, HERO, CHASER, BLOCK, BOUNDARY, CANDY
} ActorKind;

typedef struct {
// specific fields can go here, but probably none will be needed
} Hero;

typedef struct {
// specific fields can go here, but probably none will be needed
	int counter;
	bool removed;
} Chaser;

typedef struct {
// specific fields can go here, but probably none will be needed
} Block;

typedef struct {
// specific fields can go here, but probably none will be needed
} Boundary;

typedef struct 
{
// specific fields can go here, but probably none will be needed
	int counter;
} Candy;


typedef struct {
// factored common fields
	ActorKind kind;
	int x, y;
	Image image;
	union {
// specific fields for each kind
		Hero hero;
		Chaser chaser;
		Block block;
		Boundary boundary;
		Candy candy;
	} u;
} ActorStruct, *Actor;

// return x coordinate of actor a 
int actorX(Actor a){
	return a->x;
}

// return y coordinate of actor a 
int actorY(Actor a){
	return a->y;
}



#define WORLD_SIZE_X			31
#define WORLD_SIZE_Y			18
#define N_MONSTERS				5
#define INNER_BLOCKS			110
#define MONSTER_HERO_MIN_DIST	4

typedef struct {
	Actor world[WORLD_SIZE_X][WORLD_SIZE_Y];
	Actor hero;
	Actor monsters[N_MONSTERS];
	Actor candy;
} GameStruct, *Game;

/******************************************************************************
 * actorImage - Get the screen image corresponding to some kind of actor
 ******************************************************************************/
Image actorImage(ActorKind kind)
{
	switch( kind ) {
		case EMPTY:		return emptyImg;
		case HERO:		return heroImg;
		case CHASER:	return chaserImg;
		case BLOCK:		return blockImg;
		case BOUNDARY:	return boundaryImg;
		case CANDY:		return candyImg;
		default:		return invalidImg;
	}
}

/******************************************************************************
 * cellSet - Useful function to update one cell in the matrix and in the screen
 ******************************************************************************/
void cellSet(Game g, Actor a, int x, int y, Image img)
{
	tyDrawImage(img, x * ACTOR_PIXELS_X, y * ACTOR_PIXELS_Y);
	g->world[x][y] = a;	
}

/******************************************************************************
 * isOutSideBoundaries - Useful function to verify if point (x, y) is inside 
 * of game area
 ******************************************************************************/
bool isOutSideBoundaries(int x, int y){
	return x > WORLD_SIZE_X - 1 || y > WORLD_SIZE_Y - 1 || x < 1 || y < 1;
}

/******************************************************************************
 * cellIsEmpty - Check in the matrix if a cell is empty (if contains NULL)
 ******************************************************************************/
bool cellIsEmpty(Game g, int x, int y)
{
	return !isOutSideBoundaries(x, y) && g->world[x][y] == NULL;
}

/******************************************************************************
 * actorShow - Install an actor in the matrix and in the screen
 ******************************************************************************/
void actorShow(Game g, Actor a)
{
	cellSet(g, a, a->x, a->y, a->image);
}

/******************************************************************************
 * actorHide - Removes an actor from the matrix and from the screen
 ******************************************************************************/
void actorHide(Game g, Actor a)
{
	cellSet(g, NULL, a->x, a->y, emptyImg);
}


/******************************************************************************
 * actorMove - Move an actor to a new position
 * pre: the new position is empty
 ******************************************************************************/
void actorMove(Game g, Actor a, int nx, int ny)
{
	actorHide(g, a);
	g->world[a->x][a->y] = NULL;
	a->x = nx;
	a->y = ny;
	g->world[a->x][a->y] = a;
	actorShow(g, a);
}

/******************************************************************************
 * actorNew - Creates a new actor and installs it in the matrix and the screen
 ******************************************************************************/
Actor actorNew(Game g, ActorKind kind, int x, int y)
{
	Actor a = malloc(sizeof(ActorStruct));
	a->kind = kind;
	a->x = x;
	a->y = y;
	a->image = actorImage(kind);
	actorShow(g, a);
	return a;
}

/******************************************************************************
 * isMovable - verify if actor is movable
 ******************************************************************************/
bool isMovable(Actor actor){
	switch(actor->kind){
		case EMPTY:		return true;
		case HERO:		return true;
		case BLOCK:		return true;
		default:		return false;
	}
}


/******************************************************************************
 * canBeKilled - verify if actor a can be killed
 ******************************************************************************/
bool canBeKilled(Actor a ){
	switch(a->kind){
		case HERO:		return true;
		default:		return false;
	}
}


/******************************************************************************
 * moveChaser - checks if can move the chaser and return true. False otherwise
 ******************************************************************************/
bool moveChaser (Game g, Actor a) {
	for(int i = a->x - 1; i <= a->x + 1; i++)
			for(int j = a->y - 1; j <= a->y + 1; j++)
				if(cellIsEmpty(g, i, j) || canBeKilled(g->world[i][j]))
					return true;
		return false;
}

/******************************************************************************
 * moveCandy - checks if can move the candy and return true. False otherwise
 ******************************************************************************/
bool moveCandy(Game g, Actor a) {
	for(int i = a->x - 2; i <= a->x + 2; i++)
			if(cellIsEmpty(g, i, a->y - 2) || cellIsEmpty(g, i, a->y + 2))
				return true;
		for(int j = a->y - 2; j <= a->y + 2; j++)
			if(cellIsEmpty(g,  a->x- 2, j) || cellIsEmpty(g,  a->x + 2, j))
				return true;
		return false;

}

/******************************************************************************
 * canMove - checks if can move an actor.
 ******************************************************************************/
bool canMove(Game g, Actor a){
	switch (a->kind)
	{
	case CHASER: return moveChaser(g,a);
	case CANDY: return moveCandy(g, a);
	default: return false;
	}
}

/******************************************************************************
 * monstersCanMove - verify if all monsters in game g can move in game area
 ******************************************************************************/
bool monstersCanMove(Game g){
	for(int i = 0; i < N_MONSTERS; i++)
		if(!g->monsters[i]->u.chaser.removed && canMove(g, g->monsters[i]))
			return true;
	return false;

}

/******************************************************************************
 * removeActor - remove one actor of type kind
 ******************************************************************************/
void removeActor(Game g, ActorKind kind){
	switch(kind){
		case CANDY:
			if(g->candy != NULL){
				g->world[g->candy->x][g->candy->y] = NULL;
				actorHide(g, g->candy);
				g->candy = NULL;
			}
		break;
		case CHASER:
			for( int i = 0; i < N_MONSTERS; i++){
				Actor monster = g->monsters[i];
				if(!monster->u.chaser.removed && canMove(g, monster)){
					g->world[monster->x][monster->y] = NULL;
					actorHide(g, monster);
					monster->u.chaser.removed = true;
					break;
				}
			}
		break;
		case HERO:
			if(g->hero != NULL){
			actorHide(g, g->hero);
			g->world[g->hero->x][g->hero->y] = NULL;
			g->hero = NULL;
			}

		default:break;
	}
}

/******************************************************************************
 * push - actor a push actor b in dx dy direction
 ******************************************************************************/
bool push(Game g, Actor a, Actor b, int dx, int dy)
{
	if (b == NULL){
		if(isMovable(a) && !isOutSideBoundaries(a->x+dx, a->y+dy)){
			actorMove(g, a, a->x + dx, a->y + dy);
			return true;
		} 
		return false;
	}
	else
	{
		if(!isOutSideBoundaries(b->x+dx, b->y+dy) && isMovable(a) && isMovable(b)){
			bool move = push(g, b, g->world[b->x + dx][b->y + dy], dx, dy);
			if(move){
				actorMove(g, a, a->x + dx, a->y + dy);
				return true;
			}
		}
		return false;
	}
}

/******************************************************************************
 * removeNotGenerous - verify if actor a can remove non generous actor
 ******************************************************************************/
bool removeNotGenerous(Actor a){
	switch(a->kind){
		case CANDY: return true;
		default: return false;
	}
}

/******************************************************************************
 * attack - verify if actor a can attack other actors
 ******************************************************************************/
bool attack(Actor a){
	switch (a->kind)
	{
	case CHASER: return true;
	default: return false;
	}
}
/******************************************************************************
 * heroAnimation - The hero moves using the cursor keys
 ******************************************************************************/
void heroAnimation(Game g, Actor a)
{
	int dx = tyKeyDeltaX(), dy = tyKeyDeltaY();
	if(dx == 0 && dy == 0) return;
	int nx = a->x + dx, ny = a->y + dy;
	if (cellIsEmpty(g, nx, ny))
		actorMove(g, a, nx, ny);
	else if (removeNotGenerous(g->world[nx][ny]))
	{
		removeActor(g, g->world[nx][ny]->kind);
		removeActor(g, CHASER);
	}
	else if (attack(g->world[nx][ny]))
	{
		removeActor(g, a->kind);
		actorMove(g, g->world[nx][ny], nx, ny);
	}
	else
	{
		int x = a->x + dx, y = a->y + dy;
		Actor block = g->world[x][y];
		push(g, a, block, dx, dy);
	}
}

/******************************************************************************
 * isGenerous - verify if actor a is generous
 ******************************************************************************/
bool isGenerous(Actor a){
	if(a == NULL) return false; 
	switch(a->kind){
		case HERO: return true;
		default: return false;
	}
}

/******************************************************************************
 * randxy - generate randomly positive, negative or null base number
 ******************************************************************************/
int randxy(){
	int positive = tyRand(2);
	int add = tyRand(2);
	if(!add)
		return 0;
	else if(positive)
		return 1;
	else 
		return -1;
}


/******************************************************************************
 * chaserAnimation - They move through the free squares, one square at a time, 
 * horizontally, vertically and diagonally in hero direction
 ******************************************************************************/
void chaserAnimation(Game g, Actor a)
{	
	if (a->u.chaser.removed) return;

	if(a->u.chaser.counter == UPDATE_MONSTER){
		a->u.chaser.counter = 0;
		Actor hero = g->hero;
		if(hero == NULL) return;
		int nx = a->x, ny = a->y;

		if(hero->x < a->x)
			nx = a->x - CHASER_RANGE_MOVE;
		else if(hero->x > a->x )
			nx = a->x + CHASER_RANGE_MOVE;

		if(hero->y < a->y )
			ny = a->y - CHASER_RANGE_MOVE;
		else if(hero->y > a->y )
			ny = a->y + CHASER_RANGE_MOVE;

		Actor ac = g->world[nx][ny];
		if(isGenerous(ac)){
			removeActor(g, ac->kind);
			actorMove(g, a, nx, ny);
		}else if (cellIsEmpty(g, nx, ny))
			actorMove(g, a, nx, ny);
		else if(cellIsEmpty(g, nx, a->y))
			actorMove(g, a, nx, a->y);
		else if(cellIsEmpty(g, a->x, ny))
			actorMove(g, a, a->x, ny);
		else{
			int dx = 0,dy = 0;
			dx = randxy()*CHASER_RANGE_MOVE;
			dy = randxy()*CHASER_RANGE_MOVE;
			if (cellIsEmpty(g, a->x+dx, a->y+dy) )
				actorMove(g, a, a->x+dx, a->y+dy);
		}
		
	}else 
		a->u.chaser.counter++;
}

/******************************************************************************
 * distance - Calculates the distance between actor a and actor b 
 ******************************************************************************/
int distance(Actor a, Actor b){
	return tyDistance(a->x, a->y, b->x, b->y);
}

/******************************************************************************
 * candyAnimation - The candy runs from hero 
 ******************************************************************************/
void candyAnimation(Game g, Actor a) {
	if (a->u.candy.counter == UPDATE_CANDY)
	{
		a->u.candy.counter = 0;
		Actor hero = g->hero;

		if (hero == NULL)
			return;

		int nx = a->x, ny = a->y;
		if (hero->x > a->x)
			nx = a->x - CANDY_RANGE_MOVE;
		else if (hero->x < a->x)
			nx = a->x + CANDY_RANGE_MOVE;
		else if(hero->x == a->x)
			if(a->x + CANDY_RANGE_MOVE > WORLD_SIZE_X - 1)
				nx = a->x - CANDY_RANGE_MOVE;
			else
				nx = a->x + CANDY_RANGE_MOVE;

		if (hero->y > a->y)
			ny = a->y - CANDY_RANGE_MOVE;
		else if (hero->y <= a->y)
			ny = a->y + CANDY_RANGE_MOVE;
		else if(hero->y == a->y)
			if(a->y + CANDY_RANGE_MOVE > WORLD_SIZE_Y - 1)
				ny = a->y - CANDY_RANGE_MOVE;
			else
				ny = a->y + CANDY_RANGE_MOVE;

		if (cellIsEmpty(g, nx, ny))
			actorMove(g, a, nx, ny);
		else if(cellIsEmpty(g, nx, a->y))
			actorMove(g, a, nx, a->y);
		else if(cellIsEmpty(g, a->x, ny))
			actorMove(g, a, a->x, ny);
		else{
			int dx = 0,dy = 0;
			dx = randxy()*CANDY_RANGE_MOVE;
			dy = randxy()*CANDY_RANGE_MOVE;
			if (cellIsEmpty(g, a->x+dx, a->y+dy) && distance(a, g->hero) > 2)
				actorMove(g, a, a->x+dx, a->y+dy);
		}

	}
	else
		a->u.candy.counter++;
}


/******************************************************************************
 * actorAnimation - The actor behaves according to its kind
 ******************************************************************************/
void actorAnimation(Game g, Actor a)
{
	if(a == NULL) return;
	switch( a->kind ) {
		case HERO: heroAnimation(g, a); break;
		case CHASER: chaserAnimation(g,a);break;
		case CANDY: candyAnimation(g,a); break;
		default: break;
	}
}


/******************************************************************************
 * heroIsAlive - verify if hero is alive
******************************************************************************/
bool heroIsAlive(Game g){
	return g->hero != NULL;
}

/******************************************************************************
 * validDist - verify if the actor of kind kind is in a valid distane from
 * monsters
 ******************************************************************************/
bool validDist(Game g, ActorKind kind,  int x, int y ){
	switch(kind){
		case HERO:
			for(int i = 0; i < N_MONSTERS; i++){
				if(!g->monsters[i]->u.chaser.removed && 
				tyDistance(x,y,actorX(g->monsters[i]),actorY(g->monsters[i])) 
				< MONSTER_HERO_MIN_DIST)
				return false;
			}
			return true;
			break;
		default: return false;
	}
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/* GAME */

/******************************************************************************
 * gameClearWorld - Clears the matrix and the screen
 ******************************************************************************/
void gameClearWorld(Game g)
{
	for(int y = 0; y < WORLD_SIZE_Y ; y++)
		for(int x = 0; x < WORLD_SIZE_X ; x++ )
			cellSet(g, NULL, x, y, emptyImg);
}

/******************************************************************************
 * gameInstallBoundaries - Install the boundary blocks
 ******************************************************************************/
void gameInstallBoundaries(Game g)
{
	for(int y = 0; y < WORLD_SIZE_Y ; y++)
		for(int x = 0; x < WORLD_SIZE_X ; x++)
			if( x == 0 || x == WORLD_SIZE_X - 1
			|| y == 0 || y == WORLD_SIZE_Y - 1 ) {
				actorNew(g, BOUNDARY, x, y);
			}
}

/******************************************************************************
 * gameInstallBlocks - Install the movable blocks
 ******************************************************************************/
void gameInstallBlocks(Game g)
{
	int x, y;
	for(int i = 0; i < INNER_BLOCKS ; i++){
		do{
			x = tyRand(WORLD_SIZE_X-1) + 1;
		    y = tyRand(WORLD_SIZE_Y-1) + 1;
		} while(!cellIsEmpty(g, x, y));
		Actor block = actorNew(g, BLOCK, x, y);
		g->world[x][y] = block;
	}
}

/******************************************************************************
 * gameInstallMonsters - Install the monsters
 ******************************************************************************/
void gameInstallMonsters(Game g)
{
	int x, y;
	for(int i = 0; i < N_MONSTERS ; i++){
		do{
			x = tyRand(WORLD_SIZE_X-1) + 1;
		    y = tyRand(WORLD_SIZE_Y-1) + 1;
		} while(!cellIsEmpty(g, x, y));
		Actor monster = actorNew(g, CHASER, x, y);
		monster->u.chaser.counter = 0;
		monster->u.chaser.removed = false;
		g->monsters[i]= monster;
		g->world[x][y] = monster;
	}
}

/******************************************************************************
 * gameInstallHero - Install the hero
 ******************************************************************************/
void gameInstallHero(Game g)
{
	int x, y;
	do{
		x = tyRand(WORLD_SIZE_X-1) + 1;
		y = tyRand(WORLD_SIZE_Y-1) + 1;
	} while(!cellIsEmpty(g, x, y) || !validDist(g, HERO, x, y));
    g->hero = actorNew(g, HERO, x, y);
	g->world[x][y] = g->hero;
}

/******************************************************************************
 * gameInstallCandy - Install the candy
 ******************************************************************************/
void gameInstallCandy(Game g)
{
	int x,y;
	do{
		x = tyRand(WORLD_SIZE_X-CANDY_RANGE_MOVE-1) + CANDY_RANGE_MOVE;
		y = tyRand(WORLD_SIZE_Y-CANDY_RANGE_MOVE-1) + CANDY_RANGE_MOVE;
	} while(!cellIsEmpty(g, x, y));
	g->candy = actorNew(g,CANDY,x,y);
	g->world[x][y] = g->candy;
	g->candy->u.candy.counter=0;
}

/******************************************************************************
 * gameInit - Initialize the matrix and the screen
 ******************************************************************************/
Game gameInit(Game g)
{
	if (g == NULL)
		g = malloc(sizeof(GameStruct));
	imagesCreate();
	gameClearWorld(g);
	gameInstallBoundaries(g);
	gameInstallBlocks(g);
	gameInstallMonsters(g);
	gameInstallHero(g);
	gameInstallCandy(g);
	return g;
}

/******************************************************************************
 * gameRedraw - Redraws the entire scenario. This function is called by
 * tyHandleRedraw in very specific circumstances. It should not be used anywhere
 * else because you don't want to be constantly redrawing the whole scenario.
 ******************************************************************************/
void gameRedraw(Game g)
{
	for(int y = 0; y < WORLD_SIZE_Y; y++)
		for(int x = 0; x < WORLD_SIZE_X; x++) {
			Actor a = g->world[x][y];
			if( !cellIsEmpty(g, x, y) )
				actorShow(g, a);
		}
}


/******************************************************************************
 * gameAnimation - Sends animation events to all the animated actors
 * This function is called every tenth of a second (more or less...)
******************************************************************************/
void gameAnimation(Game g) {
	if(!heroIsAlive(g)){
		deadMessage();
	}
	else if (!monstersCanMove(g))
	{
		winMessage();
	}else{
		actorAnimation(g, g->hero);
		actorAnimation(g, g->candy);
		for(int i = 0 ; i < N_MONSTERS ; i++)
			actorAnimation(g, g->monsters[i]);	
	}
}


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/* STATUS BAR */

/******************************************************************************
 * The function status populates the status bar, at the bottom of the window
 ******************************************************************************/

#define STATUS_ITEMS	5

void status(void)
{
	String s;
	sprintf(s, "TIME = %d seg.", tySeconds());
	tySetStatusText(4, s);
}



/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/* MENU COMMANDS */

/******************************************************************************
 * Each function handles one menu command
 ******************************************************************************/

void comandAbout(void)
{
	tyAlertDialog("About", "%s\n%s\n\n%s\n%s",
		APP_NAME,
		"(Reimplementation of the original game of Chuck Shotton)",
		AUTHOR1,
		AUTHOR2);
}

void deadMessage(){
	tyAlertDialog("", "Dead Meat!!!");
	comandRestart();
}

void winMessage(){
	tyAlertDialog("", "You Win!!!");
	comandRestart();
}

void comandRestart(void)
{
	tyHandleStart();
}

void comandFinish(void)
{
	tyAlertDialog("Quit", "See you later!");
	tyQuit();
}


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/


/* FUNCTIONS REQUIRED BY THE FRAMEWORK wxTiny */

/******************************************************************************
 * Section with all the "root" "functions required by the wxTiny support system. 
 * 
 * There is no function "main" in a wxTiny program, as the main function is
 * hidden within the wxTiny library. The most important thing you need to know
 * is that the function "tyHandleStart" is called when the program begins,
 * and that function "tyHandleTime" is called periodically 10 times per second,
 * to make the program progress. In some sense, both this function make a kind
 * of main function.
 * 
 * More information about the wxTiny functions in the file "wxTiny.h".
 ******************************************************************************/

static Game game = NULL; // defined here to be available to the "root" functions

/****************************************************************************** 
 * tyAppName - specify the name of the app
 ******************************************************************************/
tyStr tyAppName(void)
{
	return APP_NAME;
}

/****************************************************************************** 
 * tyWidth - specify the width of the window
 ******************************************************************************/
int tyWidth(void)
{
	return WORLD_SIZE_X * ACTOR_PIXELS_X;
}

/****************************************************************************** 
 * tyHeight - specify the height of the window
 ******************************************************************************/
int tyHeight(void)
{
	return WORLD_SIZE_Y * ACTOR_PIXELS_Y;
}

/****************************************************************************** 
 * tyStatusItems - specify the number of slots available in the status bar
 ******************************************************************************/
int tyStatusItems(void)
{
	return STATUS_ITEMS;
}

/****************************************************************************** 
 * tyMenus - specify the menus
 ******************************************************************************/
tyStr tyMenus(void)
{
	return ":+Menu"
			":&About\tCtrl-A"
			":-"
			":&Restart\tCtrl-R"
			":-"
			":&Quit\tCtrl-Q";
}

/****************************************************************************** 
 * tyHandleMenuCommand - Handles the menu commands
 ******************************************************************************/
void tyHandleMenuCommand(tyStr command)
{
	if( strcmp(command, "About") == 0 )
		comandAbout();
	else if( strcmp(command, "Restart") == 0 )
		comandRestart();
	else if( strcmp(command, "Quit") == 0 )
		comandFinish();
	else
		tyFatalError("Unknown command: \"%s\"", command);
}

/****************************************************************************** 
 * tyHandleRedraw - redraws the window
 *
 * Automatically called in rare situations, for example if the game window is
 * minimized and then maximized
 ******************************************************************************/
void tyHandleRedraw(void)
{
	gameRedraw(game);
}

/****************************************************************************** 
 * tyHandleTime - Called periodically, around 10 time per second
 * 
 * This function does the following: animate the actors; update the status bar;
 *	possibly more things
 ******************************************************************************/
void tyHandleTime(void)
{
	status();
	gameAnimation(game);
}

/****************************************************************************** 
 * tyHandleStart - Program initialization
 ******************************************************************************/
void tyHandleStart(void)
{
	tySecondsSetZero();
	tySetSpeed(5);
	game = gameInit(game);
}
