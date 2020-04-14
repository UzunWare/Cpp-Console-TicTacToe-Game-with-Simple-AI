#include <iostream>
#include <string>
#include <vector>

using namespace std;

//global constants
const	char	X = 'X'; 
const	char	O = 'O'; 
const	char	EMPTY = ' '; 
const	char	TIE = 'T'; 
const	char	NO_ONE = 'N';

//	function	prototypes 
void instructions();
char askYesNo(string question);
int	askNumber(string question,int high,int low = 0); 
char humanPiece(); 
char opponent(char piece); 
void displayBoard(const	vector<char>& board); 
char winner(const vector<char>&	board); 
bool isLegal(const vector<char>& board,int move); 
int	humanMove(const	vector<char>& board,char human); 
int computerMove(vector<char> board,char computer); 
void announceWinner(char winner,char computer,char human);

int main()
{
	int move;
	const int NUMSQUARES = 9;
	vector<char> board(NUMSQUARES,EMPTY);

	instructions(); 
	char human = humanPiece();
	char computer = opponent(human);
	char turn = X;
	
	displayBoard(board);

	while (winner(board) == NO_ONE)
	{
		if (turn == human)
		{
			move = humanMove(board,human);
			board[move] = human;
		}
		else
		{
			move = computerMove(board,computer);
			board[move] = computer;
		}
		
		displayBoard(board);
		turn = opponent(turn);
	}

	announceWinner(winner(board),computer,human);
	
	return 0;
}

void instructions()
{
	cout << "Welcome to the ultimate man-machine showdown: Tic-Tac-Toe.\n";
	cout << "--where human brain is pit against silicon processor\n\n";
	cout << "Make your move known by entering a number, 0 - 8. The number\n";
	cout << "corresponds to the desired board position, as illustrated:\n\n";
	cout << "0 | 1 | 2\n";
	cout << "---------\n";
	cout << "3 | 4 | 5\n";
	cout << "---------\n";
	cout << "6 | 7 | 8\n\n";

	cout << "Prepare yourself, human. The battle is about to begin.\n\n";
}

int	askNumber(string question, int high, int low)
{
	int move;	
	do
	{
		cout << question << " (" << low << " - " << high << "): ";
		cin >> move;
	}while (move < low || move > high);

	return move;
}

char humanPiece()
{
	char go_first = askYesNo("Do you require the first move?");
	if (go_first == 'y')
	{
		cout << "\nThen take the first move. You will need it.\n";
		return X;
	}
	else
	{
		cout << "\nYour bravery will be your undoing... I will go first.\n";
		return O;
	}
}

char opponent(char piece)
{
	if (piece == 'X')
	{
		return O;
	}
	else
	{
		return X;
	}
}

char askYesNo(string question)
{
	char response;
	do
	{
		cout << question << " (y/n): ";
		cin >> response;
	} while (response != 'y' && response != 'n');

	return response;
}

void displayBoard(const	vector<char>& board)
{
	cout << "\n\t" << board[0] << " | " << board[1] << " | " << board[2];
	cout << "\n\t" << "---------";
	cout << "\n\t" << board[3] << " | " << board[4] << " | " << board[5];
	cout << "\n\t" << "---------";
	cout << "\n\t" << board[6] << " | " << board[7] << " | " << board[8];
	cout << "\n\n";
}

char winner(const vector<char>&	board)
{
	char win;


		//vertically
	if (board[0] != EMPTY && (board[0] == board[1]) && (board[1] == board[2]))
		{
			win = board[0];
		}
	else if (board[3] != EMPTY && (board[3] == board[4]) && (board[4] == board[5]))
		{
			win = board[3];
		}
	else if (board[6] != EMPTY && (board[6] == board[7]) && (board[7] == board[8]))
		{
			win = board[6];
		}

		//horizontally
	else if (board[0] != EMPTY && (board[0] == board[3]) && (board[3] == board[6]))
		{
			win = board[0];
		}
	else if (board[1] != EMPTY && (board[1] == board[4]) && (board[4] == board[7]))
		{
			win = board[1];
		}
	else if (board[2] != EMPTY && (board[2] == board[5]) && (board[5] == board[8]))
		{
			win = board[2];
		}

		//diagnolly
	else if (board[0] != EMPTY && (board[0] == board[4]) && (board[4] == board[8]))
		{
			win = board[0];
		}
	else if (board[2] != EMPTY && (board[2] == board[4]) && (board[4] == board[6]))
		{
			win = board[2];
		}
		else
		{
			bool found = false;
			for (int i = 0; i < 9; i++)
			{
				if (board[i] == EMPTY)
				{
					found = true;
					break;
				}
			}

			if (found)
			{
				win = NO_ONE;
			}
			else
			{
				win = TIE;
			}
		}

	
	return win;
}

bool isLegal(const vector<char>& board, int move)
{
	return board[move] == EMPTY;
}

int	humanMove(const	vector<char>& board, char human)
{
	int move = askNumber("Where will you move?", (board.size() - 1));
	while (!isLegal(board,move))
	{
		cout << "\nThat square is already occupied, foolish human.\n";
		move = askNumber("Where will you move?", (board.size() - 1));
	}

	cout << "Fine...\n";

	return move;
}

int computerMove(vector<char> board, char computer)
{
	unsigned int move = 0;
	bool found = false;

	while (!found && move < board.size())
	{
		if (isLegal(board, move))
		{
			board[move] = computer;
			found = winner(board) == computer;
			board[move] = EMPTY;
		}

		if (!found)
		{
			move++;
		}
	}

	if (!found)
	{
		move = 0;
		char human = opponent(computer);
		while (!found && move < board.size())
		{
			if (isLegal(board, move))
			{
				board[move] = human;
				found = winner(board) == human;
				board[move] = EMPTY;
			}

			if (!found)
			{
				move++;
			}
		}
	}

	if (!found)
	{
		move = 0;
		unsigned int i = 0;
		const int BEST_MOVES[] = { 4, 0, 2, 6, 8, 1, 3, 5, 7 };
		while (!found && i < board.size())
		{
			move = BEST_MOVES[i];
			if (isLegal(board, move))
			{
				found = true;
			}
			++i;
		}
	}

	cout << "I shall take square number: " << move << endl;
	return move;
}

void announceWinner(char winner, char computer, char human)
{
	if (winner == computer)
	{
		cout << winner << "'s won!\n";
		cout << "As I predicted, human, I am triumphant once more -- proof\n";
		cout << "that computers are superior to humans in all regards.\n";
	}
	else if (winner == human)
	{
		cout << winner << "'s won!\n";
		cout << "No, no! It cannot be! Somehow you tricked me, human.\n";
		cout << "But never again! I, the computer, so swear it!\n";
	}
	else
	{
		cout << "It's a tie.\n";
		cout << "You were most lucky, human, and somehow managed to tie me.\n";
		cout << "Celebrate...for this is the best you will ever achieve.\n";
	}
}