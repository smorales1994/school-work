import java.awt.Color;
import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.util.Scanner;

import javax.imageio.ImageIO;

public class Mandelbrot
{
	public static final int WIDTH = 800;

	public static final int HEIGHT = 600;

	public static final int THRESHOLD = 2000;
	
	//public static final String PATH = "CS201_Assign04_Gradle/"
	public static final String PATH = "C:/CS201-Spring2022/CS201_Assign04_Gradle/";

	public static void main(String[] args) throws InterruptedException, IOException
	{
		double x1 = -2.0;
		double y1 = -1.0;
		double x2 = 2.0;
		double y2 = 2.0;
		//double x1 = -1.28667;
		//double y1 = -0.413333;
		//double x2 = -1.066667;
		//double y2 = -0.193333;
		int colorChoice = 1;
		int numThreads = 1;
		String fileName = "output.png";
		
		// Uncomment to allow user to enter coordinates
		Scanner keyboard = new Scanner(System.in);

		System.out.println("Please enter coordinates of region to render:");
		System.out.print("  x1: ");

		x1 = keyboard.nextDouble();

		System.out.print("  y1: ");

		y1 = keyboard.nextDouble();

		System.out.print("  x2: ");

		x2 = keyboard.nextDouble();

		System.out.print("  y2: ");

		y2 = keyboard.nextDouble();
		
		// Create bounding rectangle for Mandelbrot region
		Rect bounds = new Rect(x1,y1,x2,y2);

		// Uncomment to prompt user for output filename
		System.out.print("Output filename (.png): ");
		fileName = keyboard.next();
		
		// Uncomment to allow user to choose color scheme
		System.out.println("Choose a color chooser: ");
		System.out.println("   1 - Simple Gradient");
		System.out.println("   2 - Color Mapping");
		colorChoice = keyboard.nextInt();

		// Uncomment to allow user to select number of threads
		System.out.print("Enter the number of threads to use: ");
		numThreads = keyboard.nextInt();
		
		System.out.println("Working...");
		
		// Create iteration count array and compute iterations
		int[][] iterCounts = new int[HEIGHT][WIDTH];
		computeIterations(bounds, numThreads, iterCounts);
		
		// Create output image from iteration array		
		BufferedImage bufferedImage = new BufferedImage(WIDTH, HEIGHT, BufferedImage.TYPE_INT_ARGB);
		renderImage(bufferedImage, iterCounts, colorChoice);

		// Write output image to PNG file
		OutputStream os = new BufferedOutputStream(new FileOutputStream(PATH + fileName));
		try
		{
			ImageIO.write(bufferedImage, "PNG", os);
		}

		finally
		{
			os.close();
		}
		
		System.out.println("Image written successfully!");
	}

	// Method to compute iterations for each pixel
	public static void computeIterations(Rect bounds, int numThreads, int[][] iterCounts) throws InterruptedException
	{
		// TODO: Create MandelbrotTasks and threads
		if (numThreads == 1)
		{
			MandelbrotTask task = new MandelbrotTask(bounds.getX1(), bounds.getY1(), bounds.getX2(), bounds.getY2(), 0, WIDTH, 0, HEIGHT, iterCounts);

			task.run();
		}

		else
		{
			MandelbrotTask[] tasks = new MandelbrotTask[numThreads];

			for (int i = 0; i < numThreads; i++)
			{
				tasks[i]  = new MandelbrotTask(bounds.getX1(), bounds.getY1(), bounds.getX2(), bounds.getY2(), (WIDTH / numThreads) * i, (WIDTH / numThreads) * (i + 1), 0, HEIGHT, iterCounts);
			}

			Thread[] threads = new Thread[numThreads];

			// TODO: Start threads
			for (int i = 0; i < numThreads; i++)
			{
				threads[i] = new Thread(tasks[i]);
				threads[i].start();
			}

			// TODO: Wait for all threads to finish
			try
			{
				for (int i = 0; i < numThreads; i++)
				{
					threads[i].join();
				}
			}

			catch (InterruptedException e)
			{
				System.err.println("Error: A thread has been interrupted.");
			}
		}
	}

	// Method to create image buffer using user selected colorChooser
	public static BufferedImage renderImage(BufferedImage bufferedImage, int[][] iterCounts, int colorChoice)
	{
	
		ColorChooser chooser = null;
		
		// TODO: set chooser based on colorChoice menu selection
		if (colorChoice == 1)
		{
			chooser = new SimpleGradientColorChooser();
		}

		else if (colorChoice == 2)
		{
			chooser = new ColorMappingColorChooser(iterCounts);
		}

		else
		{
			chooser = new SimpleGradientColorChooser();
		}		
		
		// Use computed iteration counts to render the image
		Graphics g = bufferedImage.getGraphics();
		for (int i = 0; i < HEIGHT; i++)
		{
			for (int j = 0; j < WIDTH; j++)
			{
				Color c = chooser.getColor(iterCounts[i][j]);
				g.setColor(c);
				g.fillRect(j, i, 1, 1);
			}
		}

		g.dispose();
		return bufferedImage;
	}
}
