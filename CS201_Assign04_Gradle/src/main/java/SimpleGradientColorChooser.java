import java.awt.Color;

// Simple color chooser implementation using a gradient transitioning
// from blue (lower iteration counts) to green (higher iteration counts)
public class SimpleGradientColorChooser implements ColorChooser
{
	@Override
	public Color getColor(int iterCount)
	{
		if (iterCount == Mandelbrot.THRESHOLD)
		{
			return Color.BLACK;
		}

		else
		{
			double f = Math.log10(iterCount) / Math.log10(Mandelbrot.THRESHOLD);

			int g = (int)(f * 256);
			int b = 255 - ((int)f*256);

			g = constrainRange(g, 0, 255);
			b = constrainRange(b, 0, 255);

			return new Color(0, g, b);
		}
	}

	private int constrainRange(int val, int min, int max)
	{
		if (val < min)
		{
			return min;
		}

		else if (val > max)
		{
			return max;
		}

		else
		{
			return val;
		}
	}
}
