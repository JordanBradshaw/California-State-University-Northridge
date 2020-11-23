<?php
session_start();
$dbhost = "localhost";
$dbuser = "root";
$dbpass = "424Group";
$db = "COMP424";
$conn = mysqli_connect($dbhost, $dbuser, $dbpass, $db);
if (!$conn){
die("Connection failed: ".mysqli_connect_error());
}

