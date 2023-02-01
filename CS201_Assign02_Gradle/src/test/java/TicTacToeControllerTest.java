import static org.junit.Assert.*;

import java.util.Arrays;

import org.junit.Before;
import org.junit.Test;

public class TicTacToeControllerTest
{
	private static int[][] EMPTY_BOARD = {
			{ TicTacToeModel.EMPTY, TicTacToeModel.EMPTY, TicTacToeModel.EMPTY },
			{ TicTacToeModel.EMPTY, TicTacToeModel.EMPTY, TicTacToeModel.EMPTY },
			{ TicTacToeModel.EMPTY, TicTacToeModel.EMPTY, TicTacToeModel.EMPTY },
	};
	private static int[][] CENTER_X_BOARD = {
			{ TicTacToeModel.EMPTY, TicTacToeModel.EMPTY,    TicTacToeModel.EMPTY },
			{ TicTacToeModel.EMPTY, TicTacToeModel.PLAYER_X, TicTacToeModel.EMPTY },
			{ TicTacToeModel.EMPTY, TicTacToeModel.EMPTY,    TicTacToeModel.EMPTY },
	};
	private static int[][] X_WINS_ROW_BOARD = {
			{ TicTacToeModel.EMPTY,    TicTacToeModel.PLAYER_O, TicTacToeModel.PLAYER_O },
			{ TicTacToeModel.PLAYER_X, TicTacToeModel.PLAYER_X, TicTacToeModel.PLAYER_X },
			{ TicTacToeModel.PLAYER_O, TicTacToeModel.EMPTY,    TicTacToeModel.EMPTY },
	};
	private static int[][] DRAW_BOARD = {
			{ TicTacToeModel.PLAYER_X, TicTacToeModel.PLAYER_O, TicTacToeModel.PLAYER_X },
			{ TicTacToeModel.PLAYER_X, TicTacToeModel.PLAYER_X, TicTacToeModel.PLAYER_O },
			{ TicTacToeModel.PLAYER_O, TicTacToeModel.PLAYER_X, TicTacToeModel.PLAYER_O },
	};

	private static int[][] DIAGONAL_WIN_X = {
			{ TicTacToeModel.PLAYER_X, TicTacToeModel.EMPTY, TicTacToeModel.EMPTY },
			{ TicTacToeModel.EMPTY, TicTacToeModel.PLAYER_X, TicTacToeModel.EMPTY },
			{ TicTacToeModel.EMPTY, TicTacToeModel.EMPTY,    TicTacToeModel.PLAYER_X}
	};

	private int[][] transpose(int[][] a)
	{
		int[][] result = new int[3][3];
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				result[j][i] = a[i][j];
			}
		}
		return result;
	}
	
	private int[][] invertPlayer(int[][] a)
	{
		int[][] result = new int[3][3];
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				int p = a[i][j];
				if (p != TicTacToeModel.EMPTY)
				{
					p = (p == TicTacToeModel.PLAYER_X) ? TicTacToeModel.PLAYER_O : TicTacToeModel.PLAYER_X;
				}
				result[i][j] = p;
			}
		}
		return result;
	}

	private TicTacToeModel emptyBoard;
	private TicTacToeModel centerX;
	private TicTacToeModel xWinsRow;
	private TicTacToeModel xWinsCol;
	private TicTacToeModel oWinsRow;
	private TicTacToeModel oWinsCol;
	private TicTacToeModel draw;
	private TicTacToeModel diagonalWinX;
	private TicTacToeController controller;

	
	@Before
	public void setUp()
	{
		int[][] centerXBoard = {
				{ TicTacToeModel.EMPTY, TicTacToeModel.EMPTY,    TicTacToeModel.EMPTY },
				{ TicTacToeModel.EMPTY, TicTacToeModel.PLAYER_X, TicTacToeModel.EMPTY },
				{ TicTacToeModel.EMPTY, TicTacToeModel.EMPTY,    TicTacToeModel.EMPTY },
		};
		int[][] xWinsRowBoard = {
				{ TicTacToeModel.EMPTY,    TicTacToeModel.PLAYER_O, TicTacToeModel.PLAYER_O },
				{ TicTacToeModel.PLAYER_X, TicTacToeModel.PLAYER_X, TicTacToeModel.PLAYER_X },
				{ TicTacToeModel.PLAYER_O, TicTacToeModel.EMPTY,    TicTacToeModel.EMPTY },
		};
		int[][] drawBoard = {
				{ TicTacToeModel.PLAYER_X, TicTacToeModel.PLAYER_O, TicTacToeModel.PLAYER_X },
				{ TicTacToeModel.PLAYER_X, TicTacToeModel.PLAYER_X, TicTacToeModel.PLAYER_O },
				{ TicTacToeModel.PLAYER_O, TicTacToeModel.PLAYER_X, TicTacToeModel.PLAYER_O },
		};

		emptyBoard = new TicTacToeModel(EMPTY_BOARD, TicTacToeModel.PLAYER_X);
		centerX = new TicTacToeModel(centerXBoard, TicTacToeModel.PLAYER_O);
		xWinsRow = new TicTacToeModel(xWinsRowBoard.clone(), TicTacToeModel.PLAYER_X);
		xWinsCol = new TicTacToeModel(transpose(X_WINS_ROW_BOARD), TicTacToeModel.PLAYER_X);
		oWinsRow = new TicTacToeModel(invertPlayer(X_WINS_ROW_BOARD), TicTacToeModel.PLAYER_O);
		oWinsCol = new TicTacToeModel(transpose(invertPlayer(X_WINS_ROW_BOARD)), TicTacToeModel.PLAYER_O);
		draw = new TicTacToeModel(drawBoard, TicTacToeModel.PLAYER_O);
		diagonalWinX = new TicTacToeModel(DIAGONAL_WIN_X.clone(), TicTacToeModel.PLAYER_X);
		controller = new TicTacToeController();
	}

	@Test
	public void testMakeMove()
	{
		assertTrue(controller.makeMove(emptyBoard, TicTacToeModel.PLAYER_X, 0, 0));
		assertTrue(controller.makeMove(emptyBoard, TicTacToeModel.PLAYER_X, 2, 0));
		assertTrue(controller.makeMove(emptyBoard, TicTacToeModel.PLAYER_X, 0, 2));
		assertFalse(controller.makeMove(emptyBoard, TicTacToeModel.PLAYER_X, 4, 0));
		assertFalse(controller.makeMove(emptyBoard, TicTacToeModel.PLAYER_X, 0, 4));
		assertFalse(controller.makeMove(emptyBoard, TicTacToeModel.PLAYER_X, -1, 1));
		assertFalse(controller.makeMove(emptyBoard, TicTacToeModel.PLAYER_X, 2, -5));
		assertFalse(controller.makeMove(emptyBoard, TicTacToeModel.PLAYER_O, 0, 2));
		
		assertTrue(controller.makeMove(centerX, TicTacToeModel.PLAYER_O, 0, 2));
		assertFalse(controller.makeMove(centerX, TicTacToeModel.PLAYER_O, 1, 1));
		assertFalse(controller.makeMove(centerX, TicTacToeModel.PLAYER_X, 1, 2));
	}

	@Test
	public void testCheckWin()
	{
		assertTrue(controller.checkWin(xWinsRow));
		assertTrue(controller.checkWin(xWinsCol));
		assertFalse(controller.checkWin(emptyBoard));
		assertFalse(controller.checkWin(centerX));

		assertTrue(controller.checkWin(oWinsRow));
		assertTrue(controller.checkWin(oWinsCol));

		assertTrue(controller.checkWin(diagonalWinX));
	}
	
	@Test
	public void testCheckDraw()
	{
		assertFalse(controller.checkDraw(emptyBoard));
		assertFalse(controller.checkDraw(centerX));
		assertTrue(controller.checkDraw(draw));
	}
}
