import static org.junit.Assert.*;

import java.awt.Color;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Set;
import java.util.TreeMap;

import org.junit.Before;
import org.junit.Test;

public class ComplexTest
{
	
	private Complex a;
	private Complex b;	
	private static double eps = 0.001;
	
	@Before
	public void setUp() throws Exception
	{
 
		a = new Complex(2,3);
		b = new Complex(-4,1);
	}
	
	@Test
	public void testAdd()
	{
		Complex c = a.add(b);
		assertEquals(2.0+(-4.0), c.getReal(), eps);
		assertEquals(3.0+1.0, c.getImag(), eps);
	}

	@Test
	public void testMult()
	{
		Complex c = a.mult(b);
		assertEquals((2.0*(-4.0) - (3.0*1.0)), c.getReal(), eps);
		assertEquals((3.0*(-4.0) + (2.0*1.0)), c.getImag(), eps);
	}

	@Test
	public void testgetMagnitude()
	{
		assertEquals(Math.sqrt(2.0*2.0 + 3.0*3.0), a.getMagnitude(), eps);
		assertEquals(Math.sqrt((-4.0)*(-4.0) + 1.0*1.0), b.getMagnitude(), eps);
	}
}
