<?php

if ($_POST) {

    // Get roll number
    $rollNo = $_POST['rollNo'];

    // Connect to the database
    $conn = mysqli_connect("localhost", "root", "", "vit_result");

    // Get student details
    $sql = "SELECT * FROM students1 WHERE prn='$rollNo'";
    $result = mysqli_query($conn, $sql);
    
    // Check if a student was found
    if ($result && mysqli_num_rows($result) > 0) {
        $student = mysqli_fetch_assoc($result);

        // Get result details
        $sql = "SELECT * FROM results WHERE student_id = {$student['id']}";
        $result = mysqli_query($conn, $sql);
    } else {
        // Student not found, handle the case here (e.g., display an error message)
        $student = null;
    }

}

?>

<!DOCTYPE html>
<html>

<head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Student Result</title>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css">
</head>

<body>

    <div class="container mt-5">

        <form method="post">
            <div class="form-group">
                <label>Enter PRN Number</label>
                <input type="text" name="rollNo" class="form-control">
            </div>
            <button type="submit" class="btn btn-primary">Get Result</button>
        </form>

        <?php if (isset($student)) { ?>
            <br>
            <h2>
                Name: <?php echo $student['name']; ?>
            </h2>
            <h5>
                <strong>Year: </strong><?php echo $student['year']; ?>rd
                <br>
                <strong>Division: </strong><?php echo $student['division']; ?> Division
                <br>
                <strong>Roll No: </strong><?php echo $student['roll']; ?>
                <br>
                <strong>PRN No: </strong><?php echo $student['prn']; ?>
            </h5>

            <table class="table table-bordered">
                <thead>
                    <tr>
                        <th>Subject</th>
                        <th>MSE Marks</th>
                        <th>ESE Marks</th>
                        <th>Total Marks</th>
                        <th>Grade</th>
                    </tr>
                </thead>
                <tbody>
                    <?php while ($row = mysqli_fetch_assoc($result)) { ?>
                        <tr>
                            <td>
                                <?php echo $row['subject']; ?>
                            </td>
                            <td>
                                <?php echo $row['mse_marks']; ?>
                            </td>
                            <td>
                                <?php echo $row['ese_marks']; ?>
                            </td>
                            <td>
                                <?php echo $row['total_marks']; ?>
                            </td>
                            <td>
                                <?php echo $row['grade']; ?>
                            </td>
                        </tr>
                    <?php } ?>
                </tbody>
            </table>

        <?php } else { ?>
            <p>Student not found. Please enter a valid PRN Number.</p>
        <?php } ?>

    </div>

</body>

</html>
