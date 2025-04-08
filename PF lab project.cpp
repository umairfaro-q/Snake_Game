#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std ;

void gotoxy( short int , short int ) ;
void Border() ;
void Draw() ;
void Input() ;
void Setup() ;
void Logic() ;
void Replay() ;

bool gameOver ;
char name[10] ;
const int width = 20 , height = 20 ;
int x , y , fruitX , fruitY , score , choice , tailX[100], tailY[100] , nTail ;
enum eDirecton { STOP = 0 , LEFT , RIGHT , UP , DOWN } ;
eDirecton dir ;

int main()
{
	system("cls"); //clear screen
	//game startup
		Setup() ;
    //game 
		while ( !gameOver ) 
	    {
	        Draw() ; 
	    	Border() ;    
			Input() ;
	        Logic() ; 
	    }
    //ask for replay
    Replay() ;
    
    return 0 ;
    
}

void gotoxy( short int a , short int b )
{
	COORD V = { a , b } ;
	SetConsoleCursorPosition ( GetStdHandle ( STD_OUTPUT_HANDLE ) , V ) ;
}

void Replay() //end game screen and ask to replay
{
	Border() ;
	gotoxy(17,3) ;
    	cout<<"Game End";
    gotoxy(13,6) ; 
		cout<<"Hi!" ;
    gotoxy(16,7) ; 
		cout<<name ;
    gotoxy(13,8) ; 
		cout<<"Your Score is "<<score ;
    gotoxy(11,19) ;	
		cout<<"Press Any key to Exit " ;
	gotoxy(11,20) ; 
		cout<<"and 'Y' to play again " ;
    char play = getch() ;
    if( play == 'Y' || play == 'y')
    { 
		main() ;
	}
}

void Border() //border to game 
{
	gotoxy(0,1) ;
	for (int i = 0; i < width+2; i++)
        cout << "# " ;
    cout << endl ;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if ( j == 0 ) 
                cout << "# " ;
        	cout << "  ";
            if ( j == width - 1 )
                cout << "#" ;
        }
        cout << endl ;
    }
    for ( int i = 0 ; i < width+2 ; i++ )
        cout << "# " ;
    cout << endl ;
}

void Draw()
{
	
	//score bar
		gotoxy(16,0) ;
		cout << "Score : " << score << endl ;
	//game play area
	gotoxy(0,2) ; 
    for ( int i = 0 ; i < height ; i++ )
    {
        for ( int j = 0 ; j < width ; j++ )
        {
        	if ( j == 0 )
                cout << "# " ;
            if ( i == y && j == x )
                cout << "@ " ;
            else if ( i == fruitY && j == fruitX )
                cout << "o " ;
            else
            {
                bool print = false ;
                for ( int k = 0 ; k < nTail ; k++ ) 
                {
                    if ( tailX[k] == j && tailY[k] == i )
                    {
                        cout << "* " ;
                        print = true ;
                    }
                }
                if ( !print )
                {
                	cout << "  " ;
				}
   			}
       }
        cout << endl ;
    }
    gotoxy(0,25) ;
    Sleep(70) ; //speed control 
}

void Input() //input from user to change snake direction
{
    if (_kbhit())
    {
        switch (_getch())
        {
		    case 'a' :
		        dir = LEFT ;
		        break ;
		    case 'd' :
		        dir = RIGHT ;
		        break ;
		    case 'w' :
		        dir = UP ;
		        break ;
		    case 's' :
		        dir = DOWN ;
		        break ;
		    case ' ' :
		        gameOver = true ;
		        break ;
        }
    }
}

void Setup()
{
	//startup initialize
		nTail = 0 ;
		score = 0 ;
	    gameOver = false ;
	    dir = STOP ;
	    x = width / 2 ;
	    y = height / 2 ;
	    fruitX = rand() % width ;
	    fruitY = rand() % height ;  
    //name 
	    Border() ;
	    gotoxy( 6 , 6 ) ;
		cout << "Enter your name : " ;
		gets(name);
	//choice
		Border() ;
		gotoxy(4,6) ;
			cout << "Enter choice ( default : Regular ) :";
		gotoxy(8,7) ;
			cout << "1. Regular";
		gotoxy(8,8) ;
			cout << "2. Bordered";
		gotoxy(11,9) ;
			choice = getch() ; 
	//note
		Border();
		gotoxy(5,5) ; 
			cout<<"Note:" ; 
		gotoxy(9,6) ; 
			cout<<"Use W,A,S & D keys to " ;
		gotoxy(9,7) ; 
			cout<<"move and space to exit" ;
		gotoxy(10,15) ;	
			cout<<"Press 'Y' to Start " ;
		char z = getch() ;
		if( z == 'Y' || z == 'y' ) 
		{
			 	
		}
		else
		{
			Replay() ;	
		}
}

void Logic()
{
    int prevX = tailX[0] ;
    int prevY = tailY[0] ;
    int prev2X, prev2Y ;
    tailX[0] = x ;
    tailY[0] = y ;
    
	for ( int i = 1 ; i < nTail ; i++ )
    {
        prev2X = tailX[i] ;
        prev2Y = tailY[i] ;
        tailX[i] = prevX ;
        tailY[i] = prevY ;
        prevX = prev2X ;
        prevY = prev2Y ;
    }
    //movement of snake
	    switch (dir)
	    {
		    case LEFT :
		        x-- ;
		        break ;
		    case RIGHT :
		        x++ ;
		        break ;
		    case UP :
		        y-- ;
		        break ; 
		    case DOWN :
		        y++ ;
		        break ;
		    default :
		        break ;
	    }
    //bordered or regular
	    switch ( choice )
	    {
	    	case '1' :
	    		//regular
	    		if (x >= width) 
				{
					x = 0 ;
				} 
				else if (x < 0) 
				{
					x = width - 1 ;
				}
				
			    if (y >= height) 
				{
					y = 0 ;
				} 
				else if (y < 0) 
				{
					y = height - 1 ;
				}
				break ;
	    	case '2' :
	    		//bordered
				if (x > width || x < 0 || y > height || y < 0)
				{
					gameOver = true;
				}
				break ;
	    	default :
	    		//regular
	    		if (x >= width) 
				{
					x = 0 ;
				} 
				else if (x < 0) 
				{
					x = width - 1 ;
				}
				
			    if (y >= height) 
				{
					y = 0 ;
				} 
				else if (y < 0) 
				{
					y = height - 1 ;
				}
	    		break ;
		}	
	//tail collusion
	    for ( int i = 0 ; i < nTail ; i++ )
	    {
	    	if ( tailX[i] == x && tailY[i] == y ) 
	        {
	        	gameOver = true ;
			}
		}
	//add tail
	    if ( x == fruitX && y == fruitY )
	    {
	        score += 10 ;
	        fruitX = rand() % width ;
	        fruitY = rand() % height ;
	        nTail++ ;
	    }
}