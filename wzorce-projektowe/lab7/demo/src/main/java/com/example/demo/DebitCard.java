package com.example.demo;

public class DebitCard {
    public Address address;

    public DebitCard() {}

    public DebitCard(Address address) {
	System.out.println("Hitting Constructor");
	this.address = address;
    }

    public Address getAddress() {
	return address;
    }

    public void setAddress(Address address) {
	System.out.println("Hitting setter method");
	this.address = address;
    }

    public void details() {
	System.out.println("This is Debit Card and address is: " + address.city);
    }
}

