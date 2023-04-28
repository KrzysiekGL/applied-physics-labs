package com.example.demo;

import org.springframework.context.annotation.*;

@Configuration
public class AddressConfig {
    @Bean
    public Address address() {
	return new Address("Jan", "Gdansk");
    }
}

