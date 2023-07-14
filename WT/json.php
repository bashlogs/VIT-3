<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>
    <table>
        <thead>
            <tr>
                <th>Roll No</th>
                <th>Name</th>
            </tr>
        </thead>
        <tbody>
            <?php
                $jsonobj = '{ "employees" : [{ "RollNo":"1" , "Name":"Doe" },{ "RollNo":"2" , "Name":"Jone" },{ "RollNo":"3" , "Name":"vit" }]}';
                
                $obj = json_decode($jsonobj);

                foreach ($obj->employees as $employee) {
                    echo "<tr>";
                    echo "<td>" . $employee->RollNo . "</td>";
                    echo "<td>" . $employee->Name . "</td>";
                    echo "</tr>";
                }
            ?>
        </tbody>
    </table>
</body>
</html>
