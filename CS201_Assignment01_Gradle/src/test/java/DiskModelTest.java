import static org.junit.Assert.*;

import java.util.ArrayList;

import org.junit.Before;
import org.junit.Test;

public class DiskModelTest {	
	private Disk disk1;
	private Disk disk2;
	private Disk disk3;
	private DiskModel emptyModel;
	private DiskModel fullModel;

	@Before
	public void setUp() throws Exception {
		disk1 = new Disk(100, 100, 20, DiskColor.RED);
		disk2 = new Disk(10, 20, 40, DiskColor.CYAN);
		disk3 = new Disk(20, 150, 30, DiskColor.GREEN);
		emptyModel = new DiskModel();
		fullModel = new DiskModel();
	}
	
	@Test
	public void testEmptyModel() throws Exception {
		assertEquals(0, emptyModel.getNumDisks());
		assertEquals(new ArrayList<Disk>(), emptyModel.getDisks());
		assertEquals(0, fullModel.getNumDisks());
		assertEquals(new ArrayList<Disk>(), fullModel.getDisks());
	}
	
	@Test
	public void testAdd1Disk() throws Exception {
		assertEquals(0, fullModel.getNumDisks());
		fullModel.addDisk(disk1);
		assertEquals(1, fullModel.getNumDisks());
		assertEquals(disk1, fullModel.getDisks().get(0));		
	}
	
	@Test
	public void testAdd2Disks() throws Exception {
		assertEquals(0, fullModel.getNumDisks());
		fullModel.addDisk(disk1);
		assertEquals(1, fullModel.getNumDisks());
		assertEquals(disk1, fullModel.getDisks().get(0));
		fullModel.addDisk(disk2);
		assertEquals(2, fullModel.getNumDisks());
		assertEquals(disk2, fullModel.getDisks().get(1));
	}
	
	@Test
	public void testAdd3Disks() throws Exception {
		assertEquals(0, fullModel.getNumDisks());
		fullModel.addDisk(disk1);
		assertEquals(1, fullModel.getNumDisks());
		assertEquals(disk1, fullModel.getDisks().get(0));
		fullModel.addDisk(disk2);
		assertEquals(2, fullModel.getNumDisks());
		assertEquals(disk2, fullModel.getDisks().get(1));
		fullModel.addDisk(disk3);
		assertEquals(3, fullModel.getNumDisks());
		assertEquals(disk3, fullModel.getDisks().get(2));
	}
}
