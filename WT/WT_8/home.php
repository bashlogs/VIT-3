<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Home Page</title>
</head>
<body>
    <?php session_start(); ?>
    <?php
    if(isset($_SESSION['username']))
    {
        echo "Welcome ".$_SESSION['username'];
    }
    else
    {
        echo "You are not logged in";
    }

    $servername = "localhost";
    $username = "root";
    $password = "";
    $database = "test";
    $conn = new mysqli($servername, $username, $password);

    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }
    echo "<br>Database Connected successfully";

    ?>

    <h3>Menu: </h3>
    <label for="catalogues">Catalogue Page: </label>
    <br>
    <?php

        $sql = "SELECT * FROM test.books";
        $result = $conn->query($sql);
        $i = 1;
        while($row = $result->fetch_assoc()) {
            echo "<br>" . $i . ") \"" . "<a href=\"registration.html\">" .$row["B_Name"]."</a>" . "\" by " . $row["B_Author"] . " - Released in " . $row["B_RDate"] . "<br>";
            $i++;
        }

    ?>
</body>
</html>