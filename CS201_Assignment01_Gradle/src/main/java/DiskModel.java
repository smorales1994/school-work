import java.util.ArrayList;

/**
 * The model for the disk game
 * which stores and ArrayList of Disks
 */
public class DiskModel
{
	// Initialized private field
	private ArrayList <Disk> disks;

	// Constructor to create empty array list for number of disks placed.
	public DiskModel()
	{
		disks = new ArrayList <Disk>();
	}

	// Returns ArrayList object of disks.
	public ArrayList<Disk> getDisks()
	{
		return disks;
	}

	// Returns number of placed disks.
	public int getNumDisks()
	{
		return disks.size();
	}

	// Adds a new disk to the array list once the user places their current one.
	public void addDisk(Disk disk)
	{
		disks.add(disk);
	}

}
