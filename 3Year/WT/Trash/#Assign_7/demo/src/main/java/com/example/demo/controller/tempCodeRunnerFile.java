package com.yourpackage.controller;

import com.yourpackage.model.Result;
import com.yourpackage.repository.ResultRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

@RestController
public class ResultController {
    @Autowired
    private ResultRepository resultRepository;

    @PostMapping("/insert-result")
    public Result insertResult(@RequestBody Result result) {
        return resultRepository.save(result);
    }

    @GetMapping("/get-result")
    public Result getResult(@RequestParam String rollNumber) {
        Result result = resultRepository.findByRollNumber(rollNumber);
        // Calculate total marks for each subject and set in the result object
        // result.setSubject1Total(...);
        return result;
    }
}
