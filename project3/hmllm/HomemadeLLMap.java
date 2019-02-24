package hmllm;

import java.util.Iterator;

/**
 * HomemadeLLMap
 * 
 * An implementation of the HomemadeMap class that uses
 * a completely-homemade linked list on the inside.
 * 
 * @author Thomas VanDrunen
 * CSCI 245, Wheaton College
 * June 30, 2014
 */

public class HomemadeLLMap implements HomemadeMap {

	public Node first;
	public Node tmp;
	public int listLen = 0;
    /**
     * Test whether an association exists for this key.
     * @param key The key to remove
     * @return true if there is an association for this key, false otherwise
     */
    public boolean containsKey(String key) {
    	return (getNode(key) != null);
    }
    
    /**
     * Find the node associated with this key
     * @param key The key to the desired node
     * @return Node if there is a node for this key, null otherwise
     */
    public Node getNode(String key) {
    	tmp = first;
    	int i;
    	for (i=0;i<listLen;i++) {
    		if (tmp.key == key) {
    			return tmp;
    		}
    		tmp = tmp.getNext();
    	}
    	return null;
    }
   

    /**
     * Add an association to the map.
     * @param key The key to this association
     * @param val The value to which this key is associated
     */
    public void put(String key, String val) {
    	if (key == null) {
    		return;
    	}
    	if (first == null) {
    		first = new Node(key, val);
    		listLen++;
    		return;
    	} else {
    		tmp = getNode(key);
    		if (tmp == null) {
    			tmp = new Node(key, val);
    			first.last().setNext(tmp);
    			tmp.setPrev(first.last().getPrev());
    		} else {
    			tmp.setVal(val);
    		}
    	}
    	listLen++;
    }  

    /**
     * Get the value for a key.
     * @param key The key whose value we're retrieving.
     * @return The value associated with this key, null if none exists
     */
    public String get(String key) {
//    	tmp = getNode(key);
//    	if (tmp == null) {
//    		return null;
//    	} else {
//    		return tmp.getVal();
//    	}
    	if (containsKey(key)) {
    		return getNode(key).getVal();
    	}
    	return null;
    }

    /**
     * Get an iterator for all the keys in this map.
     * @return An iterator over the set of keys.
     */
    public Iterator<String> keyIterator() {
    	return null;
    }

    
    /**
     * Remove the association for this key.
     * @param key The key to remove
     */   
    public void remove(String key) {
    }


	
}
