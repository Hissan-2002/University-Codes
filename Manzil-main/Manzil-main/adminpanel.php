<?php
session_start();

if (!isset($_SESSION['authenticated']) || $_SESSION['authenticated'] !== true) {
    header('Location: login.html');
    exit;

}

$username = $_SESSION['username'];
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>MANZIL - Admin Panel</title>
    <link rel="stylesheet" href="https://fonts.googleapis.com/css2?family=Material+Symbols+Outlined:opsz,wght,FILL,GRAD@24,400,0,0" />
    <style>
        * {
            padding: 0;
            margin: 0;
            box-sizing: border-box;
            font-family: "Poppins", sans-serif;
        }

        body {
            background-color: hsl(210, 11%, 15%);
            display: flex;
            flex-direction: column;
            margin: 0.5em;
        }

        .options {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(400px, 1fr));
            justify-content: center;
            align-items: flex-start;
            gap: 1.5em; /* Adjust the gap value as needed */
            min-height: 50vh;
            user-select: none;
        }

        .card {
            border-radius: 10px;
            filter: drop-shadow(0 5px 10px 0 #ffffff);
            width: 100%;
            height: 180px;
            background-color: hsl(0, 0%, 69%);
            padding: 20px;
            position: relative;
            z-index: 0;
            overflow: hidden;
            transition: 0.6s ease-in;
            display: flex;
            align-items: center;
        }

        .card::before {
            content: "";
            position: absolute;
            z-index: -1;
            top: -15px;
            right: -15px;
            background: hsl(180, 98%, 31%);
            height: 220px;
            width: 25px;
            border-radius: 32px;
            transform: scale(1);
            transform-origin: 50% 50%;
            transition: transform 0.25s ease-out;
        }

        .card:hover::before {
            transition-delay: 0.2s;
            transform: scale(40);
        }

        .card:hover {
            color: #ffffff;
        }

        .card h4 {
            font-size: 3rem;
        }

        a {
            text-decoration: none;
            color: inherit;
        }

        .heading {
            color: white;
            display: flex;
            align-items: center;
            justify-content: space-between; /* Align the icon vertically with the text */
        }

        .acc {
            font-size: 3em;
            display: flex;
            align-items: center;
        }

        .out {
            font-size: 3em;
        }

        .account {
            font-family: 'Material Symbols Outlined';
            font-size: 2em; /* Adjust the size as needed */
            margin-right: 10px; /* Add some spacing between the icon and the text */
        }
    </style>
</head>
<body>
    <div class="heading">
        <div></div>
        <div class="acc">
            <span class="material-symbols-outlined account">
            account_circle
            </span>    
            <h3 class="name"><?php echo htmlspecialchars($username); ?></h3>
        </div>
        <a href="logout.php" class="logout">
            <span class="material-symbols-outlined out">
            logout
            </span>
        </a>
    </div>
    
    <div style="height: 30px;"></div>
    <div class="options">
        <a href="assets/php/landmarks_admin.php"><div class="card">
            <h4>Landmarks</h4>
        </div></a>
        <a href="assets/php/accomodation_admin.php"><div class="card">
            <h4>Accomodations</h4>
        </div></a>
        <a href="assets/php/food_admin.php"><div class="card">
            <h4>Food</h4>
        </div></a>
        <a href="assets/php/transport_admin.php"><div class="card">
            <h4>Transport</h4>
        </div></a>
        <a href="assets/php/activities_admin.php"><div class="card">
            <h4>Activities</h4>
        </div></a>
        <a href="assets/php/guides_admin.php"><div class="card">
            <h4>Guides</h4>
        </div></a>
        <a href="assets/php/tours_admin.php"><div class="card">
            <h4>Tours</h4>
        </div></a>
        <a href="assets/php/blog_admin.php"><div class="card">
            <h4>Blog</h4>
        </div></a>
        <a href="assets/php/accounts_admin.php"><div class="card">
            <h4>Accounts</h4>
        </div></a>
    </div>
</body>

</html>
