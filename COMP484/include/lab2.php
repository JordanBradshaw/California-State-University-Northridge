<?php
$dbhost = "localhost";
$dbuser = "yupps";
$dbpass = "Kaplan484!";
$db = "484db";
$conn = mysqli_connect($dbhost, $dbuser, $dbpass, $db);
if (!$conn){
die("Connection failed: ".mysqli_connect_error());
}
