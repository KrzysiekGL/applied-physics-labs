package com.example.demo;

public class DebitCard {
    public Address address;

    public DebitCard() {}

    public DebitCard(Address address) {
	System.out.println("DebitCard::constructor");
	this.address = address;
    }

    public Address getAddress() {
	return address;
    }

    public void setAddress(Address address) {
	System.out.println("DebitCard::setAddress");
	this.address = address;
    }

    public String info() {
	return (String)("DC name: "+address.getName()+" DC city: "+address.getCity());
    }
}

