package com.book.store.model;

import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import jakarta.persistence.Table;

//import org.springframework.context.annotation.EnableAspectJAutoProxy;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

@Setter
@Getter
@AllArgsConstructor
@NoArgsConstructor
@Entity
@Table(name = "book")
public class Book {
	

 


public Book(int i, String string, String string2, int j) {
	// TODO Auto-generated constructor stub
}
@Id
 @GeneratedValue(strategy = GenerationType.AUTO)
 private long id;
 @Column
 private String bookName;
 @Column
 private String authorName;
 @Column
 private long price;
}