<?php
require_once "dbconfig.php";

$rollNumber = $_POST["rollNumber"]; // Ensure you sanitize and validate user input

$query = "SELECT * FROM results WHERE roll_number = '$rollNumber'";
$result = $conn->query($query);

if ($result->num_rows > 0) {
    $row = $result->fetch_assoc();
    $subject1Total = $row["subject1_mse"] * 0.3 + $row["subject1_ese"] * 0.7;

    echo json_encode([
        "subject1" => $subject1Total,
    ]);
} else {
    echo "No results found for the provided roll number.";
}

$conn->close();
?>
