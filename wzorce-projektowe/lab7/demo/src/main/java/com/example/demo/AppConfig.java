package com.example.demo;

import java.util.ArrayList;
import org.springframework.context.annotation.*;

@Configuration
public class AppConfig {
    @Bean
    public ArrayList<ITree> arrayListTree() {
	return new ArrayList<ITree>();
    }

    @Bean
    public TreesCollection treesCollection() {
	return new TreesCollection(arrayListTree());
    }

    @Bean
    public Tree treeOak() {
	String name = "Oak";
	Integer age = 150;
	ArrayList<Double> position = new ArrayList<Double>(){
		{
		    add(55.001);
		    add(33.002);
		}
	    };
	ArrayList<String> photos = new ArrayList<String>(){
		{
		    add("TREE-OAK.png");
		    add("tree-oak.jpg");
		}
	    };
	return new Tree(name, age, photos, position);
    }

    @Bean
    public Tree treePine() {
	String name = "Pine";
	Integer age = 80;
	ArrayList<Double> position = new ArrayList<Double>(){
		{
		    add(45.991);
		    add(-29.092);
		}
	    };
	ArrayList<String> photos = new ArrayList<String>(){
		{
		    add("TREE-PINE.png");
		    add("tree-pine.jpg");
		}
	    };
	return new Tree(name, age, photos, position);
    }
}

