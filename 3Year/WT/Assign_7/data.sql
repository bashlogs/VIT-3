-- Create database
CREATE DATABASE vit_result;

use vit_result;

-- Create students table
CREATE TABLE students (
  id INT AUTO_INCREMENT PRIMARY KEY,
  name VARCHAR(100),
  roll_no VARCHAR(10)
);

-- Create results table 
CREATE TABLE results (
  id INT AUTO_INCREMENT PRIMARY KEY,
  student_id INT,
  subject VARCHAR(50),
  mse_marks INT,
  ese_marks INT,
  total_marks INT,
  grade CHAR(2),
  FOREIGN KEY (student_id) REFERENCES students(id)
);

-- Insert sample student
INSERT INTO students (name, roll_no) VALUES 
('Omkar Kanase', '12220053');

-- Insert sample results 
INSERT INTO results (student_id, subject, mse_marks, ese_marks, total_marks, grade) VALUES
(1, 'SDAM', 29, 60, 89, 'A'),  
(1, 'WT', 28, 60, 88, 'A'),
(1, 'CN', 29, 60, 89, 'A'),
(1, 'DAA', 28, 60, 88, 'A'),
(1, 'DT', 29, 60, 89, 'A'),
(1, 'EDI', 30, 59, 89, 'A');