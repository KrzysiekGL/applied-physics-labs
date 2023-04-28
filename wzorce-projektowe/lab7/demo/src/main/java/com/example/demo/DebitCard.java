package com.example.demo;

import org.springframework.beans.factory.annotation.Autowired;

public class DebitCard {
    public IAddress address;

    @Autowired
    public DebitCard(IAddress address) {
	System.out.println("DebitCard::constructor");
	this.address = address;
    }

    public IAddress getAddress() {
	return address;
    }

    public void setAddress(IAddress address) {
	System.out.println("DebitCard::setAddress");
	this.address = address;
    }

    public String info() {
	return (String)("DC name: "+address.getName()+" DC city: "+address.getCity());
    }
}

