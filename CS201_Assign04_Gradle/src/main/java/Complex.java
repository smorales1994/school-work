public class Complex
{
	private double real, imag;
	
	public Complex(double real, double imag)
	{
		this.real = real;
		this.imag = imag;
	}
	
	public double getReal()
	{
		return real;
	}
	
	public double getImag()
	{
		return imag;
	}

    // Method to add given complex number to this one, returning the Complex result	
	public Complex add(Complex other)
	{
		Complex sum;
		
		// TODO: Compute sum of complex numbers
		//       (a + bi) + (c + di) = (a+c) + (b+d)i
		sum = new Complex (real + other.getReal(), imag + other.getImag());
		
		return sum;
	}

    // Method to multiply given complex number to this one, returning the Complex result		
	public Complex mult(Complex other)
	{
		Complex product;
		
		// TODO: Compute product of complex numbers
		//       (a + bi)(c + di) = (ac - bd) + (bc + ad)i
		product = new Complex (real * other.getReal() - (imag * other.getImag()), imag * other.getReal() + real * other.getImag());
		
		return product;
	}

    // Method to get the magnitude of this complex number		
	public double getMagnitude()
	{
		double mag = 0.0;
		
		// TODO: Compute magnitude of a complex number
		//       |(a + bi)| = sqrt(a^2 + b^2)
		mag = Math.sqrt((real * real) + (imag * imag));
		
		return mag;
	}
}
