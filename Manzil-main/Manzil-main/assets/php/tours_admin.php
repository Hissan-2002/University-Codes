<?php
session_start();

if (!isset($_SESSION['authenticated']) || $_SESSION['authenticated'] !== true) {
    header('Location: ../../login.html');
    exit;
}
?>


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Admin Panel - Tours</title>
    <style>
        body {
            font-family: 'Arial', sans-serif;
            background-color: hsl(210, 11%, 15%);
            margin: 20px;
            padding: 20px;
            color: white;
            position: relative;
        }

        #back-arrow {
            position: fixed;
            top: 10px;
            left: 10px;
            font-size: 20px;
            color: hsl(0, 0%, 69%);
            text-decoration: none;
        }

        h1 {
            text-align: center;
            margin: 0;
        }

        h2 {
            color: white;
        }

        form {
            background-color: hsl(0, 0%, 69%);
            padding: 20px;
            margin-bottom: 20px;
            border-radius: 8px;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
        }

        label {
            display: block;
            margin-bottom: 8px;
            color: #555;
        }

        select,
        input[type="submit"] {
            width: 100%;
            padding: 10px;
            margin-bottom: 15px;
            border: 1px solid #ccc;
            border-radius: 4px;
            box-sizing: border-box;
        }

        input[type="submit"] {
            background: hsl(180, 98%, 31%);
            color: white;
        }

        input[type="submit"]:hover {
            background: hsl(180, 98%, 37%);
        }

        input[type="number"] {
            width: 50px;
        }

        input {
            margin-bottom: 5px;
        }

        ul {
            list-style: none;
            padding: 0;
        }

        li {
            background-color: #fff;
            padding: 10px;
            margin-bottom: 10px;
            border-radius: 4px;
            box-shadow: 0 0 5px rgba(0, 0, 0, 0.1);
        }
    </style>
</head>
<body>
    <a id="back-arrow" href="../../adminpanel.php">← Back</a>
    <h1>Tours</h1> 
<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "manzil";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Handle Add Product Form Submission
if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_POST['add_product'])) {
    // Get data from the form
    $name = $_POST['name'];
    $days = $_POST['days'];
    $price = $_POST['price'];
    $rating = $_POST['rating'];
    $info = $_POST['info'];
    $link = $_POST['link'];
    $imageURL = $_POST['imageURL'];

    // Insert data into the database
    $sql = "INSERT INTO tours (name, days, price, rating, info, link, imageURL) VALUES ('$name', '$days', '$price', '$rating', '$info', '$link', '$imageURL')";

    if ($conn->query($sql) === TRUE) {
        echo "Product added successfully";
    } else {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }
}

// Handle Delete Product Form Submission
if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_POST['delete_product'])) {
    // Check if the selected_product is set in the form
    if (isset($_POST['selected_product'])) {
        // Get selected product ID from the form
        $selected_product = $_POST['selected_product'];

        // Delete product from the database
        $sql = "DELETE FROM tours WHERE id = '$selected_product'";

        if ($conn->query($sql) === TRUE) {
            echo "Product deleted successfully";
        } else {
            echo "Error: " . $sql . "<br>" . $conn->error;
        }
    } else {
        echo "Please select a product to delete.";
    }
}

// Display existing products for deletion
$result = $conn->query("SELECT * FROM tours");

if ($result->num_rows > 0) {
    echo "<h2>Delete Existing Products</h2>";
    echo "<form action='' method='post'>";
    echo "<label for='selected_product'>Select Product to Delete:</label>";
    echo "<select name='selected_product'>";
    while ($row = $result->fetch_assoc()) {
        echo "<option value='{$row['id']}'>{$row['name']}</option>";
    }
    echo "</select><br>";
    echo "<input type='submit' name='delete_product' value='Delete Product'>";
    echo "</form>";
} else {
    echo "<p>No products found</p>";
}

// Close connection
$conn->close();
?>

<h2>Add Product</h2>
<form action="" method="post">
    <label for="name">Name:</label>
    <input type="text" name="name" required><br>

    <label for="days">Days:</label>
    <input type="number" name="days" required><br>

    <label for="price">Price:</label>
    <input type="number" name="price" required><br>

    <label for="rating">Rating:</label>
    <input type="number" name="rating" min="1" max="5" required><br>

    <label for="info">Info:</label>
    <input type="text" name="info"><br>

    <label for="link">Link:</label>
    <input type="text" name="link" required><br>

    <label for="imageURL">Image URL:</label>
    <input type="text" name="imageURL"><br>

    <input type="submit" name="add_product" value="Add Product">
</form>

</body>
</html>
