package com.example.demo;

import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.core.io.ClassPathResource;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

import java.io.IOException;
import java.io.InputStream;

@SpringBootApplication
@RestController
public class read_json {

    private static final ObjectMapper objectMapper = new ObjectMapper();
    private static JsonNode jsonData;

    static {
        try {
            InputStream inputStream = new ClassPathResource("data.json").getInputStream();
            jsonData = objectMapper.readTree(inputStream);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @RequestMapping(value = "/{id}", method = RequestMethod.GET)
    public String hello(@PathVariable int id) {
        String name = jsonData.get(String.valueOf(id)).asText();
        return "Hello, " + name + "!";
    }

    public static void main(String[] args) {
        SpringApplication.run(read_json.class, args);
    }
}