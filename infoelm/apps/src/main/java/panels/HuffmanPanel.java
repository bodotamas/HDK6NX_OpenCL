package panels;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;

import javax.swing.JPanel;

import base.HuffmanNode;
import base.Rational;

import java.text.DecimalFormat;
import java.util.ArrayList;

public class HuffmanPanel extends JPanel implements MouseListener, MouseMotionListener {

	private static final long serialVersionUID = 1L;

	private int s;
	private ArrayList<Rational> probabilities;
	
	private int offsetX;
	private int offsetY;
	
	private int mx;
	private int my;
	
	// Average code length
	private Rational L;
	
	private DecimalFormat decimalFormat;

	private String errorMessage;

	public HuffmanPanel() {
		setBackground(Color.white);
		
		decimalFormat = new DecimalFormat("0.000000");

		addMouseMotionListener(this);
		addMouseListener(this);
	}
	
	public void setValues(int s, ArrayList<Rational> probabilities) {
		this.s = s;
		this.probabilities = probabilities;

		offsetX = 240;
		offsetY = 80;

		repaint();
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

		// Return when probability not set yet
		if (probabilities == null) return;
		
		probabilities = Rational.sort(probabilities, "descending");
		
		// Create Huffman node list
		ArrayList<HuffmanNode> nodeList = new ArrayList<HuffmanNode>();
		for (int i = 0; i < probabilities.size(); i++) {

			HuffmanNode node = new HuffmanNode();
			node.setProbability(probabilities.get(i));
			node.setX(offsetX);
			node.setY(i * 80 + offsetY);
			
			nodeList.add(node);
		}
				
		int pickCount = 2;

		// Handle non binary cases
		if (s > 2) pickCount = HuffmanNode.getFirstPickCount(probabilities.size(), s);
		
		while (nodeList.size() > 1) {
			// pick nodes
			HuffmanNode[] pickables = new HuffmanNode[pickCount];
			for (int i = 0; i < pickCount; i++) {
				pickables[i] = nodeList.get(i);
			}
			
			for (int i = pickCount; i < nodeList.size(); i++) {
				// Get index of maximal value in pickables
				int maxIndex = 0;
				for (int k = 1; k < pickCount; k++) {
					if (pickables[k].getProbability().compareTo(pickables[maxIndex].getProbability()) > 0) {
						maxIndex = k;
					}
				}
				
				if (nodeList.get(i).getProbability().compareTo(pickables[maxIndex].getProbability()) < 0) {
					// Swap node in pickables
					pickables[maxIndex] = nodeList.get(i); 
				}
			}

			// sort pickables
			HuffmanNode temp;
			for (int i = 0; i < pickCount - 1; i++) {
				int minIndex = i;
				for (int k = i; k < pickCount; k++) {
					if (pickables[k].getY() < pickables[minIndex].getY()) {
						minIndex = k;
					}
				}
				temp = pickables[i];
				pickables[i] = pickables[minIndex];
				pickables[minIndex] = temp;
			}
			
			// create new node
			Rational sum = Rational.ZERO;
			int y = 0;
			for (int i = 0; i < pickCount; i++) {
				sum = sum.add(pickables[i].getProbability());
				y += pickables[i].getY();
			}
			y /= pickCount;
			y = (int)(0.4 * y + 0.6 * pickables[0].getY());
			
			HuffmanNode newNode = new HuffmanNode();
			newNode.setProbability(sum);

			// Get maximal x value of pickables
			int maxX = -9999;
			for (int i = 0; i < pickCount; i++) {
				if (pickables[i].getX() > maxX) maxX = pickables[i].getX();
			}
			
			// Set (x, y) position of new node
			newNode.setX(maxX + 100);
			newNode.setY(y);
			
			// Set child nodes
			for (int i = 0; i < pickCount; i++) {
				newNode.add(pickables[i]);
			}
			
			// remove picked nodes from list
			for (int i = 0; i < pickCount; i++) {
				nodeList.remove(pickables[i]);
			}

			// add new node to list
			nodeList.add(newNode);
			
			// Draw tree
			for (int i = 0; i < newNode.getChildNumber(); i++) {
				HuffmanNode child = (HuffmanNode)newNode.get(i);
				int x1 = newNode.getX();
				int y1 = newNode.getY();
				int x2 = child.getX();
				int y2 = child.getY();				
				
				g.setColor(new Color(0, 0, 100));
				g.drawLine(x1, y1, x2, y2);

				g.setColor(Color.blue);
				g.drawString("" + i, (x1 + x2) / 2, (y1 + y2) / 2 - 5);
			}
			
			// Set pick count for next iteration
			pickCount = s;
		}
		
		// Draw nodes recursively and calculate average code length
		L = Rational.ZERO;
		
		recursiveDrawer(g, nodeList.get(0), "");
		
		// Draw average code length
		g.setColor(new Color(255, 255, 220));
		g.fillRect(640, 20, 140, 40);

		g.setColor(new Color(200, 200, 100));
		g.drawRect(640, 20, 140, 40);

		g.setColor(Color.black);
		g.drawString("L = " + (decimalFormat.format(L.getDouble())).replace(',', '.'), 660, 45);
	}
	
	private void recursiveDrawer(Graphics g, HuffmanNode node, String code) {
		// Draw node
		node.draw(g);
		
		for (int i = 0; i < node.getChildNumber(); i++) {
			recursiveDrawer(g, (HuffmanNode)node.get(i), code + i);
		}
		
		// Draw code labels
		if (node.getChildNumber() == 0) {
			g.setColor(Color.red);
			g.drawString(code, node.getX() - 70, node.getY());

			// Calculate L
			L = L.add(node.getProbability().multiply(new Rational(code.length(), 1)));
		}
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

	@Override
	public void mouseClicked(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseEntered(MouseEvent me) {
		// TODO Auto-generated method stub
	}

	@Override
	public void mouseExited(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mousePressed(MouseEvent me) {
		mx = me.getX();
		my = me.getY();		
	}

	@Override
	public void mouseReleased(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}
}
