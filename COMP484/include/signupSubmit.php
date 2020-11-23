<?php
if (isset($_POST['newName'])) {
	require "lab2.php";
	$username = $_POST['usernameString'];
	$password = $_POST['passwordString'];
	if (empty($username) || empty($password)) {
		//header("Location: ../newUser.php?error=emptyfields&usernameField=" . $username);
		exit("Empty Field");
	} else if (!preg_match("/^[a-zA-Z0-9]*$/", $username)) {
		//header("Location: ../newUser.php?error=invalidusername");
		exit("Invalid Username");
	} else {
		$sql = "SELECT username FROM users WHERE username=?";
		$stmt = mysqli_stmt_init($conn);
		if (!mysqli_stmt_prepare($stmt, $sql)) {
			//header("Location: ../newUser.php?error=sqlerror1");
			exit("SQLError");
		} else {
			mysqli_stmt_bind_param($stmt, "s", $username);
			mysqli_stmt_execute($stmt);
			mysqli_stmt_store_result($stmt);
			$resultCheck = mysqli_stmt_num_rows($stmt);
			if ($resultCheck > 0) {
				//header("Location: ../newUser.php?error=usernametaken");
				exit("Username Taken");
			} else {
				$sql = "INSERT INTO users (username,password) VALUES (?,?)";
				$stmt = mysqli_stmt_init($conn);
//var_dump($stmt);
				if (!mysqli_stmt_prepare($stmt, $sql)) {
					//header("Location: ../newUser.php?error=sqlerror2");
					exit("SQL Error");
				} else {
					$hashPassword = password_hash($password, PASSWORD_DEFAULT);
					mysqli_stmt_bind_param($stmt, "ss", $username, $hashPassword);
					//mysqli_stmt_execute($stmt);
					//var_dump($stmt);
					if($stmt->execute()){
						exit("Username Created");
					}else{
						echo "Error: " . mysqli_error($conn);
						exit("Username Creation Failed");
					}
					//header("Location: ../index.php");
					exit("Username Created");
				}
			}
		}
	}
	mysqli_stmt_close($stmt);
	mysqli_close($conn);
} else {
	//header("Location: ../newUser.php");
	exit("Party Foul");
}