package base;

import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics;
import java.awt.geom.Rectangle2D;
import java.util.ArrayList;

/**
 * Rational number in (p / q) form,
 * where p, q is an integer, and q > 0.
 * 
 * @author Piller Imre
 */
public class Rational {

	// Numerator and denominator
	private long p;
	private long q;
	
	private static int parserIndex;
	
	// Common values
	public static final Rational ZERO = new Rational(0, 1);
	public static final Rational ONE  = new Rational(1, 1);
	
	// Font settings
	Font font;
	FontMetrics fontMetrics;
	
	// Name of value when use as symbol
	private String valueName;

	/**
	 * Construct zero valued rational number
	 */
	public Rational() {	
		p = 0;
		q = 1;

		loadFont();
	}

	/**
	 * Construct (p / q) rational number
	 * 
	 * @param p numerator
	 * @param q denominator
	 */
	public Rational(long p, long q) {
		set(p, q);
		simplify();

		loadFont();
	}

	/**
	 * Load font and font metrics for drawing
	 */
	private void loadFont() {
		font = new Font("Verdana", Font.PLAIN, 12);
		fontMetrics = new FontMetrics(font) {};
	}
	
	// Get numerator p
	public long getP() {
		return p;
	}
	
	// Get denominator q
	public long getQ() {
		return q;
	}
	
	/**
	 * Set rational value
	 * 
	 * @param p nominator
	 * @param q denominator
	 */
	public void set(long p, long q) {
		if (q != 0) {
			this.p = p;
			this.q = q;
		}
		else {
			// Invalid q value !
			System.err.println("Invalid q value !");
		}		
	}
	
	/**
	 * Greatest Common Divisor of a and b integer values
	 * 
	 * @param a integer value
	 * @param b integer value
	 * @return the greatest common divisor
	 */
	private long gcd(long a, long b) {
		while (b != 0) {
			long t = b;
			b = a % b;
			a = t;
		}

		return a;
	}
	
	/**
	 * Try to simplify
	 */
	private void simplify() {
		if (p == 0) {
			q = 1;
			return;
		}
		
		long m = gcd(p, q);
		p = p / m;
		q = q / m;
		
		if (q < 0) {
			p = -p;
			q = -q;
		}
	}
	
	// Addition
	public Rational add(Rational x) {
		Rational y = new Rational(p * x.q + q * x.p, q * x.q);
		y.simplify();
		return y;
	}

	// Subtraction
	public Rational subtract(Rational x) {
		Rational y = new Rational(p * x.q - q * x.p, q * x.q);
		y.simplify();
		return y;
	}
	
	// Multiplication
	public Rational multiply(Rational x) {
		Rational y = new Rational(p * x.p, q * x.q);
		y.simplify();
		return y;
	}
	
	// Division
	public Rational divide(Rational x) {
		Rational y = new Rational(p * x.q, q * x.p);
		y.simplify();
		return y;
	}
	
	/**
	 * Compare value with the x rational number
	 * 
	 * @param x rational value for comparison
	 * @return 0 when the number equals with x, -1 when lower and 1 when greater.
	 */
	public int compareTo(Rational x) {
		// Use common denominator
		long a = this.p * x.q;
		long b = this.q * x.p;
		
		if (a < b) {
			return -1;
		}
		else if (a == b) {
			return 0;
		}
		else {
			return 1;
		}
	}
	
	// Check, that the character is a number
	private static boolean isNumeric(char c) {
		return (c >= '0' && c <= '9');
	}
	
	/**
	 * Read the first rational numbers from string.
	 * 
	 * @param string rational number as a text
	 * @param index start index for parsing
	 * @return the rational number, or null when cannot found.
	 */
	public static Rational parse(String string, int index) {
		// Set start index for parsing
		parserIndex = index;

		int p = 0;
		int q = 1;
		
		while (parserIndex < string.length() && isNumeric(string.charAt(parserIndex)) == false && string.charAt(parserIndex) != '.') {
			parserIndex++;
		}

		if (parserIndex == string.length()) {
			// There is no valid rational number in string
			return null;
		}
		
		if (string.charAt(parserIndex) == '.') {
			parserIndex++;
			
			if (parserIndex == string.length()) {
				// Invalid number format !  "  ."
				return null;
			}
			
			if (isNumeric(string.charAt(parserIndex)) == false) {
				// Invalid number format !  " . "
				return null;
			}
			
			while (parserIndex < string.length() && isNumeric(string.charAt(parserIndex)) == true) {
				p *= 10;
				p += string.charAt(parserIndex) - '0';
				q *= 10;
				parserIndex++;
			}
		}
		else {
			while (parserIndex < string.length() && isNumeric(string.charAt(parserIndex)) == true) {
				p *= 10;
				p += string.charAt(parserIndex) - '0';
				parserIndex++;
			}

			if (parserIndex == string.length()) {
				return new Rational(p, q);
			}

			if (string.charAt(parserIndex) == '.') {
				parserIndex++;
				if (isNumeric(string.charAt(parserIndex)) == false) {
					// Invalid number format !  " ###. "
					return null;
				}
				
				while (parserIndex < string.length() && isNumeric(string.charAt(parserIndex)) == true) {
					p *= 10;
					p += string.charAt(parserIndex) - '0';
					q *= 10;
					parserIndex++;
				}				
			}
			else {
				while ( parserIndex < string.length() &&
						isNumeric(string.charAt(parserIndex)) == false &&
						string.charAt(parserIndex) != '/' ) {
					parserIndex++;
				}
				
				if (parserIndex == string.length()) {
					return new Rational(p, q);
				}
				
				if (string.charAt(parserIndex) == '/') {
					parserIndex++;
					
					if (parserIndex == string.length()) {
						// Invalid number format !  " ### /"
						return null;
					}
					
					while (parserIndex < string.length() && isNumeric(string.charAt(parserIndex)) == false) {
						parserIndex++;
					}
					
					if (parserIndex == string.length()) {
						// Invalid number format !  " ### /  "
						return null;
					}
					
					q = 0;
					while (parserIndex < string.length() && isNumeric(string.charAt(parserIndex)) == true) {
						q *= 10;
						q += string.charAt(parserIndex) - '0';
						parserIndex++;
					}
					
					// division by zero
					if (q == 0) {
						return null;
					}
				}
			}
		}

		return new Rational(p, q);
	}
	
	// Parse string from the beginning
	public static Rational parse(String string) {
		return parse(string, 0);
	}
	
	/**
	 * Read list of rational values from string.
	 * 
	 * @param string the rational number list as a text
	 * @param index start index for parsing
	 * @return a list of rational numbers. An empty list when not found.
	 */
	public static ArrayList<Rational> parseList(String string) {
		// Create new list
		ArrayList<Rational> valueList = new ArrayList<Rational>();
		
		// Parse from the beginning
		parserIndex = 0;
		
		// Read list
		while (parserIndex < string.length()) {
			Rational rational = Rational.parse(string, parserIndex);
			if (rational != null) {
				valueList.add(rational);
			}
			else if (parserIndex != string.length()) {
				return null;
			}
		}

		// Avoid empty lists
		if (valueList.size() == 0) {
			return null;
		}
		
		return valueList;
	}
	
	/**
	 * Check that the given number is an integer power of ten, or not.
	 * 
	 * @param non negative integer value
	 * @return true, when the number can be written in 10^k form, else false.
	 */
	private boolean isPowerOfTen(long n) {
		if (n <= 9) return false;
		while (n % 10 == 0) n /= 10;
		return (n == 1);
	}
	
	/**
	 * Get decimal pointed form of a rational number
	 * 
	 * @return decimal pointed number as a string
	 */
	private String getPointedFormat() {
		String numberString = "";
		if (p < q) {
			numberString = "0.";
			long pTemp = p;
			pTemp *= 10;
			while (pTemp < q) {
				numberString += "0";
				pTemp *= 10;
			}
			while (pTemp % 10 == 0) pTemp /= 10;
			numberString += pTemp;
		}
		else {
			// Get integer part
			long a = p / q;
			p %= q;
			numberString = "" + a + ".";
			long pTemp = p;
			pTemp *= 10;
			while (pTemp < q) {
				numberString += "0";
				pTemp *= 10;
			}
			while (pTemp % 10 == 0) pTemp /= 10;
			numberString += pTemp;
		}
		
		return numberString;
	}
	
	/**
	 * Draw rational number at given position
	 * 
	 * @param g Graphics reference for drawing
	 * @param x coordinate x
	 * @param y coordinate y
	 */
	public void draw(Graphics g, int x, int y) {		
		// Set font
		g.setFont(font);
		
		if (q == 1) {
			Rectangle2D pBounds = fontMetrics.getStringBounds("" + p, g);
			g.drawString("" + p, x, (int)(y + pBounds.getHeight()));
		}
		else if (isPowerOfTen(q) == true) {
			String numberString = getPointedFormat();
			Rectangle2D pBounds = fontMetrics.getStringBounds(numberString, g);
			g.drawString(numberString, x, (int)(y + pBounds.getHeight()));
		}
		else {
			Rectangle2D pBounds = fontMetrics.getStringBounds("" + p, g);
			Rectangle2D qBounds = fontMetrics.getStringBounds("" + q, g);
			
			if (pBounds.getWidth() > qBounds.getWidth()) {
				g.drawString("" + p, x, (int)(y + pBounds.getHeight()));
				g.drawLine(x, (int)(y + pBounds.getHeight()) + 2, (int)(x + pBounds.getWidth()), (int)(y + pBounds.getHeight()) + 2);
				g.drawString("" + q, (int)(x + (pBounds.getWidth() - qBounds.getWidth()) / 2), (int)(y + pBounds.getHeight() + qBounds.getHeight()));
			}
			else {
				g.drawString("" + p, (int)(x + (qBounds.getWidth() - pBounds.getWidth()) / 2), (int)(y + pBounds.getHeight()));
				g.drawLine(x, (int)(y + pBounds.getHeight()) + 2, (int)(x + qBounds.getWidth()), (int)(y + pBounds.getHeight()) + 2);
				g.drawString("" + q, x, (int)(y + pBounds.getHeight() + qBounds.getHeight()));				
			}
		}
	}
	
	/**
	 * Get width of rational number in pixel for drawing
	 * 
	 * @return width in pixels.
	 */
	public int getWidth(Graphics g) {
		if (q == 1) {
			Rectangle2D pBounds = fontMetrics.getStringBounds("" + p, g);
			return (int)pBounds.getWidth();
		}
		else if (isPowerOfTen(q) == true) {
			String numberString = getPointedFormat();
			Rectangle2D pBounds = fontMetrics.getStringBounds(numberString, g);
			return (int)pBounds.getWidth();
		}
		else {
			Rectangle2D pBounds = fontMetrics.getStringBounds("" + p, g);
			Rectangle2D qBounds = fontMetrics.getStringBounds("" + q, g);
			
			if (pBounds.getWidth() > qBounds.getWidth()) {
				return (int)pBounds.getWidth();
			}
			else {
				return (int)pBounds.getHeight();
			}
		}
	}
	
	/**
	 * Get height of rational number in pixel for drawing
	 * 
	 * @return height in pixels.
	 */
	public int getHeight(Graphics g) {
		if (q == 1) {
			Rectangle2D pBounds = fontMetrics.getStringBounds("" + p, g);
			return (int)pBounds.getHeight();
		}
		else if (isPowerOfTen(q) == true) {
			String numberString = getPointedFormat();
			Rectangle2D pBounds = fontMetrics.getStringBounds(numberString, g);
			return (int)pBounds.getHeight();
		}
		else {
			Rectangle2D pBounds = fontMetrics.getStringBounds("" + p, g);
			Rectangle2D qBounds = fontMetrics.getStringBounds("" + q, g);
			
			return (int)(pBounds.getHeight() + qBounds.getHeight());
		}
	}
	
	/**
	 * Print rational number in string format
	 */
	public String toString() {
		String string;
		if (q == 1) {
			string = "" + p;
		}
		else if (isPowerOfTen(q) == true) {
			string = getPointedFormat();
		}
		else {
			string = "" + p + "/" + q;
		}
		return string;
	}

	/**
	 * Get approximate double value of the rational number.
	 * 
	 * @return approximate double value
	 */
	public double getDouble() {
		return (double)p / q;
	}
	
	// Get name of the value
	public String getName() {
		return valueName;
	}

	// Set name of the value
	public void setName(String name) {
		valueName = name;
	}
	
	// Sort elements of list
	public static ArrayList<Rational> sort(ArrayList<Rational> list, String direction) {
		Rational temp;
		if ("ascending".equals(direction)) {
			for (int i = 0; i < list.size() - 1; i++) {
				int minIndex = i;
				for (int k = i; k < list.size(); k++) {
					if (list.get(k).compareTo(list.get(minIndex)) < 0) {
						minIndex = k;
					}
				}
				temp = list.get(i);
				list.set(i, list.get(minIndex));
				list.set(minIndex, temp);
			}
		}
		else {
			for (int i = 0; i < list.size() - 1; i++) {
				int maxIndex = i;
				for (int k = i; k < list.size(); k++) {
					if (list.get(k).compareTo(list.get(maxIndex)) > 0) {
						maxIndex = k;
					}
				}
				temp = list.get(i);
				list.set(i, list.get(maxIndex));
				list.set(maxIndex, temp);
			}			
		}
		
		return list;
	}
}
