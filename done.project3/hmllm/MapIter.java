package hmllm;

import java.util.Iterator;


/**
 * MapIter
 * 
 * An implementation of the Iterator interface.
 * 
 * @author John Drury
 * CSCI 245, Wheaton College
 * February 23, 2019
 */
public class MapIter implements Iterator<String> {

	/* Node that holds current node */
	public Node node;
	/* String that holds current key */
	public String key;
	
	/* Constructor */
	public MapIter(Node n) {
		node = n;
	}
	
	/**
	 * checks whether or not the iterable
	 * has more values to iterate through
	 * @return true if there is another node in the list, false if not 
	 */
	@Override
	public boolean hasNext() {
		if (node == null) {
			return false;	
		}
		//return node.getNext() != null;
		return true;
	}
	
	/**
	 * checks for the next value in the iterable
	 * @return key if there is another node in the list, null if not 
	 */
	@Override
	public String next() {
		key = node.getKey();
		if (hasNext()) {
			node = node.getNext();
		}
		return key;
		
	}
	
	/**
	 * if user tries to remove value
	 * throws an exception 
	 */
	@Override
	public void remove() {
		throw new UnsupportedOperationException();
	}

}
