import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;
import java.util.Random;
import javax.swing.JPanel;
import javax.swing.Timer;

public class DisksPanel extends JPanel
{
	private static final long serialVersionUID = 1L;
	public static final int WIDTH = 400;
	public static final int HEIGHT = 300;
	private static final Font FONT = new Font("Dialog", Font.BOLD, 24);

	// Added private fields for the various objects needed in this game.
	private Timer timer;
	private DiskModel diskModel;
	private Disk currentDisk;
	private int x, y, radius, timeRem, initialTimeRem, timeIncrement;
	private boolean gameIsOver;
	private Random randValue;
	private ArrayList <DiskColor> nextColor;
	private DiskColor newColor;
	private Color barColor;

	// Constructor to initialize the objects from DiskPanel class.
	public DisksPanel()
	{
		diskModel = new DiskModel();
		currentDisk = new Disk(x, y, radius, newColor);
		randValue = new Random();
		x += radius;
		y += radius;
		radius = 10 + randValue.nextInt(35);
		newColor = DiskColor.values()[randValue.nextInt(15)];
		barColor = new Color(255, 23, 23, 63);
		nextColor = new ArrayList <DiskColor>();
		gameIsOver = false;
		initialTimeRem = WIDTH;
		timeRem = initialTimeRem;
		timeIncrement = 1;

		setPreferredSize(new Dimension(WIDTH, HEIGHT));
		setBackground(Color.GRAY);

		addMouseListener(new MouseAdapter()
		{
			@Override
			public void mouseClicked(MouseEvent e)
			{
				handleMouseClick(e);
			}
		});

		addMouseMotionListener(new MouseAdapter()
		{
			@Override
			public void mouseMoved(MouseEvent e)
			{
				handleMouseMove(e);
			}
		});

		// Schedule timer events to fire every 100 milliseconds (0.1 seconds)
		this.timer = new Timer(100, new ActionListener()
		{
			@Override
			public void actionPerformed(ActionEvent e)
			{
				handleTimerEvent(e);
			}
		});

		timer.start();
	}

	// You can call this method to convert a DiskColor value into
	// a java.awt.Color object.
	public Color colorOf(DiskColor dc)
	{
		return new Color(dc.red(), dc.green(), dc.blue());
	}

	// This method is called whenever the mouse is moved
	private void handleMouseMove(MouseEvent e)
	{
		// Condition that checks if the game is over before letting the user move their mouse around to place a disk.
		if (!gameIsOver)
		{
			x = e.getX();
			y = e.getY();
		}

		repaint();
	}

	// This method is called whenever the mouse is clicked
	private void handleMouseClick(MouseEvent e)
	{
		// Condition that checks if the game is over and if a left or right click from the user occurs, along with stopping and resetting the timer duration if a valid disk is placed.
		if (!gameIsOver && (e.getButton() == MouseEvent.BUTTON1 || e.getButton() == MouseEvent.BUTTON3))
		{
			timer.stop();

			// Creates a new Disk object for the current disk that hasn't been placed.
			currentDisk = new Disk(x, y, radius, newColor);

			// Loop to check if the current disk when placed overlaps with any previous disks.
			for (int i = 0; i < diskModel.getNumDisks(); i++)
			{
				// Condition that will result in game over if the current disk overlaps with any previous disks when placed.
				if (currentDisk.overlaps(diskModel.getDisks().get(i)))
				{
					gameIsOver = true;

					timer.stop();
				}
			}

			// Condition that checks if the current disk placed is out of bounds of the rectangle defined in this class, and if the game is over to ensure an overlapped disk is not added.
			if (!currentDisk.isOutOfBounds(WIDTH, HEIGHT) && !gameIsOver)
			{
				nextColor.add(DiskColor.values()[randValue.nextInt(15)]);
				diskModel.addDisk(currentDisk);
				diskModel.getNumDisks();
				radius = 10 + randValue.nextInt(34);

				// Resets the time back to the initial time remaining, while also making the time remaining shorter for the user to place a disk.
				timer.restart();
				timeIncrement += timeIncrement;
				timeRem = initialTimeRem - (timeIncrement / 5000);
			}

			// Gives a game over if the current disk placed is out of bounds.
			else
			{
				gameIsOver = true;

				timer.stop();
			}
		}

		repaint();
	}

	// This method is called whenever a timer event fires
	private void handleTimerEvent(ActionEvent e)
	{
		// Decreases the time remaining until the user places a disk down.
		timeRem -= 10;

		// Condition to check if time remaining is 0 and will result in a game over.
		if (timeRem <= 0)
		{
			gameIsOver = true;

			timer.stop();
		}

		repaint();
	}

	// This method is called automatically whenever the contents of
	// the window need to be redrawn.
	@Override
	public void paint(Graphics g)
	{
		// Paint the window background
		super.paint(g);

		// Condition that checks if the game is over to determine if a disk outline will be drawn on screen or not.
		if (!gameIsOver)
		{
			g.setColor(Color.black);
			g.drawOval(x - radius, y - radius, 2 * radius, 2 * radius);
		}

		// Condition to ensure no disks are present at the start of the game.
		if (diskModel.getNumDisks() > 0)
		{
			// Loop that draws all disks placed on the screen each time a new disk is placed.
			for (int i = 0; i < diskModel.getNumDisks(); i++)
			{
				// Generates random colors to add to the DiskColor ArrayList for disks placed.
				g.setColor(colorOf(nextColor.get(i)));

				// Draws the disk on screen.
				g.fillOval((int) (diskModel.getDisks().get(i).getX() - diskModel.getDisks().get(i).getRadius()), (int) (diskModel.getDisks().get(i).getY() - diskModel.getDisks().get(i).getRadius()), (int) (2 * diskModel.getDisks().get(i).getRadius()), (int) (2 * diskModel.getDisks().get(i).getRadius()));
			}

			// Draws the game over text on the screen if the game is over from an overlap or out of bounds test returning true.
			if (gameIsOver)
			{
				g.setColor(Color.black);
				g.setFont(FONT);
				g.drawString("Game Over!", 125, 150);

				timer.stop();
			}

			// Draws the current number of disks placed on the screen.
			g.setColor(Color.black);
			g.setFont(FONT);
			g.drawString("" + diskModel.getNumDisks(), 370, 20);
		}

		// Draws the timer bar that is the time remaining for the user to place a disk; when it runs out the game is over.
		g.setColor(barColor);
		g.fillRect(0, 270, timeRem, 25);
	}
}


