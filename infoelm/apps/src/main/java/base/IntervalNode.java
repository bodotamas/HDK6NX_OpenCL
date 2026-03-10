package base;

import java.awt.Color;
import java.awt.Graphics;
import java.util.ArrayList;

import panels.ShannonPanel;

public class IntervalNode extends Node {

	// Interval [a, b]
	private Rational a;
	private Rational b;
	
	// Additive cost -> weights of the symbols
	Rational[] symbolWeights;
	
	// Points on [0, 1] interval
	Rational[] points;
	
	// Width of interval for drawing
	int intervalWidth;
	
	// Relative position
	int x;
	int y;
	
	// Store code of derivation for calculate codes
	private int derivationCode;
	
	// Code tree mode
	private static boolean codeTreeMode;
		
	public static void setCodeTreeMode(boolean mode) {
		codeTreeMode = mode;
	}
	
	public void setDerivationCode(int code) {
		derivationCode = code;
	}
	
	public int getDerivationCode() {
		return derivationCode;
	}
	
	public IntervalNode(Rational a, Rational b, Rational[] symbolWeights, Rational[] points) {
		try {
			// Set members
			setInterval(a, b);
			setSymbolWeights(symbolWeights);
			setPoints(points);
		}
		catch (Exception e) {
			System.err.println(e.toString());
		}
		
		intervalWidth = 400;
			
		x = 0;
		y = 0;
	}

	/**
	 * Set the [a, b] interval
	 * 
	 * @return with true on success, and false when the input is invalid
	 */
	public void setInterval(Rational a, Rational b) throws Exception {
		// Check parameters
		if (a.compareTo(Rational.ZERO) < 0 || b.compareTo(Rational.ONE) > 0) {
			throw new Exception("IntervalNode::setInterval - Invalid [a, b] interval !  [" + a + ", " + b + "]");
		}
		
		// Set new values
		this.a = a;
		this.b = b;
	}
	
	/**
	 * Set the weights, for interval division
	 * 
	 * @param symbolWeights the weights of symbols
	 * @throws Exception
	 */
	public void setSymbolWeights(Rational[] symbolWeights) throws Exception {
		// Check, that weights are correct
		Rational sum = Rational.ZERO;
		for (int i = 0; i < symbolWeights.length; i++) {
			sum = sum.add(symbolWeights[i]);
		}
		
		if (sum.compareTo(Rational.ONE) != 0) {
			throw new Exception("IntervalNode::setSymbol - The sum of weights are not equals with 1 !  sum = " + sum);
		}

		this.symbolWeights = symbolWeights;
	}

	/**
	 * Set the points for coding
	 * 
	 * @param points list of points on [0, 1] interval
	 * @throws Exception
	 */
	public void setPoints(Rational[] points) throws Exception {
		// Check point list
		for (int i = 0; i < points.length; i++) {
			if (points[i].compareTo(Rational.ZERO) < 0 || points[i].compareTo(Rational.ONE) > 0) {
				throw new Exception("IntervalNode::setPoints - Invalid point value !  points[" + i + "] = " + points[i]);
			}
		}
		
		this.points = points;
	}

	/**
	 * Extend interval node, and build full code tree
	 */
	public void extend(String code) {
		// Length of interval
		Rational intervalLength = b.subtract(a);
		
		// Get subintervals
		Rational subIntervalA = null;
		Rational subIntervalB = a;
		
		for (int intervalIndex = 0; intervalIndex < symbolWeights.length; intervalIndex++) {
			// Step interval
			subIntervalA = subIntervalB;
			subIntervalB = subIntervalB.add(symbolWeights[intervalIndex].multiply(intervalLength));
						
			// Collect points in interval
			ArrayList<Rational> pointList = new ArrayList<Rational>();
			int pointIndex = 0;
			for (int i = 0; i < points.length; i++) {
				Rational p = points[i];
				if (p.compareTo(subIntervalA) >= 0 && p.compareTo(subIntervalB) < 0) {
					pointList.add(p);
					pointIndex = i;
				}
			}
			
			// Store code word
			if (pointList.size() == 1) {
				ShannonPanel.codeMap.put(pointIndex, code + intervalIndex);
			}
			
			int isLeafless = 1;
			if (codeTreeMode == true) isLeafless = 0;

			if (pointList.size() > isLeafless) {
				// Create new interval node
				IntervalNode newNode = new IntervalNode(subIntervalA, subIntervalB, symbolWeights, points);

				// Extend interval recursively
				if (pointList.size() > 1) {
					newNode.extend(code + intervalIndex);
				}
				
				// Set derivation code
				newNode.setDerivationCode(intervalIndex);
				
				// Add node to child list
				add(newNode);
			}
		}
	}
	
	/**
	 * Draw interval node at given position
	 * 
	 * @param g graphics context
	 * @param x coordinate x as integer value
	 * @param y coordinate y as integer value
	 */
	public void draw(Graphics g, int posX, int posY) {

		if (codeTreeMode) {
			intervalWidth = 40;
		}
		else {
			intervalWidth = 400;			
		}

		int paddingTop = 30;
		int paddingLeft = 20;
		
		int a_x = posX + paddingLeft;
		int a_y = posY + paddingTop;
		int b_x = a_x + intervalWidth;
		int b_y = a_y;
		
		// Draw frame
		g.setColor(new Color(250, 250, 250));
		g.fillRect(posX, posY, intervalWidth + 40, 80);
		
		g.setColor(new Color(220, 220, 220));
		g.drawRect(posX, posY, intervalWidth + 40, 80);
		
		if (codeTreeMode == true) {
			// Draw code tree node
			String nodeLabel = "";
			int firstIndex = -1;
			int lastIndex = -1;
			for (int i = 0; i < points.length; i++) {
				Rational r = points[i];
				if (r.compareTo(a) >= 0 && r.compareTo(b) < 0) {
					if (firstIndex == -1) firstIndex = i;
					lastIndex = i;
				}
			}
			
			firstIndex++;
			lastIndex++;
			
			if (firstIndex < lastIndex) {
				g.setColor(Color.red);
				int nPoints = lastIndex - firstIndex + 1;
				if (nPoints < 3) {
					nodeLabel = "x" + firstIndex + "*, x" + lastIndex + "*";
					a_x = 15;
				}
				else {
					nodeLabel = "x" + firstIndex + "*, ... , x" + lastIndex + "*";
					a_x = 5;
				}
			}
			else {
				g.setColor(Color.blue);
				nodeLabel = "x" + firstIndex + "*";
				a_x = 30;
			}
			g.drawString(nodeLabel, posX + a_x, posY + 45);
		}
		else {
			// Draw interval baseline
			g.setColor(Color.black);
			g.drawLine(a_x, a_y, b_x, b_y);
			g.drawLine(a_x, a_y - 7, a_x, a_y + 7);
			g.drawLine(b_x, b_y - 7, b_x, b_y + 7);
			
			// Draw subdivision
			Rational sum = new Rational(0, 1);
			Rational labelSum = a;
			int tick_x;
			g.setColor(new Color(140, 140, 140));
			for (int i = 0; i < symbolWeights.length - 1; i++) {
				sum = sum.add(symbolWeights[i]);
				labelSum = labelSum.add(symbolWeights[i].multiply(b.subtract(a)));
				tick_x = (int)(a_x + intervalWidth * sum.getDouble());
				g.drawRect(tick_x, b_y - 5, 0, 10);
				labelSum.draw(g, tick_x - (labelSum.getWidth(g) / 2), b_y + 7);
			}
			
			// Draw labels at end points
			g.setColor(Color.black);
			a.draw(g, a_x - (a.getWidth(g) / 2), a_y + 7);
			b.draw(g, b_x - (b.getWidth(g) / 2), b_y + 7);
					
			// Draw points
			g.setColor(Color.red);		
			for (int i = 0; i < points.length; i++) {
				Rational p = points[i];
				if (p.compareTo(a) >= 0 && p.compareTo(b) < 0) {
					tick_x = (int)(a_x + intervalWidth * (p.getDouble() - a.getDouble()) / (b.getDouble() - a.getDouble()));
					g.drawRect(tick_x, b_y - 5, 0, 10);
					g.drawString("x" + (i + 1) + "*", tick_x - 4, a_y - 10);
				}
			}
		}
	}
	
	// Get width of node in pixels
	public int getWidth() {
		// NOTE: QuickFix !!!
		if (codeTreeMode) return 80;
		return 440;
		
		// return intervalWidth + 40;
	}
	
	// Get relative x coordinate
	public int getX() {
		return x;
	}

	// Get relative y coordinate
	public int getY() {
		return y;
	}

	// Set relative x coordinate
	public void setX(int x) {
		this.x = x;
	}

	// Set relative y coordinate
	public void setY(int y) {
		this.y = y;
	}
}
