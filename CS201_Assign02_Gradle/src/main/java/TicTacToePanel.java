import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import javax.swing.JPanel;

public class TicTacToePanel extends JPanel
{
	private static final long serialVersionUID = 1L;

	private static final int WIDTH = 300;
	private static final int HEIGHT = 300;
	private static final Font FONT = new Font("Dialog", Font.BOLD, 24);
	
	// Added private fields for the game model, controller, and end game conditions.
	private TicTacToeModel model;
	private TicTacToeController controller;
	private boolean gameIsOver, gameDraw;

	// Constructor that sets up the game board and logic for the player to start.
	public TicTacToePanel()
	{
		// TODO: Initialize fields
		model = new TicTacToeModel();
		controller=  new TicTacToeController();
		gameIsOver = false;
		gameDraw = false;

		setPreferredSize(new Dimension(WIDTH, HEIGHT));
		setBackground(Color.BLACK);
		
		addMouseListener(new MouseAdapter()
		{
			@Override
			public void mouseClicked(MouseEvent e) { handleMouseClick(e); }
		});
		
		// Register event handlers (DO NOT CHANGE)
		addKeyListener(new KeyListener()
		{

			@Override
			public void keyTyped(KeyEvent e) {}

			@Override
			public void keyPressed(KeyEvent e) { handleKeyTyped(e); }

			@Override
			public void keyReleased(KeyEvent e) {}
			
		});
	}

	// Handles when a left click or right click happens during the game, checking to ensure the board is empty and that the move is legal.
	private void handleMouseClick(MouseEvent e)
	{
		if (!gameIsOver && !gameDraw)
		{
			int row = e.getX() / 100;
			int col = e.getY() / 100;

			// Ensures that if a far edge is clicked, it will click on the corresponding cell instead.
			if (row == 3)
			{
				row = 2;
			}

			if (col == 3)
			{
				col = 2;
			}

			if (e.getButton() == MouseEvent.BUTTON1 && model.getTurn() == TicTacToeModel.PLAYER_X)
			{
				if (controller.makeMove(model, TicTacToeModel.PLAYER_X, row, col))
				{
					model.placeMarker(row, col);

					if (controller.checkWin(model))
					{
						gameIsOver = true;
					}

					else if (controller.checkDraw(model))
					{
						gameDraw = true;
					}

					if (!gameIsOver && !gameDraw)
					{
						controller.changePlayer(model);
					}
				}
			}

			if (e.getButton() == MouseEvent.BUTTON3 && model.getTurn() == TicTacToeModel.PLAYER_O)
			{
				if (controller.makeMove(model, TicTacToeModel.PLAYER_O, row, col))
				{
					model.placeMarker(row, col);

					if (controller.checkWin(model))
					{
						gameIsOver = true;
					}

					else if (controller.checkDraw(model))
					{
						gameDraw = true;
					}

					if (!gameIsOver && !gameDraw)
					{
						controller.changePlayer(model);
					}
				}
			}
		}

		repaint();
	}

	// Handles when the user clicks s for saving a game or l for loading a game. It will print messages if the save/load failed or succeeded.
	private void handleKeyTyped(KeyEvent e)
	{
		if (e.getKeyChar() == 's')
		{
			if (controller.saveGame(model))
			{
				System.out.println("Game saved successfully!");
			}

			else
			{
				System.out.println("Failed to save game!");
			}
		}

		if (e.getKeyChar() == 'l')
		{
			if (controller.loadGame() != null)
			{
				System.out.println("Game loaded successfully!");

				model = controller.loadGame();

				repaint();
			}

			else
			{
				System.out.println("Game failed to load!");
			}
		}
	}
	
	@Override
	public void paint(Graphics g)
	{
		super.paint(g); // paint background

		// Draw the tic-tac-toe board (DO NOT MODIFY)
		g.setColor(Color.WHITE);
		for (int i = 1; i < 4; i++)
		{
			// Vertical line
			g.drawLine(i*(WIDTH/3), 0, i*(WIDTH/3), HEIGHT-1);
			// Horizontal line
			g.drawLine(0, i*(HEIGHT/3), WIDTH-1, i*(HEIGHT/3));
		}
		
		// Draws the player X or O marker when the X or O player clicks on a cell on the game board, along with updating the board as more markers are placed.
		for (int i = 0; i < HEIGHT / 100; i++)
		{
			for (int j = 0; j < WIDTH / 100; j++)
			{
				if (model.getCell(i, j) == TicTacToeModel.PLAYER_X)
				{
					g.setColor(Color.GREEN);
					g.drawRect(i * (HEIGHT / 3) + 12, j * (WIDTH / 3) + 12, HEIGHT / 4, WIDTH / 4);
					g.fillRect(i * (HEIGHT / 3) + 12, j * (WIDTH / 3) + 12, HEIGHT / 4, WIDTH / 4);
				}

				if (model.getCell(i, j) == TicTacToeModel.PLAYER_O)
				{
					g.setColor(Color.BLUE);
					g.drawOval(i * (HEIGHT / 3) + 12, j * (WIDTH / 3) + 12, HEIGHT / 4, WIDTH / 4);
					g.fillOval(i * (HEIGHT / 3) + 12, j * (WIDTH / 3) + 12, HEIGHT / 4, WIDTH / 4);
				}
			}
		}

		// Prints out end game messages when either Player X or O wins, or if the game is a draw.
		if (gameIsOver)
		{
			if (model.getTurn() == TicTacToeModel.PLAYER_X)
			{
				g.setColor(Color.YELLOW);
				g.setFont(FONT);
				g.drawString("Game Over!", 85, 150);
				g.drawString("Player X wins!", 85, 170);
			}

			else
			{
				g.setColor(Color.YELLOW);
				g.setFont(FONT);
				g.drawString("Game Over!", 85, 150);
				g.drawString("Player O wins!", 85, 170);
			}
		}

		if (gameDraw)
		{
			g.setColor(Color.YELLOW);
			g.setFont(FONT);
			g.drawString("It's a draw!", 90, 150);
		}
	}
}
