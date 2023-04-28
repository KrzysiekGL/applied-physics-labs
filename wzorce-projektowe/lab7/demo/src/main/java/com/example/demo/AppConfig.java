package com.example.demo;

import org.springframework.context.annotation.*;

@Configuration
public class AppConfig {
    @Bean
    public Address address() {
	return new Address("Jan", "Gdansk");
    }

    @Bean
    public Address addressSpec() {
	return new Address("Niemoc", "Mniedopada");
    }
}

