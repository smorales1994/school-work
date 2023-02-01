/**
 * An instance of the Disk class represents a disk
 * to be placed on the game board.
 */

// I went to CS201 tutoring on 2/3/2022 and Josh Snyder helped me to figure out how to finish up the isOutOfBounds function, along with tips on cleaning up my code for readability and removing redundant variables.
public class Disk
{
	private double x, y, radius; // Adding private fields for Disk class.
	private DiskColor color;    // Adding private field for Disk class.

	public Disk(double x, double y, double radius, DiskColor color) // Constructor to store the values and initialize the objects in Disk class.
	{
		this.x = x;
		this.y = y;
		this.radius = radius;
		this.color = color;
	}

	public double getX() // Getter method to return x coordinate value.
	{
		return x;
	}

	public double getY() // Getter method to return y coordinate value.
	{
		return y;
	}

	public double getRadius() // Getter method to return radius value.
	{
		return radius;
	}

	public DiskColor getColor() // Getter method to return color value.
	{
		return color;
	}

	public boolean overlaps(Disk other)
	{
		double diskDistance = Math.sqrt(((x - other.x) * (x - other.x)) + ((y - other.y) * (y - other.y))); // Variable to store the distance calculation of the 2 disks.
		double radiusSum = radius + other.radius; // Variable to store the sum of the radius of the 2 disks.

		if (diskDistance < radiusSum) // Statement checking if the distance of the 2 disks is smaller than the radius sum of the 2 disks.
		{
			return true;
		}

		return false;
	}

	public boolean isOutOfBounds(double width, double height)
	{
		if (x + radius > width || x - radius < 0 || y + radius > height || y - radius < 0) // Statement checking if the disk will be out of bounds of the rectangle.
		{
			return true;
		}

		return false;
	}
}
