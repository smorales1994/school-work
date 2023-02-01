public class MandelbrotTask implements Runnable
{
    private double x1, y1, x2, y2;
    private int startCol, endCol, startRow, endRow;
    private int[][] iterCounts;

	// TODO: Add constructor to set bounds for task
    public MandelbrotTask(double x1, double y1, double x2, double y2, int startCol, int endCol, int startRow, int endRow, int[][] iterCounts)
	{
		this.x1 = x1;
		this.y1 = y1;
		this.x2 = x2;
		this.y2 = y2;
		this.startCol = startCol;
		this.endCol = endCol;
		this.startRow = startRow;
		this.endRow = endRow;
		this.iterCounts = iterCounts;
	}

	// Method to compute all iteration counts for region
	public void run()
	{
		// TODO: Loop over array extents to compute iterations for each point
		for (int i = startRow; i < endRow; i++)
		{
			for (int j = startCol; j < endCol; j++)
			{
				Complex c = getComplex(i, j);
				int iterCount = computeIterCount(c);
				iterCounts[i][j] = iterCount;
			}
		}
	}

	// Method to determine the number of iterations beginning with value c
	public int computeIterCount(Complex c)
	{
		int count = 0;

		// Reference created to represent the mandelbrot equation; will be iterated in the loop below to find out the number of iterations for each point.
		Complex z = new Complex (0, 0);

		// TODO: Iterate Mandelbrot equation up to Mandelbrot.THRESHOLD
		while (z.getMagnitude() <= 2 && count < Mandelbrot.THRESHOLD)
		{
			z = z.mult(z).add(c);

			count ++;
		}

		return count;
	}
	
	// Method to determine the complex value from the bounds and array indicies
	public Complex getComplex(int row, int col)
	{
		Complex c;

		// TODO: Compute the complex value from the region bounds and
		//       the given array indicies
		c = new Complex (x1 + col * (x2 - x1) / (iterCounts[row].length - 1), y2 - row * (y2 - y1) / (iterCounts.length - 1));

		return c;
	}
}
