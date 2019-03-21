package hmllm;


/**
 * Node
 * 
 * A class that when instantiated gives you an
 * object to be used in keeping track of a 
 * linked list.
 * 
 * @author John Drury
 * CSCI 245, Wheaton College
 * February 23, 2019
 */
public class Node {
	
	public Node prev = null;
	public Node next = null;
	public String key;
	public String val;
	
	/* Constructor */
	public Node(String k, String v) {
		key = k;
		val = v;
	}
	
	/**
	 * sets the next node for a node
	 * @param Node to be set as next 
	 */
	public void setNext(Node n) {
		next = n;
	}
	
	/**
	 * sets the previous node for a node
	 * @param Node to be set as prev 
	 */
	public void setPrev(Node n) {
		prev = n;
	}

	/**
	 * gets the next node from a node
	 * @return Node that is after the current node 
	 */
	public Node getNext() {
		return next;
	}

	/**
	 * gets the previous node from a node
	 * @return Node that is previous to current node 
	 */
	public Node getPrev() {
		return prev;
	}

	/**
	 * gets value of node
	 * @return String which is the value of the current node 
	 */
	public String getVal() {
		return val;
	}

	/**
	 * sets value of node
	 * @param String which is the value
	 * to be set for the current node 
	 */
	public void setVal(String v) {
		val = v;
	}
	
	/**
	 * gets value of node
	 * @return String which is the key of this node
	 */
	public String getKey() {
		return key;
	}
	
}
