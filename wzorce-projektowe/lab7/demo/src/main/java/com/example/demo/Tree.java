package com.example.demo;

import java.util.ArrayList;

interface ITree {
    public String getName();
    public Integer getAge();
    public ArrayList<String> getPhotos();
    public ArrayList<Double> getPosition();
}

public class Tree implements ITree {
    public String name;
    public Integer age;
    public ArrayList<String> photos;
    public ArrayList<Double> position;

    public Tree(String name, Integer age, ArrayList<String> photos, ArrayList<Double> position) {
	this.name = name;
	this.age = age;
	this.photos = photos;
	this.position = position;
    }

    public String getName() {
	return name;
    }

    public Integer getAge() {
	return age;
    }

    public ArrayList<String> getPhotos() {
	return photos;
    }

    public ArrayList<Double> getPosition() {
	return position;
    }
}

