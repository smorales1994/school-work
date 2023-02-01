import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

public class MandelbrotTaskTest
{
	private MandelbrotTask t1;
	private static double eps = 0.001;
	
	@Before
	public void setUp() throws Exception
	{
		t1 = new MandelbrotTask(-1.2,-0.5, 2.0, 1.8, 0, 4, 0, 2, new int[3][5]);
	}
	
	@Test
	public void testGetComplex()
	{
		Complex c = t1.getComplex(0,0);
		assertEquals(-1.2, c.getReal(), eps);
		assertEquals(1.8, c.getImag(), eps);
		c = t1.getComplex(1,2);
		assertEquals(0.4, c.getReal(), eps);
		assertEquals(0.65, c.getImag(), eps);
		c = t1.getComplex(2,1);
		assertEquals(-0.4, c.getReal(), eps);
		assertEquals(-0.5, c.getImag(), eps);
		c = t1.getComplex(2,4);
		assertEquals(2.0, c.getReal(), eps);
		assertEquals(-0.5, c.getImag(), eps);
	}

	@Test
	public void testComputeIterCount()
	{
		assertEquals(Mandelbrot.THRESHOLD, t1.computeIterCount(new Complex(0,0)));
		assertEquals(1, t1.computeIterCount(new Complex(1.85,1.385)));
		assertEquals(37, t1.computeIterCount(new Complex(0.325,0.495)));
		assertEquals(103, t1.computeIterCount(new Complex(-0.905,-0.265)));
		assertEquals(Mandelbrot.THRESHOLD, t1.computeIterCount(new Complex(0.335,-0.565)));
	}
}
