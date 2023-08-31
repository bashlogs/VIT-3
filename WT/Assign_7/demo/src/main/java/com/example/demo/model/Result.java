package com.example.demo.model;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;

@Entity
public class Result {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private String rollNumber;
    private float subject1MSE;
    private float subject1ESE;
    private float subject2MSE;
    private float subject2ESE;
    private float subject3MSE;
    private float subject3ESE;
    private float subject4MSE;
    private float subject4ESE;

    // Constructors, getters, and setters
}
