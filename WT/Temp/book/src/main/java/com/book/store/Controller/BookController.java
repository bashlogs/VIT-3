package com.book.store.Controller;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

import com.book.store.model.Book;
import com.book.store.repository.BookRepository;
@CrossOrigin(origins = "http://localhost:3001/")
@RestController
public class BookController {

 @Autowired
 private BookRepository bookRepository;
 @GetMapping("/books")
 public List<Book> getAllBooks() {
  return bookRepository.findAll();
 }
}