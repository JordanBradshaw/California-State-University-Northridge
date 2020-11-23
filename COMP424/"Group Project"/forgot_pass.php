<?php
	include("include/conn.php");
?>

<!DOCTYPE html>
<html>

<head>
	<title>Comp 424 Dope Login System</title>
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.0/jquery.min.js"></script>
	<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>

	<link rel="stylesheet" type="text/css" href="css/app_style.css" charset="utf-8" />
	<script src="https://cdnjs.cloudflare.com/ajax/libs/zxcvbn/4.2.0/zxcvbn.js"></script>
	<script src="https://www.google.com/recaptcha/api.js"></script>
</head>

<body>
	<div class="container">
		<div class="row-fluid">
			<div class="col-md-auto">
				<div class="form-body">
							<div class="inner-form">
								<form name="recover-form" id="recover-form">
									<input type="hidden" id="process_name" name="process_name" value="user_recover" />
									<div class="errorMsg errorMsgReg"></div>
									<div class="form-group">
										<label for="recover_email">Email:</label>
										<input type="email" name="recover_email" class="form-control" id="recover_email" required />
									</div>
									<button type="button" class="btn btn-success btn-recover-submit">Submit</button>
								</form>
							</div>
				</div>
			</div>
		</div>
		<script src="https://ajax.aspnetcdn.com/ajax/jquery.validate/1.9/jquery.validate.js"></script>
		<script>
				$(document).on('click', '.btn-recover-submit', function(ev) {
					if ($("#recover-form").valid() == true) {
						var data = $("#recover-form").serialize();
						$.post('include/check_user.php', data, function(data, status) {
							console.log("Submitting Result => Data: " + data + "\nStatus: " + status);
							if (data == "Grab Security Success") {
                                var security_question = <?php echo json_encode($_SESSION['security_question']) ?>;
                                var security_answer = <?php echo json_encode($_SESSION['security_answer']) ?>;
                                var prompt_response = prompt(security_question,"");
				if (prompt_response == security_answer){
					alert("They Match");
					var new_password = prompt("New Password?","");
					var push_email = document.getElementById("recover_email").value;
					$.post( "recoverMail.php" ,{email: push_email ,newPass: new_password});
						alert("Sent to email!");
				

				}
                                else{
                                    alert("They do not match");				    
                                }
								window.location = 'verify_2fa.php';
							} else {
			
							alert("Failed");
							}

						});
                    }
				});
		</script>
</body>
</html>
