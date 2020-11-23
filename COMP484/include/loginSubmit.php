<?php
if (isset($_POST['login'])){
	require "lab2.php";
	$username = $_POST['usernameText'];
	$password = $_POST['passwordText'];
if(empty($username) || empty($password)){
	//header("Location: ../index.php?error=emptyfields");
	exit('Empty Fields');
}else{
	$sql = "SELECT * FROM users WHERE username=?;";
	$stmt = mysqli_stmt_init($conn);
	if(!mysqli_stmt_prepare($stmt,$sql)){
		//header("Location: ../index.php?error=sqlerror");
		exit('SQL Error');
	}
	mysqli_stmt_bind_param($stmt,"s",$username);
	mysqli_stmt_execute($stmt);
	$result = mysqli_stmt_get_result($stmt);
	if($row = mysqli_fetch_assoc($result)){
$passwordCheck = password_verify($password,$row[password]);
if($passwordCheck == false){
	//header("Location: ../index.php?error=wrongpassword");
	exit("Invalid Password");
}else if($passwordCheck == true){
session_start();
$_SESSION['IDuser']=$row['userid'];
$_SESSION['NAMEuser']=$row['username'];
//header("Location: ../index.php?login=success");
exit('Success');
}
else{
	//header("Location: ../index.php?error=wrongpassword");
	exit('Wrong Password');
}
	}else{
//header("Location: ../index.php?error=nouser");
	exit('Invalid Username');
	}
}
}else{
	//header("Location: ../index.php");
	exit('RIP');
}