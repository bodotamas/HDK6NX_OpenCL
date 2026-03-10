package base;

import java.awt.Color;
import java.awt.Graphics;

public class HuffmanNode extends Node {	

	private Rational probability;

	private int x;
	private int y;
	
	public void setProbability(Rational p) {
		probability = p;
	}
	
	public Rational getProbability() {
		return probability;
	}
	
	public void setX(int x) { this.x = x; }
	public int getX() { return x; }

	public void setY(int y) { this.y = y; }
	public int getY() { return y; }

	// Calculate number of elements at the first pick
	public static int getFirstPickCount(int n, int m) {
		int a = n % (m - 1);
		int k = 2;
		while (k % (m - 1) != a) k++;
		return k;
	}
	
	public void draw(Graphics g) {
		g.setColor(new Color(240, 240, 250));
		g.fillOval(x - 25, y - 25, 50, 50);

		g.setColor(new Color(210, 210, 255));
		g.drawOval(x - 25, y - 25, 50, 50);
		
		g.setColor(Color.black);
		probability.draw(g, x - probability.getWidth(g) / 2, y - probability.getHeight(g) / 2);
	}
}
