package panels;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.HashMap;

import javax.swing.JPanel;

import base.IntervalNode;
import base.IntervalTree;
import base.Rational;

public class ShannonPanel extends JPanel implements MouseListener, MouseMotionListener {

	private static final long serialVersionUID = 1L;

	private ArrayList<Rational> points;
	private ArrayList<Rational> weights;
	
	private ArrayList<Rational> probabilities;
	
	private int offsetX;
	private int offsetY;
	
	private int mx;
	private int my;

	private IntervalNode rootNode;
	private IntervalTree intervalTree;
	
	public static HashMap<Integer, String> codeMap;
	
	private DecimalFormat decimalFormat;
	
	// code table flag
	private boolean showCodeTable;
	
	private String errorMessage;
	
	public ShannonPanel() {
		setBackground(Color.white);
		
		codeMap = new HashMap<Integer, String>();
		
		decimalFormat = new DecimalFormat("0.000000");
		
		addMouseMotionListener(this);
		addMouseListener(this);
	}

	public void setValues(ArrayList<Rational> weights, ArrayList<Rational> points, ArrayList<Rational> probabilities) {
		this.weights = weights;
		this.points = points;
		this.probabilities = probabilities;

		// Convert to arrays
		Rational[] weightArray = new Rational[weights.size()];
		Rational[] pointArray  = new Rational[points.size()];
		
		weights.toArray(weightArray);
		points.toArray(pointArray);
		
		// Create root node
		rootNode = new IntervalNode(new Rational(0, 1), new Rational(1, 1), weightArray, pointArray);
		
		offsetX = 360;
		offsetY = 80;

		createTree();
	}

	public void createTree() {
		
		if (rootNode == null) {
			repaint();
			return;
		}
		
		// Remove childs
		rootNode.removeAllChild();
		
		// Clear code map
		codeMap.clear();
		
		// Create tree
		rootNode.extend("");

		intervalTree = new IntervalTree(rootNode);

		repaint();
	}

	public void setShowCodeTable(boolean newState) {
		showCodeTable = newState;
	}
	
	public void setErrorMessage(String errorMessage) {
		this.errorMessage = errorMessage;
		repaint();
	}
	
	@Override
	protected void paintComponent(Graphics g){
		super.paintComponent(g);

		// Show error messages
		if (errorMessage != null) {
			g.setColor(Color.red);
			g.drawString(errorMessage, 40, 50);
			return;
		}
		
		// Draw tree
		if (intervalTree != null) {
			intervalTree.draw(g, offsetX, offsetY);
		}

		if (showCodeTable && points != null) {
			// Draw frame
			g.setColor(new Color(250, 250, 255));
			g.fillRect(20, 20, 180, points.size() * 35 + 10);

			g.setColor(new Color(100, 100, 200));
			g.drawRect(20, 20, 180, points.size() * 35 + 10);

			// Draw point values and calculate average code length
			Rational L = Rational.ZERO;
			g.setColor(Color.gray);
			for (int i = 0; i < points.size(); i++) {
				Rational p = points.get(i);
				L = L.add(probabilities.get(i).multiply(new Rational(codeMap.get(i).length(), 1)));
				p.draw(g, 30, i * 35 + 40 - p.getHeight(g) / 2);
			}
			
			// Draw symbols
			g.setColor(Color.blue);
			for (int i = 0; i < points.size(); i++) {
				g.drawString("x" + (i + 1) + "*  -->  " + codeMap.get(i), 70, i * 35 + 45);
			}
			
			// Draw average code length
			g.setColor(new Color(255, 255, 220));
			g.fillRect(640, 20, 140, 40);

			g.setColor(new Color(200, 200, 100));
			g.drawRect(640, 20, 140, 40);

			g.setColor(Color.black);
						
			g.drawString("L = " + (decimalFormat.format(L.getDouble())).replace(',', '.'), 660, 45);
		}
	}
	
	@Override
	public void mouseClicked(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseEntered(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseExited(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mousePressed(MouseEvent me) {
		mx = me.getX();
		my = me.getY();		
	}

	@Override
	public void mouseReleased(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseDragged(MouseEvent me) {
		offsetX += me.getX() - mx;
		offsetY += me.getY() - my;
		mx = me.getX();
		my = me.getY();
		repaint();
	}

	@Override
	public void mouseMoved(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}
}
