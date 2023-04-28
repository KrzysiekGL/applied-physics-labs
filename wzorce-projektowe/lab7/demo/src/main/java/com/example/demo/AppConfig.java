package com.example.demo;

import org.springframework.context.annotation.*;

@Configuration
public class AppConfig {
    @Bean
    public Address address() {
	return new Address("Jan", "Gdansk");
    }

    @Bean DebitCard debitCard() {
	return new DebitCard(address());
    }
}

