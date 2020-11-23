<?php
include("include/conn.php");
#echo var_dump($_SESSION);
if (empty($_SESSION["user_valid"]) || ($_SESSION["user_valid"] != 1)) {
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

        }

?>

<!doctype html>
<html>
<head>
    <title>Comp 424 Dope Login System</title>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
    <link rel="stylesheet" type="text/css" href="css/app_style.css" charset="utf-8" />
</head>
<body>
    <div class="container">
        <div class="row-fluid">
                <div class="panel panel-info">
                    <div class="panel-heading">
                        <h3 class="panel-title">Hi, <?php echo $user_row['profile_name']; ?></h3>
                    </div>
                    <div class="panel-body">
                        <div class="row">
                            <div class=" col-md-auto">
                            <table class="table table-user-information">
                                    <tbody>
                                        <tr>
                                            <td>User ID:</td>
                                            <td>
                                                <?php echo $user_row[ 'user_id']; ?>
                                            </td>
                                        </tr>
                                        <tr>
                                            <td>Email:</td>
                                            <td>
                                                <?php echo $user_row[ 'email']; ?>
                                            </td>
                                        </tr>
                                        <tr>
                                            <td>Total Logins:</td>
                                            <td>
                                                <?php echo $user_row[ 'total_logins']; ?>
                                            </td>
                                        </tr>
                                        <tr>
                                            <td>Last Login:</td>
                                            <td>
                                                <?php echo $user_row[ 'last_login']; ?>
                                            </td>
                                        </tr>
                                    </tbody>
                                </table>
                                <div class="row">                               
                                <a href="include/file_download.php">
                                    <button type="button" class="btn btn-primary">Download</button>
                                </a>                            
                                </div></br>
                                <div class="row justify-content-end"> 
                                <a href="include/logout.php">
                                <button type="button" style="float: right; margin-right:8%;" class="btn btn-secondary">Logout</button>
                                </div>
                                </a>
                            </div>
                    </div>
            
            </div>
        </div>
    </div>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.0/jquery.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
</body>
</html>