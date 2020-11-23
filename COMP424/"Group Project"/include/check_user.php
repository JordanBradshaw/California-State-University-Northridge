<?php
include "conn.php";
require_once 'GoogleAuthenticator.php';
$gauth = new GoogleAuthenticator();
$secret_key = $gauth->createSecret();
$process_name = $_POST['process_name'];
if ($process_name == "user_register") {
        $reg_name = $_POST['reg_name'];
        $reg_email = $_POST['reg_email'];
        $reg_password = $_POST['reg_password'];
        $sql = "SELECT * FROM tbl_users WHERE email=?";
        $stmt = mysqli_stmt_init($conn);
        if (!mysqli_stmt_prepare($stmt, $sql)) {
                echo "SQLError";
        } else {
                mysqli_stmt_bind_param($stmt, "s", $reg_email);
                mysqli_stmt_execute($stmt);
                mysqli_stmt_store_result($stmt);
                $resultCheck = mysqli_stmt_num_rows($stmt);
                if ($resultCheck > 0) {
                        exit("This email already exists in the system");
                } else {
                        $sql = 'INSERT INTO tbl_users (profile_name, email, password, google_auth_code, created_at) VALUES (?,?,?,?,?)';
                        $stmt = mysqli_stmt_init($conn);
                        if (!mysqli_stmt_prepare($stmt, $sql)) {
                                exit("SQL Error");
                        } else {
                                $hashPassword = password_hash($reg_password, PASSWORD_DEFAULT);
                                $current_date = date("Y-m-d");
                                mysqli_stmt_bind_param($stmt, "sssss", $reg_name, $reg_email, $hashPassword, $secret_key, $current_date);
                                if ($stmt->execute()) {
                                        $sql = "SELECT user_id FROM tbl_users WHERE email='$reg_email'";
                                        $stmt = mysqli_stmt_init($conn);
                                        if (!mysqli_stmt_prepare($stmt, $sql)) {
                                                exit('SQL Error');
                                        }
                                        mysqli_stmt_execute($stmt);
                                        $result = mysqli_stmt_get_result($stmt);
                                        if ($row = mysqli_fetch_assoc($result)) {
                                                $_SESSION['user_id'] = $row['user_id'];
                                                
                                               
                                                exit("Username Created");
                                        }
                                } else {
                                        echo "Error: " . mysqli_error($conn);
                                        exit("Username Creation Failed");
                                }
                                exit("Username Created");
                        }
                }
        }
        mysqli_stmt_close($stmt);
        mysqli_close($conn);
}

if ($process_name == "user_login") {
        $login_email = $_POST['login_email'];
        $login_password = $_POST['login_password'];
        if (empty($login_email) || empty($login_password)) {
                exit('Empty Fields');
        } else {
                $sql = "SELECT * FROM tbl_users WHERE email='$login_email'";
                $stmt = mysqli_stmt_init($conn);
                if (!mysqli_stmt_prepare($stmt, $sql)) {
                        exit('SQL Error');
                }
                mysqli_stmt_execute($stmt);
                $result = mysqli_stmt_get_result($stmt);
                if ($row = mysqli_fetch_assoc($result)) {
                        if (password_verify($login_password, $row['password'])) {
                                $_SESSION['user_id'] = $row['user_id'];
                                exit("Valid Credentials");
                        } else {
                                exit("Invalid Password");
                        }
                }
        }
}

if ($process_name == "verify_code") {
        $scan_code = $_POST['scan_code'];
        $user_id = $_SESSION['user_id'];
        $sql = "SELECT * FROM tbl_users WHERE user_id='$user_id'";
        $stmt = mysqli_stmt_init($conn);
        if (!mysqli_stmt_prepare($stmt, $sql)) {
                exit('SQL Error');
        }
        mysqli_stmt_execute($stmt);
        $result = mysqli_stmt_get_result($stmt);
        if ($user_row = mysqli_fetch_assoc($result)) {
                $secret_key = $user_row['google_auth_code'];
                $checkResult = $gauth->verifyCode($secret_key, $scan_code, 2); // 2 = 2*30sec clock tolerance
                if ($checkResult) {
                        $total_logins = ++$user_row['total_logins'];
                        $current_date = date("Y-m-d");
                        $total_logins_sql = "UPDATE tbl_users SET total_logins = '$total_logins', last_login = '$current_date' WHERE user_id='$user_id'";
                        if (!mysqli_stmt_prepare($stmt, $total_logins_sql)) {
                                exit('SQL Error');
                        }
                        mysqli_stmt_execute($stmt);
                        $_SESSION['googleVerifyCode'] = $scan_code;
                        $_SESSION['user_valid'] = true;
                        exit("Verify 2FA Success");
                } else {
                        exit("Note : Code not matched.");
                }
        } else {
                echo "SQL Fetch Failed";
        }
}

if ($process_name == "save_code") {
        $user_id = $_SESSION['user_id'];
        $scan_code = $_POST['scan_code'];
        $security_question = $_POST['security_question'];
        $security_answer = $_POST['security_answer'];
        $sql = "SELECT * FROM tbl_users WHERE user_id='$user_id'";
        $stmt = mysqli_stmt_init($conn);
        if (!mysqli_stmt_prepare($stmt, $sql)) {
                exit('SQL Error');
        }
        mysqli_stmt_execute($stmt);
        $result = mysqli_stmt_get_result($stmt);
        if ($user_row = mysqli_fetch_assoc($result)) {
                $secret_key = $user_row['google_auth_code'];
                $checkResult = $gauth->verifyCode($secret_key, $scan_code, 2); // 2 = 2*30sec clock tolerance
                if ($checkResult) {
                        $total_logins = ++$user_row['total_logins'];
                        $current_date = date("Y-m-d");
                        $security_sql = "UPDATE tbl_users SET total_logins = '$total_logins', last_login = '$current_date', security_question = '$security_question', security_answer = '$security_answer' WHERE user_id='$user_id'";
                        if (!mysqli_stmt_prepare($stmt, $security_sql)) {
                                exit('SQL Error');
                        }
                        mysqli_stmt_execute($stmt);
                        $_SESSION['googleVerifyCode'] = $scan_code;
                        $_SESSION['user_valid'] = true;
                        exit("Saved 2FA Success");
                } else {
                        exit("Note : Code not matched.");
                }
        } else {
                echo "SQL Fetch Failed";
        }
}

if ($process_name == "user_recover") {
        $email = $_POST['recover_email'];
        $sql = "SELECT * FROM tbl_users WHERE email='$email'";
        
        $stmt = mysqli_stmt_init($conn);
        if (!mysqli_stmt_prepare($stmt, $sql)) {
                exit('SQL Error');
        }
        mysqli_stmt_execute($stmt);
        $result = mysqli_stmt_get_result($stmt);
        if ($user_row = mysqli_fetch_assoc($result)) {
                session_destroy();
                session_start();
                $_SESSION['security_question'] = $user_row['security_question'];
                $_SESSION['security_answer'] = $user_row['security_answer'];
                        exit("Grab Security Success");
                } else {
                        exit("Note : Code not matched.");
                }
                exit("Failed");
        }
