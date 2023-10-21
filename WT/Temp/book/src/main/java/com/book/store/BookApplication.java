package com.book.store;


import com.book.store.model.Book;

import org.springframework.beans.factory.annotation.Autowired;
//import com.book.storegframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

//import com.book.store.model.Book;
import com.book.store.repository.BookRepository;

@SpringBootApplication
public class BookApplication implements CommandLineRunner {

 public static void main(String[] args) {
  SpringApplication.run(BookApplication.class, args);
 }

 @Autowired
 private BookRepository bookRepository;
 @Override
 public void run(String... args) throws Exception {
  Book book = new Book(0, null, null, 0);
  bookRepository.save(new Book(1, "Wings of Fire","A P J Abdul Kalam, Arun Tiwari", 500));
  bookRepository.save(new Book(2, "The Alchemist","Paulo Coelho", 144));
  bookRepository.save(new Book(3, "War and Peace","Leo Tolstoy", 299));
  bookRepository.save(new Book(3, "Song of Solomon","Tony Morrison", 555));
  
 }

}