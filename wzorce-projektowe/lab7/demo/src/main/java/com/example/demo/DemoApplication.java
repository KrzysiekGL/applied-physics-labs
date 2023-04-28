package com.example.demo;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

import org.springframework.context.ApplicationContext;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;

@SpringBootApplication
public class DemoApplication {
    public static void main(String[] args) {
	//SpringApplication.run(DemoApplication.class, args);

	//String xmlFile = "src/main/resources/application_context_debit.xml";
	//String xmlFile = "application_context_debit.xml";
	//ApplicationContext ctn = new ClassPathXmlApplicationContext(xmlFile);

	//DebitCard dcard = (DebitCard)ctn.getBean("dcard");
	//dcard.details();

	ApplicationContext ctx = new AnnotationConfigApplicationContext(AppConfig.class);

	DebitCard dc = ctx.getBean(DebitCard.class);
	System.out.println("Debit card info: "+dc.info());
    }
}

