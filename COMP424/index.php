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
					<ul class="nav nav-tabs nav-justified final-login">
						<li class="active">
							<a data-toggle="tab" href="#sectionA">Sign Up!</a>
						</li>
						<li>
							<a data-toggle="tab" href="#sectionB">Log In!</a>
						</li>
					</ul>
					<div class="tab-content">
						<div id="sectionA" class="tab-pane fade in active">
							<div class="inner-form">
								<form name="signup-form" id="signup-form">
									<input type="hidden" id="process_name" name="process_name" value="user_register" />
									<div class="errorMsg errorMsgReg"></div>
									<div class="form-group">
										<label for="name">Full Name:</label>
										<input type="text" name="reg_name" class="form-control" id="reg_name" required />
									</div>
									<div class="form-group">
										<label for="birthday">Birthday:</label>
										<input type="date" style="text-align:center;" name="reg_birthday" class="form-control" id="reg_birthday" required />
									</div>
									<div class="form-group">
										<label for="email">Email:</label>
										<input type="email" name="reg_email" class="form-control" id="reg_email" required />
									</div>
									<div class="form-group">
										<label for="password">Password:</label>
										<input type="password" name="reg_password" class="form-control" id="reg_password" required />
										<meter max="4" id="password-strength-meter"></meter>
										<p id="password-strength-text"></p>
									</div>
									<script type="text/javascript">
										var strength = {
											0: "Worst",
											1: "Bad",
											2: "Weak",
											3: "Good",
											4: "Strong"
										}
										var password = document.getElementById('reg_password');
										var meter = document.getElementById('password-strength-meter');
										var text = document.getElementById('password-strength-text');
										password.addEventListener('input', function() {
											var val = password.value;
											var result = zxcvbn(val);
											// Update the password strength meter
											meter.value = result.score;
											// Update the text indicator
											if (val !== "") {
												text.innerHTML = "Strength: " + strength[result.score];
											} else {
												text.innerHTML = "";
											}
										});
									</script>
									<div class="form-group">
										<label for="password2">Re-enter Password:</label>
										<input type="password" name="reg_password2" class="form-control" id="reg_password2" required />
									</div>
									<div class="form-group">
										<label for="g-recaptcha">Captcha:</label></br>
										<div class="g-recaptcha" style="display:inline-block;" data-sitekey="6Ld7hdoZAAAAAJU-5NRUaR5Yjdql42oEkmjZtUeP"></div>
									</div>
									<button type="button" class="btn btn-primary btn-reg-submit">Submit</button>
								</form>
								<div class="clearfix"></div>
							</div>
						</div>
						<div id="sectionB" class="tab-pane fade">
							<div class="inner-form">
								<form name="login-form" id="login-form">
									<input type="hidden" id="process_name" name="process_name" value="user_login" />
									<div class="errorMsg errorMsgReg"></div>
									<div class="form-group">
										<label for="login_email">Email:</label>
										<input type="email" name="login_email" class="form-control" id="login_email" required />
									</div>
									<div class="form-group">
										<label for="login_password">Password:</label>
										<input type="password" name="login_password" class="form-control" id="login_password" required />
									</div>
									<a href="forgot_pass.php">Forgot Password</a>
									<button type="button" class="btn btn-success btn-login-submit">Login</button>
								</form>
							</div>
						</div>
					</div>
				</div>
			</div>
		</div>
		<script src="https://ajax.aspnetcdn.com/ajax/jquery.validate/1.9/jquery.validate.js"></script>
		<script>
			$(document).ready(function() {
				$(document).on('click', '.btn-reg-submit', function(ev) {
					if ($("#g-recaptcha-response").val() == "") {
						alert("Captcha not selected!");
					} else if ($("#reg_password").val() != $("#reg_password2").val()) {
						alert("Password fields are not the same!");
					} else if ($("#signup-form").valid() == true) {
						var data = $("#signup-form").serialize();
						$.post('include/check_user.php', data, function(data, status) {
							console.log("Submitting Result => Data: " + data + "\nStatus: " + status);
							if (data == "Username Created") {
								$.post("testMail.php");
								window.location = 'save_2fa.php';
							} else {
								alert("Failed");
							}
						});
					}
				});
				$(document).on('click', '.btn-login-submit', function(ev) {
					if ($("#login-form").valid() == true) {
						var data = $("#login-form").serialize();
						$.post('include/check_user.php', data, function(data, status) {
							console.log("Submitting Result => Data: " + data + "\nStatus: " + status);
							if (data == "Valid Credentials") {
								window.location = 'verify_2fa.php';
							} else {
								alert("Failed");
							}
						});
					}
				});
				/* ebd submit form details */
			});
		</script>
</body>

</html>
