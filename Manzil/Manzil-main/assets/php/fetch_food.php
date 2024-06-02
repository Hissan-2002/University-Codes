<?php
// Replace these database connection details with your actual credentials
error_reporting(E_ALL);
ini_set('display_errors', 1);


$host = 'localhost';
$user = 'root';
$password = '';
$database = 'manzil';

// Create a connection
$connection = new mysqli($host, $user, $password, $database);

// Check the connection
if ($connection->connect_error) {
    die("Connection failed: " . $connection->connect_error);
}

// Fetch hotel data from the database
$query = "SELECT * FROM food";
$result = $connection->query($query);

// Close the database connection
$connection->close();

// Convert the result to an associative array
$foodData = [];
while ($row = $result->fetch_assoc()) {
    $foodData[] = $row;
}

// Return data as JSON
header('Content-Type: application/json');
echo json_encode($foodData);
?>
