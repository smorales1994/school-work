import static org.junit.Assert.*;

import java.util.Arrays;

import org.junit.Before;
import org.junit.Test;

public class TicTacToeModelTest
{
	private static int[][] EMPTY_BOARD = {
			{ TicTacToeModel.EMPTY, TicTacToeModel.EMPTY, TicTacToeModel.EMPTY },
			{ TicTacToeModel.EMPTY, TicTacToeModel.EMPTY, TicTacToeModel.EMPTY },
			{ TicTacToeModel.EMPTY, TicTacToeModel.EMPTY, TicTacToeModel.EMPTY }
	};
	private static int[][] CENTER_X_BOARD = {
			{ TicTacToeModel.EMPTY, TicTacToeModel.EMPTY,    TicTacToeModel.EMPTY },
			{ TicTacToeModel.EMPTY, TicTacToeModel.PLAYER_X, TicTacToeModel.EMPTY },
			{ TicTacToeModel.EMPTY, TicTacToeModel.EMPTY,    TicTacToeModel.EMPTY }
	};

	private static int[][] CENTER_O_BOARD = {
			{ TicTacToeModel.EMPTY, TicTacToeModel.EMPTY,    TicTacToeModel.EMPTY },
			{ TicTacToeModel.EMPTY, TicTacToeModel.PLAYER_O, TicTacToeModel.EMPTY },
			{ TicTacToeModel.EMPTY, TicTacToeModel.EMPTY,    TicTacToeModel.EMPTY }
	};

	private static int[][] MIDDLE_LEFT_X = {
			{ TicTacToeModel.EMPTY, TicTacToeModel.EMPTY,    TicTacToeModel.EMPTY },
			{ TicTacToeModel.PLAYER_X, TicTacToeModel.EMPTY, TicTacToeModel.EMPTY },
			{ TicTacToeModel.EMPTY, TicTacToeModel.EMPTY,    TicTacToeModel.EMPTY }
	};

	private TicTacToeModel emptyBoard;
	private TicTacToeModel centerX;
	private TicTacToeModel centerO;
	private TicTacToeModel middleLeft;

	@Before
	public void setUp()
	{
		int[][] centerXBoardArray = {
				{ TicTacToeModel.EMPTY, TicTacToeModel.EMPTY,    TicTacToeModel.EMPTY },
				{ TicTacToeModel.EMPTY, TicTacToeModel.PLAYER_X, TicTacToeModel.EMPTY },
				{ TicTacToeModel.EMPTY, TicTacToeModel.EMPTY,    TicTacToeModel.EMPTY }
		};

		int[][] centerOBoardArray = {
				{ TicTacToeModel.EMPTY, TicTacToeModel.EMPTY,    TicTacToeModel.EMPTY },
				{ TicTacToeModel.EMPTY, TicTacToeModel.PLAYER_O, TicTacToeModel.EMPTY },
				{ TicTacToeModel.EMPTY, TicTacToeModel.EMPTY,    TicTacToeModel.EMPTY }
		};

		int[][] middleLeftBoardArray = {
				{ TicTacToeModel.EMPTY, TicTacToeModel.EMPTY,    TicTacToeModel.EMPTY },
				{ TicTacToeModel.PLAYER_X, TicTacToeModel.EMPTY, TicTacToeModel.EMPTY },
				{ TicTacToeModel.EMPTY, TicTacToeModel.EMPTY,    TicTacToeModel.EMPTY }
		};

		emptyBoard = new TicTacToeModel();
		centerX = new TicTacToeModel(centerXBoardArray, TicTacToeModel.PLAYER_O);
		centerO = new TicTacToeModel(centerOBoardArray, TicTacToeModel.PLAYER_X);
		middleLeft = new TicTacToeModel(middleLeftBoardArray, TicTacToeModel.PLAYER_O);
	}

	@Test
	public void testGetTurn()
	{
		assertEquals(TicTacToeModel.PLAYER_X, emptyBoard.getTurn());
		assertEquals(TicTacToeModel.PLAYER_O, centerX.getTurn());
		assertEquals(TicTacToeModel.PLAYER_X, centerO.getTurn());
		assertEquals(TicTacToeModel.PLAYER_O, middleLeft.getTurn());
	}

	@Test
	public void testGetCell()
	{
		assertEquals(TicTacToeModel.EMPTY, emptyBoard.getCell(1, 1));
		assertEquals(TicTacToeModel.EMPTY, emptyBoard.getCell(0, 2));
		assertEquals(TicTacToeModel.EMPTY, emptyBoard.getCell(0, 0));

		assertEquals(TicTacToeModel.PLAYER_X, centerX.getCell(1, 1));
		assertEquals(TicTacToeModel.PLAYER_O, centerO.getCell(1, 1));

		assertEquals(TicTacToeModel.PLAYER_X, middleLeft.getCell(1, 0));

		assertEquals(TicTacToeModel.EMPTY, centerX.getCell(0, 2));
		assertEquals(TicTacToeModel.EMPTY, centerX.getCell(0, 0));

	}

	@Test
	public void testPlaceMarker()
	{
		emptyBoard.placeMarker(2, 1);
		assertEquals(TicTacToeModel.PLAYER_X, emptyBoard.getCell(2, 1));
		centerX.placeMarker(0, 2);
		assertEquals(TicTacToeModel.PLAYER_O, centerX.getCell(0, 2));
		middleLeft.placeMarker(1,0);
		assertEquals(TicTacToeModel.PLAYER_O, middleLeft.getCell(1,0));
	}
	
	@Test
	public void testUpdateTurn()
	{
		assertEquals(TicTacToeModel.PLAYER_X, emptyBoard.getTurn());
		emptyBoard.placeMarker(2, 1);
		emptyBoard.updateTurn();
		assertEquals(TicTacToeModel.PLAYER_O, emptyBoard.getTurn());
		emptyBoard.updateTurn();
		assertEquals(TicTacToeModel.PLAYER_X, emptyBoard.getTurn());

		assertEquals(TicTacToeModel.PLAYER_O, centerX.getTurn());
		centerX.placeMarker(0, 2);
		centerX.updateTurn();
		assertEquals(TicTacToeModel.PLAYER_X, centerX.getTurn());
		centerX.updateTurn();
		assertEquals(TicTacToeModel.PLAYER_O, centerX.getTurn());
	}
}
