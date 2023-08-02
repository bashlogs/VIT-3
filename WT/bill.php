<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Bill Calculator</title>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css">
</head>
<body>
    <div class="container mt-3">
       <h2 class="text-center">Electricity Bills</h2>
        <form id="electricityForm" method="post" class="mt-3">
            <div class="form-group">  
                <label>Enter Name: </label>
                <input type="text" class="form-control" id="name" placeholder="Enter Name" name="name" required>
                <br>
                <label>Enter Unit: </label>
                <input type="number" class="form-control" id="units" placeholder="Enter Units" name="units" required>
            </div>
            <center><input type="submit" class="btn btn-secondary" value="calculate"></center>
        </form>
        <div id="result" class="mt-4 d-none">
            <?php
              $name = $_POST["name"];
              echo "Name: ".$name."<br>";
              $input = $_POST["units"];
              echo "Total Bill Amount: ".$input*3.5;
            ?> 
            <h3 class="text-center">Electricity Bill</h3>
            <p class="text-center" id="billAmount"></p>
        </div>
        <div id="result" class="mt-4">
            <?php
            if ($_SERVER["REQUEST_METHOD"] == "POST") {
                $name = $_POST["name"];
                $units = $_POST["units"];
                $totalBillAmount = $units * 3.5;
            ?>
            <h3 class="text-center">Bill</h3>
            <p class="text-center">
                Name: <?php echo $name; ?><br>
                Total Bill Amount: <?php echo $totalBillAmount." Rs."; ?>
            </p>
            <?php } ?>
        </div>
    </div>
     
    </body>
</html>

