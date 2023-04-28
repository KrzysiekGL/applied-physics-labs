package com.example.demo;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

import org.springframework.context.ApplicationContext;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;

@SpringBootApplication
public class DemoApplication {
    public static void main(String[] args) {
	//SpringApplication.run(DemoApplication.class, args);

	ApplicationContext ctx = new AnnotationConfigApplicationContext(AppConfig.class);

	//DebitCard dc = new DebitCard(ctx.getBean(Address.class));
	DebitCard dc = new DebitCard(ctx.getBean("addressSpec", Address.class));
	System.out.println("Debit card info: "+dc.info());
    }
}

