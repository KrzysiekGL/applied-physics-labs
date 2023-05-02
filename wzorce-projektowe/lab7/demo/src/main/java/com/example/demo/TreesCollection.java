package com.example.demo;

import java.util.ArrayList;
import org.springframework.beans.factory.annotation.Autowired;

public class TreesCollection {
    @Autowired
    public ArrayList<ITree> trees;

    public TreesCollection(ArrayList<ITree> trees) {
	this.trees = trees;
    }

    public ArrayList<ITree> getTrees() {
	return trees;
    }

    public void addTree(ITree tree) {
	trees.add(tree);
    }

    public String info() {
	String message;
	message = "Trees collection:\n";
	if(0!=trees.size()) {
	    for(ITree t : trees) {
		message += "Name: " + t.getName();
		message += " Age: " + String.valueOf(t.getAge());
		message += " GPS Position: " + String.valueOf(t.getPosition());
		for(String s : t.getPhotos()) {
		    message += "\n" + s;
		}
		message += "\n";
	    }
	}
	return message;
    }
}

