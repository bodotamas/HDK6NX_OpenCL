package base;

import java.awt.Color;
import java.awt.Graphics;
import java.util.ArrayList;

/**
 * Analyze and draw interval tree from interval nodes
 * 
 * @author Piller Imre
 */
public class IntervalTree {

	private IntervalNode rootNode;
	
	public IntervalTree(IntervalNode rootNode) {
		setRootNode(rootNode);
	}
	
	public void setRootNode(IntervalNode rootNode) {
		this.rootNode = rootNode;		
	}
	
	/**
	 * Draw interval tree at given position
	 * 
	 * @param g graphics context
	 * @param x coordinate x as integer
	 * @param y coordinate y as integer
	 */
	public void draw(Graphics g, int x, int y) {
		
		// Create rail for nodes
		ArrayList<IntervalNode> nodeRail = new ArrayList<IntervalNode>();
		
		nodeRail.add(rootNode);
		
		boolean hasChild = true;
		int relativeY = 0;
				
		while (hasChild == true) {
			hasChild = false;
		
			// Calculate width of rail and set x positions
			int railWidth = 0;
			nodeRail.get(0).setX(0);
			nodeRail.get(0).setY(relativeY);
			for (int nodeIndex = 0; nodeIndex < nodeRail.size(); nodeIndex++) {
				railWidth += nodeRail.get(nodeIndex).getWidth() + 40;
				if (nodeIndex < nodeRail.size() - 1) {
					nodeRail.get(nodeIndex + 1).setX(railWidth);
					nodeRail.get(nodeIndex + 1).setY(relativeY);					
				}
			}

			railWidth -= 40;
			
			// Align rail to center
			int leftShift = railWidth / 2;
			for (int nodeIndex = 0; nodeIndex < nodeRail.size(); nodeIndex++) {
				int relativeX = nodeRail.get(nodeIndex).getX();
				relativeX -= leftShift;
				nodeRail.get(nodeIndex).setX(relativeX);
			}

			// Try to extend next level
			ArrayList<IntervalNode> nextNodeRail = new ArrayList<IntervalNode>();
			for (int nodeIndex = 0; nodeIndex < nodeRail.size(); nodeIndex++) {
				IntervalNode currentNode = nodeRail.get(nodeIndex);
				if (currentNode.getChildNumber() > 0) {
					for (int i = 0; i < currentNode.getChildNumber(); i++) {
						nextNodeRail.add((IntervalNode)currentNode.get(i));
					}
					hasChild = true;
				}
			}
			
			relativeY += 160;
			nodeRail = nextNodeRail;
		}
		
		// Draw nodes
		recursiveDrawer(g, rootNode, x, y);
	}
	
	// Draw tree recursively
	private void recursiveDrawer(Graphics g, IntervalNode node, int x, int y) {
		// Draw line to child
		g.setColor(new Color(200, 100, 100));
		for (int i = 0; i < node.getChildNumber(); i++) {
			IntervalNode childNode = (IntervalNode)node.get(i);
			int x1 = x + node.getX() + node.getWidth() / 2;
			int y1 = y + node.getY() + 50;
			int x2 = x + childNode.getX() + childNode.getWidth() / 2;
			int y2 = y + childNode.getY() + 50;
			g.drawLine(x1, y1, x2, y2);
			g.drawString("" + childNode.getDerivationCode(), (x1 + x2) / 2 - 10, (y1 + y2) / 2 - 5);
		}
		
		// Draw current node
		node.draw(g, x + node.getX(), y + node.getY());

		// Draw child nodes
		for (int i = 0; i < node.getChildNumber(); i++) {
			recursiveDrawer(g, (IntervalNode)node.get(i), x, y);
		}
	}
}
