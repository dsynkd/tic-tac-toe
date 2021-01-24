// MAKE SURE TO CHECK GRAPHICS LIBRARY IN Options > Linker > Libraries
// ALSO THE TC PATH HAS TO BE MOUNTED IN D:\TC, alternative change the path of BGI library in source code Launch() > initgraph()
/* the idea behind difficulty is that level 1 just plays randomly
** level 2 always blocks your winning move, even if it has a winning move
** level 3 plays perfectly
** But this is not currently implemented correctly...
*/

#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

void Launch();
void HardPlay();
int isFull(int a, int b, int c);
void XPrint(char text[]);
int getPosition(char pos);
int isTaken(int pos);
void draw(int xPos, int yPos);
void drawChart(int sXPos, int sYPos);
void randSidePlay();
void checkWin();
void rematch();
void Hooray(int winner);
void clearPositions();
int humanGame();
int AIGame();
void AIPlay();
void randomSentence();
void randomPlay();
int almostFull(int a, int b);
char toChar(int num);

int positions[9];
int re = 0;
int turn = 0;
int end = 0;
char dif = 0;
char mode;
const int DELAY = 1;
const int DIS = 150;
const int sXPos = 175;
const int sYPos = 25;

int main() {
    clrscr();
    if(!re) {
	XPrint("<<<THE INVINCIBLE TIC-TAC-TOE PROGRAM>>>\nWRITTEN BY V0R73X IN C...\n");
	XPrint("In Order To See The Instructions, Press 'i', To Start The Game, Press Any Other Keys...");
	char tch = getche();
	if(tch=='i') {
	    XPrint("\nINSTRUCTIO0NS:\nWHEN ASKED TO ENTER A POSITION,\nENTER:\n");
	    XPrint("1 FOR THE TOP, LEFT CELL\n2 FOR THE TOP, MIDDLE CELL\n3 FOR THE TOP, RIGHT CELL");
	    XPrint("\n4 FOR THE MIDDLE, LEFT CELL\n5 FOR THE CENTERAL CELL\n6 FOR THE MIDDLE, RIGHT CELL");
	    XPrint("\n7 FOR THE BUTTOM, LEFT CELL\n8 FOR THE BUTTON, MIDDLE CELL\n9 FOR THE BUTTON, RIGHT CELL\n");
	    XPrint("Player 1 = Red Circle\n");
	    XPrint("Player 2 = Blue Cross\n");
	    XPrint("Press Any Keys To Start The Game...");
	    getch();
	}
    }
    clrscr();
    Launch();
    int temp;
	choosemode:
    XPrint("\nAVAILABLE MODES:\n1 = AI VS YOU!\n2 = YOU VS YOU!\nCHOOSE MODE:");
    mode = getch();
    putchar(mode);
	difficulty:
    if(mode=='1') {
	XPrint("\nChoose difficulty from 1-3:");
	dif = getch();
	putchar(dif);
	if(dif>'4'||dif<'1') goto difficulty;
	temp = AIGame();
    } else if(mode =='2') {
	temp = humanGame();
    } else {
	XPrint("\nMode Not Available!");
	goto choosemode;
    }
    return 0;
}

void AIPlay() {
    if((almostFull(2,3)||almostFull(5,9)||almostFull(4,7))&&positions[0]==0)
	getPosition('1');
    else if((almostFull(1,3)||almostFull(5,8))&&positions[1]==0)
	getPosition('2');
    else if( (almostFull(1,2)||almostFull(7,5)||almostFull(6,9)) && positions[2]==0)
	getPosition('3');
    else if((almostFull(5,6)||almostFull(1,7))&&positions[3]==0)
	getPosition('4');
    else if((almostFull(1,9)||almostFull(2,8)||almostFull(3,7)||almostFull(4,6))&&positions[4]==0)
	getPosition('5');
    else if((almostFull(5,4)||almostFull(3,9))&&positions[5]==0)
	getPosition('6');
    else if((almostFull(1,4)||almostFull(5,3)||almostFull(8,9))&&positions[6]==0)
	getPosition('7');
    else if((almostFull(7,9)||almostFull(5,2))&&positions[7]==0)
	getPosition('8');
    else if((almostFull(3,6)||almostFull(8,7)||almostFull(1,5))&&positions[8]==0)
	getPosition('9');
    else if(dif>'1')
	if(positions[0]==2&&positions[8]==2||positions[2]==2&&positions[6]==2) {
	    randSidePlay();
	} else {
	    randomPlay();
	} else
	randomPlay();
}

void randomPlay() {
    randomize();
    int rand;
	rand:
    if(!positions[4]) {
        getPosition('5');
    } else {
        rand = random(10);
        if(!(positions[0]&&positions[2]&&positions[4]&&positions[6]&&positions[8]))
            if(rand%2==0) goto rand;
	if(positions[rand-1]) goto rand;
        getPosition(toChar(rand));
    }
}

void randSidePlay() {
    randomize();
    int rand1;
	randSide:
    rand1 = random(9);
    if(!(positions[1]&&positions[3]&&positions[5]&&positions[7])) {
        if(rand1%2==1||rand1==0) goto randSide;
        if(positions[rand1-1]) goto randSide;
        printf("Position:%i",rand1);
        getPosition(toChar(rand1));
    } else {
	printf("ALL TAKEN!");
	randomPlay();
    }
}

char toChar(int num) {
    if(num==1)
	return '1';
    else if(num==2)
	return '2';
    else if(num==3)
	return '3';
    else if(num==4)
        return '4';
    else if(num==5)
        return '5';
    else if(num==6)
        return '6';
    else if(num==7)
        return '7';
    else if(num==8)
        return '8';
    else if(num==9)
        return '9';
    return '1';
}

int AIGame() {
    int x,result;
    for(x=0; x<5; x++) {
    getpos:
	if(end) return 0;
	XPrint("\nEnter Position:");
	result=getPosition(getche());
	if(result==1) {
            XPrint("\nInvalid Entry!");
            goto getpos;
        }
        if(result==2) {
            XPrint("\nCell Already Taken!");
            goto getpos;
        }
        checkWin();
        if(x!=4)
	    AIPlay();
	checkWin();
    }
    XPrint("\nThe Result Is A DRAW!\n");
    rematch();
    return 0;
}

int humanGame() {
    int x,result;
    for(x=0; x<9; x++) {
    getpos:
	if(end) return 0;
	XPrint("\nPlayer ");
	printf("%i:", turn%2+1);
	result=getPosition(getche());
	if(result==1) {
	    XPrint("\nInvalid Entry!");
	    goto getpos;
	}
	if(result==2) {
	    XPrint("\nCell Already Taken!");
	    goto getpos;
	}
	checkWin();
    }
    XPrint("\nThe Result Is A DRAW!\n");
    rematch();
    return 0;
}

void Launch() {
    int t,driver,mode;
    driver = DETECT;
    mode =0;
    initgraph(&driver, &mode,"D:\\TC\\BGI");
    setbkcolor(BLACK);
    setcolor(LIGHTGREEN);
    drawChart(sXPos, sYPos);
}

void XPrint(char text[]) {
    clock_t lastclock;
    int i=0;
    while(i<strlen(text)) {
        lastclock = clock();
	while((clock()-lastclock)<DELAY) {}
        printf("%c",text[i]);
        i++;
    }
}

void drawChart(int sXPos, int sYPos) {
    int distance = DIS *3;
    line(sXPos,sYPos+ DIS,sXPos + distance,sYPos+DIS);
    line(sXPos,sYPos+ DIS*2, sXPos + distance, sYPos + DIS*2);
    line(sXPos+DIS,sYPos,sXPos+DIS,sYPos+distance);
    line(sXPos + DIS*2,sYPos,sXPos + DIS*2,sYPos+distance);
}

void draw(int xPos, int yPos) {
    int distance=DIS/2;
    if(turn++%2==0) {
        setcolor(LIGHTRED);
        circle(xPos,yPos,distance-5);
    } else {
	setcolor(LIGHTBLUE);
        line(xPos-distance,yPos-distance,xPos+distance,yPos+distance);
        line(xPos-distance,yPos+distance,xPos+distance,yPos-distance);
    }
}

int getPosition(char pos) {
    if(mode=='1'&&turn%2==1) {
        XPrint("\nV0R73X: ");
        randomSentence();
    } else {
        printf("%c",pos);
    }
    switch(pos) {
    case('1'):
        if(positions[0])
            return 2;
        else
            draw(sXPos+DIS/2,sYPos+DIS/2);
        positions[0]=positions[0]+1+(turn%2);
	break;
    case('2'):
	if(positions[1])
	    return 2;
	else
	    draw(sXPos+DIS+DIS/2,sYPos+DIS/2);
	positions[1]=positions[1]+1+(turn%2);
	break;
    case('3'):
	if(positions[2])
	    return 2;
	else
	    draw(sXPos+DIS+DIS+DIS/2,sYPos+DIS/2);
	positions[2]=positions[2]+1+(turn%2);
	break;
    case('4'):
	if(positions[3])
	    return 2;
	else
	    draw(sXPos+DIS/2,sYPos+DIS+DIS/2);
	positions[3]=positions[3]+1+(turn%2);
	break;
    case('5'):
	if(positions[4])
	    return 2;
	else
	    draw(sXPos+DIS+DIS/2,sYPos+DIS+DIS/2);
	positions[4]=positions[4]+1+(turn%2);
	break;
    case('6'):
	if(positions[5])
	    return 2;
	else
	    draw(sXPos+DIS+DIS+DIS/2,sYPos+DIS+DIS/2);
	positions[5]=positions[5]+1+(turn%2);
	break;
    case('7'):
	if(positions[6])
	    return 2;
	else
	    draw(sXPos+DIS/2,sYPos+DIS+DIS+DIS/2);
	positions[6]=positions[6]+1+(turn%2);
	break;
    case('8'):
	if(positions[7])
	    return 2;
	else
	    draw(sXPos+DIS+DIS/2,sYPos+DIS+DIS+DIS/2);
	positions[7]=positions[7]+1+(turn%2);
	break;
    case('9'):
	if(positions[8])
	    return 2;
	else
	    draw(sXPos+DIS+DIS+DIS/2,sYPos+DIS+DIS+DIS/2);
	positions[8] = positions[8]+1+(turn%2);
	break;
    case('q'):
	end = 1;
	break;
    default:
	return 1;
    }
    return 0;
}

void clearPositions() {
    for(int i = 0; i<9; i++) {
        positions[i]=0;
    }
}

void Hooray(int winner) {
    if(winner) {
        if(mode=='1'&&winner==2) {
            XPrint("MuHaHaHaHa!!! You Lost! \nNO ONE DEFEATS V0R73X!\n");
        } else if(mode=='1'&&winner==1) {
            XPrint("\nNO! NO! \nI CAN'T LOSE TO SOMEONE AS WEAK AS YOU!!\nYOU ARE ONLY A MERE HUMAN! \nI... ...\nV0R73X Is Shut Down!\n");
        } else {
            XPrint("\nPlayer ");
            printf("%i",winner);
            XPrint(" Won The Game!\n");
        }
        rematch();
    }
}

void rematch() {
    XPrint("Rematch?(y/n)");
    char tempchar = getch();
    if(tempchar=='y') {
        clearPositions();
        turn = 0;
        re = 1;
        closegraph();
        main();
    } else {
        exit(0);
    }
}

void checkWin() {
    Hooray(isFull(1,2,3));
    Hooray(isFull(4,5,6));
    Hooray(isFull(7,8,9));
    Hooray(isFull(1,4,7));
    Hooray(isFull(2,5,8));
    Hooray(isFull(3,6,9));
    Hooray(isFull(1,5,9));
    Hooray(isFull(3,5,7));
}

int isFull(int a, int b, int c) {
    if(positions[a-1]==1&&positions[b-1]==1&&positions[c-1]==1)
        return 2;
    if(positions[a-1]==2&&positions[b-1]==2&&positions[c-1]==2)
        return 1;
    return 0;
}

int almostFull(int a, int b) {
    if(dif<'3') {
        if(positions[a-1]==1&&positions[b-1]==1)
            return 1;
        if(positions[a-1]==2&&positions[b-1]==2)
            return 1;
    } else {
        if(positions[a-1]==2&&positions[b-1]==2)
            return 1;
        else
            return 0;
    }
    return 0;
}

void randomSentence() {
    randomize();
    int n = random(9);
    switch(n) {
    case(0):
        XPrint("U Can't Beat V0R73X!");
        break;
    case(1):
        XPrint("V0R73X Is Invincible!");
        break;
    case(2):
        XPrint("Nice Move, But... BOOM!");
        break;
    case(3):
        XPrint("Good, keep playing...");
        break;
    case(4):
        XPrint("Your Persistance Is Just Natural");
        break;
    case(5):
        XPrint("Now It's MY TURN!");
        break;
    case(6):
        XPrint("Yeah, And What Else?!");
        break;
    case(7):
        XPrint("EXACTLY AS PLANNED!");
        break;
    case(8):
        XPrint("TIME TO DIE, LOSER!");
        break;
    }
}
