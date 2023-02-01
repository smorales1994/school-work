import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.security.spec.KeySpec;
import java.util.Objects;

/**
 * An instance of the TicTacToeController class represents
 * a controller to update the state of a tic-tac-toe game
 */

public class TicTacToeController
{
	public static final String PATH = "C:/CS201-Spring2022/CS201_Assign02_Gradle/";
	public static final String saveGame = "saveGame.txt";

	// Checks to make sure that the current player's move is legal (no values outside the 3 x 3 game board, and that the spot is empty), and that it's the turn of the player placing the marker.
	public boolean makeMove(TicTacToeModel model, int player, int row, int col)
	{
		if (row >= 0 && row <= (TicTacToeModel.HEIGHT - 1) && col >= 0 && col <= (TicTacToeModel.WIDTH - 1))
		{
			if (model.getCell(row, col) == TicTacToeModel.EMPTY && player == model.getTurn())
			{
				model.placeMarker(row, col);

				return true;
			}
		}

		return false;
	}

	// Checks to see if a win happens after current player places their marker (Win = 3 in a row, 3 up and down, or 3 diagonally across the board of the player's markers).
	public boolean checkWin(TicTacToeModel model)
	{
		// Local variables for the game board's height and width.
		int boardHeight = TicTacToeModel.HEIGHT;
		int boardWidth = TicTacToeModel.WIDTH;

		// Loop to check if current player's turn gets a win by 3 in a row or 3 up and down.
		for (int i = 0; i < TicTacToeModel.HEIGHT; i++)
		{
			if (model.getCell(i, boardWidth - 3) == model.getTurn() && model.getCell(i, boardWidth - 2) == model.getTurn() && model.getCell(i, boardWidth - 1) == model.getTurn())
			{
				return true;
			}

			if (model.getCell(boardHeight - 3, i) == model.getTurn() && model.getCell(boardHeight - 2, i) == model.getTurn() && model.getCell(boardHeight - 1, i) == model.getTurn())
			{
				return true;
			}
		}

		// Two conditional statements to check if the current player's turn gets a win by 3 markers diagonally on either side.
		if (model.getCell(boardHeight - 3, boardWidth - 3) == model.getTurn() && model.getCell(boardHeight - 2, boardHeight - 2) == model.getTurn() && model.getCell(boardHeight - 1, boardWidth - 1) == model.getTurn())
		{
			return true;
		}

		if (model.getCell(boardHeight - 3, boardWidth - 1) == model.getTurn() && model.getCell(boardHeight - 2, boardHeight - 2) == model.getTurn() && model.getCell(boardHeight - 1, boardWidth - 3) == model.getTurn())
		{
			return true;
		}

		return false;
	}

	// Checks if a draw happens or not when current player places a marker down; a draw being when there's no more empty spots on the board.
	public boolean checkDraw(TicTacToeModel model)
	{
		for (int i = 0; i < TicTacToeModel.HEIGHT; i++)
		{
			for (int j = 0; j < TicTacToeModel.WIDTH; j++)
			{
				if (model.getCell(i, j) == TicTacToeModel.EMPTY)
				{
					return false;
				}
			}
		}

		return true;
	}

	// Switches current player's turn.
	public void changePlayer(TicTacToeModel model)
	{
		model.updateTurn();
	}


	// Function that reads the save file from a previously saved game; will load the save file game board and player turn if successful, otherwise returns null and gives an error message.
	public TicTacToeModel loadGame()
	{
		int row = 0;
		int col = 0;
		int[][] boardState = new int[TicTacToeModel.HEIGHT][TicTacToeModel.WIDTH];
		int playerTurn = TicTacToeModel.PLAYER_X;

		try
		{
			FileReader reader = new FileReader(PATH + saveGame);

			try
			{
				while (row < TicTacToeModel.WIDTH)
				{
					char marker = (char) reader.read();

					if (marker == 'X')
					{
						boardState[col][row] = TicTacToeModel.PLAYER_X;

						col++;
					}

					if (marker == 'O')
					{
						boardState[col][row] = TicTacToeModel.PLAYER_O;

						col++;
					}

					if (marker == ' ')
					{
						boardState[col][row] = TicTacToeModel.EMPTY;

						col++;
					}

					if (col == TicTacToeModel.HEIGHT)
					{
						row++;
						col = 0;
					}
				}

				reader.read();

				if ((char) reader.read() == 'O')
				{
					playerTurn = TicTacToeModel.PLAYER_O;
				}
			}

			finally
			{
				reader.close();
			}

			return new TicTacToeModel(boardState, playerTurn);
		}

		catch (FileNotFoundException e)
		{
			System.out.println(e.getMessage());
		}

		catch (IOException e)
		{
			System.out.println(e.getMessage());
		}

		return null;
	}

	// Writes the current game state to a save file, and will return true if successful, false if the function fails to save the game and gives an error message.
	public boolean saveGame(TicTacToeModel model)
	{
		try
		{
			FileWriter writer = new FileWriter(PATH + saveGame);

			try
			{
				for (int i = 0; i < TicTacToeModel.HEIGHT; i++)
				{
					for (int j = 0; j < TicTacToeModel.WIDTH; j++)
					{
						if (model.getCell(j, i) == TicTacToeModel.PLAYER_X)
						{
							 writer.write('X');
						}

						if (model.getCell(j, i) == TicTacToeModel.PLAYER_O)
						{
							writer.write('O');
						}

						if (model.getCell(j, i) == TicTacToeModel.EMPTY)
						{
							writer.write(' ');
						}

					}

					writer.write('\n');
				}

				if (model.getTurn() == TicTacToeModel.PLAYER_X)
				{
					writer.write('X');
				}

				else
				{
					writer.write('O');
				}
			}

			finally
			{
				writer.close();
			}

			return true;
		}

		catch (IOException e)
		{
			System.out.println(e.getMessage());
		}

		return false;
	}
}
