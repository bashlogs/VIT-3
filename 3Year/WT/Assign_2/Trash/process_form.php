<?php
// Connect to your database (modify the credentials accordingly)
$db = new mysqli('localhost', 'root', '', 'test');

if ($db->connect_error) {
    die("Connection failed: " . $db->connect_error);
}

// Process the form submission
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $name = $_POST['name'];
    $college = $_POST['college'];
    $prn = $_POST['prn'];
    $roll = $_POST['roll'];
    $year = $_POST['year'];
    $div = $_POST['div'];
    $age = $_POST['age'];
    $gender = $_POST['gender'];
    $phone = $_POST['phone'];

    // Insert data into the database
    $sql = "INSERT INTO students (name, college, prn, roll, year, division, age, gender, phone)
            VALUES ('$name', '$college', '$prn', '$roll', $year, '$div', '$age', '$gender', '$phone')";

    if ($db->query($sql) === TRUE) {
        echo "Record added successfully.";
    } else {
        echo "Error: " . $sql . "<br>" . $db->error;
    }
}

$db->close();
?>
