<?php
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    // Get form data
    $book = $_POST['book'];
    $author = $_POST['author'];
    $first_name = $_POST['first_name'];
    $last_name = $_POST['last_name'];
    $email = $_POST['email'];
    $password = $_POST['password'];
    $confirm_password = $_POST['confirm_password'];

    // Validate form data (you can add more validation as needed)
    if (empty($first_name) || empty($last_name) || empty($email) || empty($password) || empty($confirm_password)) {
        echo "Please fill in all fields.";
    } elseif ($password != $confirm_password) {
        echo "Passwords do not match.";
    } else {
        // Database connection
        $servername = "localhost";
        $username = "root";
        $password = "";
        $database = "test";

        $conn = new mysqli($servername, $username, $password, $database);

        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        }

        // Insert user data into the database
        $password = password_hash($password, PASSWORD_BCRYPT); // Securely hash the password

        $sql = "INSERT INTO users (book, author, first_name, last_name, email, password) 
                VALUES ('$book', '$author', '$first_name', '$last_name', '$email', '$password')";

        if ($conn->query($sql) === TRUE) {
            echo '<div style="color: green; text-align: center;">Registration successful for ' . '. Book: ' . $book . ', Author: ' . $author . '</div>';
        } else {
            echo '<div style="color: red; text-align: center;">Error: ' . $sql . '<br>' . $conn->error . '</div>';
        }

        $conn->close();
    }
}
?>


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Registration</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f3f3f3;
            margin: 0;
            padding: 0;
        }

        .container {
            max-width: 400px;
            margin: 0 auto;
            padding: 20px;
            background-color: #fff;
            border: 1px solid #ddd;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
        }

        h1 {
            color: #0077B6;
        }

        label {
            font-weight: bold;
            display: block;
            margin-bottom: 5px;
        }

        input[type="text"],
        input[type="email"],
        input[type="password"] {
            width: 95%;
            padding: 10px;
            margin-bottom: 10px;
            border: 1px solid #ddd;
            border-radius: 5px;
        }

        input[type="submit"] {
            background-color: #0077B6;
            color: #fff;
            border: none;
            padding: 10px 20px;
            border-radius: 5px;
            cursor: pointer;
        }

        input[type="submit"]:hover {
            background-color: #005A8C;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>Registration</h1>

        <form method="post">
            <label for="book">Book: </label>
            <input type="text" name="book" id="book" value="<?php echo $_GET['name']; ?>" readonly>

            <label for="author">Author: </label>
            <input type="text" name="author" id="author" value="<?php echo $_GET['author']; ?>" readonly>

            <label for="first_name">First Name: </label>
            <input type="text" id="first_name" name="first_name" required>

            <label for="last_name">Last Name: </label>
            <input type="text" id="last_name" name="last_name" required>

            <label for="email">Email: </label>
            <input type="email" id="email" name="email" required>

            <label for="password">Password: </label>
            <input type="password" name="password" required>

            <label for="confirm_password">Confirm Password: </label>
            <input type="password" name="confirm_password" required>

            <input type="submit" value="Register">
        </form>
    </div>
</body>
</html>
