<?php

error_reporting(E_ALL);
ini_set('display_errors', 1);
session_start();

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $servername = "localhost";
    $username = "root";
    $password = "";
    $database = "manzil";

    // Create connection
    $conn = new mysqli($servername, $username, $password, $database);

    // Check connection
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }

    // Get username and password from the form
    $input_username = $_POST["username"];
    $input_password = $_POST["password"];

    // Perform SQL query to check credentials
    $sql = "SELECT * FROM users WHERE username = '$input_username'";
    $result = $conn->query($sql);

    if ($result->num_rows > 0) {
        
        $row = $result->fetch_assoc();
        // Check if the entered password matches the stored hash
        if (password_verify($input_password, $row["password"])) {
            
            // Authentication successful
            $_SESSION["authenticated"] = true;
            $_SESSION["username"] = $input_username;
            echo "Please select a product to delete.";
            header("Location: adminpanel.php");
            exit;
        }
    }

    header("Location: login.html");
    exit;
} else {
    
    header("Location: login.html");
    exit;
}
?>
