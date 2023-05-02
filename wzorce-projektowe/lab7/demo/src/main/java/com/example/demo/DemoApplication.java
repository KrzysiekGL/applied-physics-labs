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

	TreesCollection tc = ctx.getBean(TreesCollection.class);
	tc.addTree(ctx.getBean("treeOak", Tree.class));
	tc.addTree(ctx.getBean("treePine", Tree.class));
	System.out.println(tc.info());
    }
}

