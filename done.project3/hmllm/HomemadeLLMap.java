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

	/* Node to represent beginning of list */
	public Node first;
	/* Node to hold temporary node for methods */
	public Node tmp;
	/* Node to represent end of list */
	public Node last;
	/* int holds length of list */
	public int len = 0;
	
	public int testi = 0;
	
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
    	for (i=0;i<len;i++) {
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
    	tmp = getNode(key);
    	if (tmp == null) {
    		if (first == null) {
    			first = new Node(key, val);
    		} else if (last == null) {
    			last = new Node(key, val);
    			first.setNext(last);
    			last.setPrev(first);
    		} else {
    			tmp = new Node(key, val);
    			last.setNext(tmp);
    			tmp.setPrev(last);
    			last = tmp;
    		}
    		len++;
    	} else {
    		tmp.setVal(val);
    	}
    	return;
    }  

    /**
     * Get the value for a key.
     * @param key The key whose value we're retrieving.
     * @return The value associated with this key, null if none exists
     */
    public String get(String key) {
    	tmp = getNode(key);
    	if (tmp != null) { 
    		return tmp.getVal();
    	}
    	return null;
    }

    /**
     * Get an iterator for all the keys in this map.
     * @return An iterator over the set of keys.
     */
    public Iterator<String> keyIterator() {
    	return new MapIter(first);
    }

    /**
     * Remove the association for this key.
     * @param key The key to remove
     */   
    public void remove(String key) {
    	tmp = getNode(key);
    	if (tmp == null) {
    		return;
    	} else {
    		if (first.getKey() == key) {
    			first = first.getNext();
    			if (first == null) {
    				len--;
    				return;
    			}
    			first.setPrev(null);
    		} else if (last.getKey() == key) {
    			last = last.getPrev();
    			last.setNext(null);
    			if (last.getKey() == first.getKey()) {
    				last = null;
    			}
    		} else {
    			Node tmp1 = tmp.getNext();
    			Node tmp2 = tmp.getPrev();
    			tmp1.setPrev(tmp2);
    			tmp2.setNext(tmp1);
    		}
    	len--;
    	}
    }


	
}
