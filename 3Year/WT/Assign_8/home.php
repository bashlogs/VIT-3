<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Catalogue Page</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f3f3f3;
            margin: 0;
            padding: 0;
        }

        .container {
            max-width: 800px;
            margin: 0 auto;
            padding: 20px;
            background-color: #fff;
            border: 1px solid #ddd;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
        }

        h1 {
            color: #0077B6;
        }

        .book-list {
            list-style: none;
            padding: 0;
        }

        .book-item {
            border: 1px solid #ddd;
            margin: 10px 0;
            padding: 10px;
            background-color: #fff;
        }

        .book-title {
            font-weight: bold;
        }

        .book-author {
            color: #555;
        }

        .book-release {
            color: #777;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>Catalogue Page</h1>
        <ul class="book-list">
            <?php
                $servername = "localhost";
                $username = "root";
                $password = "";
                $database = "test";
                $conn = new mysqli($servername, $username, $password);

                if ($conn->connect_error) {
                    die("Connection failed: " . $conn->connect_error);
                }

                $sql = "SELECT * FROM test.books";
                $result = $conn->query($sql);
                $i = 1;
                while($row = $result->fetch_assoc()) {
                    // Create links with book information in the URL
                    $bookLink = "registration.php?name=" . $row["B_Name"] . "&author=" . $row["B_Author"];
                    
                    echo "<li class='book-item'>";
                    echo "<p class='book-title'>" . $i . ") <a href='" . $bookLink . "'>" . $row["B_Name"] . "</a></p>";
                    echo "<p class='book-author'>by " . $row["B_Author"] . "</p>";
                    echo "<p class='book-release'>Released in " . $row["B_RDate"] . "</p>";
                    echo "</li>";
                    $i++;
                }
                $conn->close();
            ?>
        </ul>
    </div>
</body>
</html>
