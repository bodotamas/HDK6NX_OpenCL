package base;

import java.util.ArrayList;

/**
 * General node class for build trees
 * 
 * @author Piller Imre
 */
public class Node {

	private ArrayList<Node> childNodes;

	public Node() {
		// Create empty childnode list
		childNodes = new ArrayList<Node>();
	}
	
	// Get number of child nodes
	public int getChildNumber() {
		return childNodes.size();
	}
	
	// Get child node
	public Node get(int index) {
		// Check index
		if (index < 0 || index > childNodes.size() - 1) {
			System.err.println("ERROR: Node::getChild - Invalid index !");
			return null;
		}

		return childNodes.get(index);
	}
	
	// Add new child to node
	public void add(Node node) {
		if (node != null) {
			childNodes.add(node);
		}
	}

	// Remove node by node reference
	public void remove(Node node) {
		if (node != null) {
			childNodes.remove(node);
		}
	}

	// Remove node by node index
	public void remove(int index) {
		// Check index
		if (index < 0 || index > childNodes.size() - 1) {
			System.err.println("ERROR: Node::remove - Invalid index !");
			return;
		}

		childNodes.remove(index);
	}

	// Remove all child
	public void removeAllChild() {
		childNodes.clear();
	}
}
