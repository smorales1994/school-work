/**
 * An instance of the TicTacToeModel class represents the
 * state of a tic-tac-toe game.
 */

public class TicTacToeModel
{
	public static final int PLAYER_O = 0;
	public static final int PLAYER_X = 1;
	public static final int EMPTY = 2;
	public static final int WIDTH = 3;
	public static final int HEIGHT = 3;
		
	// Created private fields for player turn and game board objects.
	private int currentPlayerTurn;
	private int[][] gameBoard;

	// Default constructor to initialize player turn to X and to empty the game board.
	public TicTacToeModel()
	{
		this.currentPlayerTurn = PLAYER_X;
		this.gameBoard = new int [HEIGHT][WIDTH];

		for (int i = 0; i < HEIGHT; i++)
		{
			for (int j = 0; j < WIDTH; j++)
			{
				gameBoard[i][j] = EMPTY;
			}
		}
	}

	// Constructor that takes the game board and player turn values to assign them in the Model class.
	public TicTacToeModel(int[][] board, int turn)
	{
		this.gameBoard = board;
		this.currentPlayerTurn = turn;
	}

	// Returns current player's turn.
	public int getTurn()
	{
		return currentPlayerTurn;
	}

	// Returns the cell location at a given row and column.
	public int getCell(int row, int col)
	{
		return gameBoard[row][col];
	}

	// Places a O or X marker depending on which player's turn it is at a specified row and col location, given that it's a legal move.
	public void placeMarker(int row, int col)
	{
		gameBoard[row][col] = currentPlayerTurn;
	}

	// Switches current player's turn once they placed their marker down.
	public void updateTurn()
	{
		 if (currentPlayerTurn == PLAYER_X)
		 {
			 currentPlayerTurn = PLAYER_O;
		 }

		 else
		 {
			 currentPlayerTurn = PLAYER_X;
		 }
	}
}
