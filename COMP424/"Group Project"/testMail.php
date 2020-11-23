<?php
include 'include/conn.php';
use PHPMailer\PHPMailer\PHPMailer;
use PHPMailer\PHPMailer\Exception;
use PHPMailer\PHPMailer\SMTP;
require_once "vendor/autoload.php";

require_once "include/GoogleAuthenticator.php";

$gauth = new GoogleAuthenticator();
if (empty($_SESSION['user_id'])) {
	echo "<script> window.location = 'index.php'; </script>";
}
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
	$email = $user_row['email'];
	$google_QR_Code = $gauth->getQRCodeGoogleUrl($email, $secret_key, 'COMP424');
} else {
	echo "fail";
}

//PHPMailer Object
$mail = new PHPMailer(true); //Argument true in constructor enables exceptions

//Enable SMTP debugging.
$mail->SMTPDebug = 3;                               
//Set PHPMailer to use SMTP.
$mail->isSMTP();            
//Set SMTP host name                          
$mail->Host = "smtp.gmail.com";
//Set this to true if SMTP host requires authentication to send email
$mail->SMTPAuth = true;                          
//Provide username and password     
$mail->Username = "temp@gmail.com";                 
$mail->Password = "Testing123!";                           
//If SMTP requires TLS encryption then set it
$mail->SMTPSecure = "tls";                           
//Set TCP port to connect to
$mail->Port = 587;                                   



//From email address and name
$mail->From = "temp@gmail.com";
$mail->FromName = "JB";

//To address and name
$mail->addAddress("$email", "Recepient Name");
#$mail->addAddress("recepient1@example.com"); //Recipient name is optional

//Address to which recipient will reply
$mail->addReplyTo("$email", "Reply");

//CC and BCC
#$mail->addCC("cc@example.com");
#$mail->addBCC("bcc@example.com");

//Send HTML or Plain Text email
$mail->isHTML(true);

$mail->Subject = "Subject Text";
$mail->Body = $google_QR_Code;
$mail->addStringAttachment(file_get_contents($google_QR_Code), "QR");

$mail->AltBody = "This is the plain text version of the email content";

try {
    $mail->send();
    echo "Message has been sent successfully";
} catch (Exception $e) {
    echo "Mailer Error: " . $mail->ErrorInfo;
}
?>
