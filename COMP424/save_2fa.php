<?php
include('include/conn.php');

if(empty($_SESSION['user_id']))
{
	echo "<script> window.location = 'index.php'; </script>";
}
$user_id = $_SESSION['user_id'];
$sql = "SELECT * FROM tbl_users WHERE user_id='$user_id'";
$stmt = mysqli_stmt_init($conn);
	if(!mysqli_stmt_prepare($stmt,$sql)){
        	exit('SQL Error');
        }
        mysqli_stmt_execute($stmt);
        $result = mysqli_stmt_get_result($stmt);
		if($user_row = mysqli_fetch_assoc($result)){
		$secret_key    = $user_row['google_auth_code'];
		$email         		= $user_row['email'];
	} else{
	echo "fail";
	}
?>
<!DOCTYPE html>
<html>
<title>Comp 424 Dope Login System</title>
	<head>
		<link rel="stylesheet" type="text/css" href="css/app_style.css" charset="utf-8" />
		<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
		<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.0/jquery.min.js"></script>
		<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
	</head>
	<body>
	<div class="container">
		<div class="row-fluid">
			<div class="col-md-auto">
				<p>Scan with Google Authenticator application on your smart phone.</p>
			<form id="2fa-form">
			<input type="hidden" id="process_name" name="process_name" value="save_code" />
				<div class="form-group">
					<label for="email">Place your code here:</label>
					<input type="text" name="scan_code" class="form-control" id="scan_code" required />
				</div>
				<div class="form-group">
					<label for="security_question">Choose A Security Question:</label>
					<select name="security_question" id="security_question">
  						<option value="What was your childhood nickname?">What was your childhood nickname?</option>
  						<option value="In what city did you meet your spouse/significant other?">In what city did you meet your spouse/significant other?</option>
  						<option value="What is the name of your favorite childhood friend?">What is the name of your favorite childhood friend? </option>
						<option value="What street did you live on in third grade?">What street did you live on in third grade?</option>
					</select>
				</div>
				<div class="form-group">
					<label for="security_answer">Choose A Security Answer:</label>
					<input type="text" name="security_answer" class="form-control" id="security_answer" required />
				</div>
				<input type="button" class="btn btn-success btn-submit" style="float: right;" value="Submit"/>
			</form>
			</div>
			<div style="text-align:center">
				<h6>Download Google Authenticator <br/> application using this link(s),</h6>
			<a href="https://itunes.apple.com/us/app/google-authenticator/id388497605?mt=8" target="_blank"><img class='app' src="images/iphone.png" /></a>
			<a href="https://play.google.com/store/apps/details?id=com.google.android.apps.authenticator2&hl=en" target="_blank"><img class="app" src="images/android.png" /></a>
			</div>
		</div>
	</div>
	<script src="https://ajax.aspnetcdn.com/ajax/jquery.validate/1.9/jquery.validate.js"></script>
	<script>
		$(document).ready(function(){
			$(document).on('click', '.btn-submit', function(ev){
				if($("#2fa-form").valid() == true){
					var data = $("#2fa-form").serialize();
					$.post('include/check_user.php', data, function(data,status){
						console.log("Submitting result ====> Data: " + data + "\nStatus: " + status);
						if( data == "Saved 2FA Success"){
							window.location = 'logged_in.php';
						}
						else{
							alert("Failed!");
						}
					});
				}
			});
		});
	</script>
	</body>
</html>
