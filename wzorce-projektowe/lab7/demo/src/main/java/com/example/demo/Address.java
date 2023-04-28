package com.example.demo;

interface IAddress {
    public String getName();
    public String getCity();
}

public class Address implements IAddress {
    public String name;
    public String city;

    public Address(String name, String city) {
	this.name = name;
	this.city = city;
    }

    public String getName() {
	return name;
    }

    public String getCity() {
	return city;
    }
}

