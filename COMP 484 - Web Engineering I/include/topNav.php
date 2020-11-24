 <?php
 session_start();
 ?>
 <div class="topnav"><div class="login-container">
<?php
if(isset($_SESSION['IDuser'])){
  echo '<form action="include/logoutSubmit.php">
   <input type="submit" id="logoutButton" value="Logout" name="logoutButton" />
    </form>';
  }else{
  echo '
  <form method="post" >
    <input type="text" id="usernameNav" placeholder="Username" name="usernameText">
    <input type="password" id="passwordNav" placeholder="Password" name="passwordText">
    <input type="button" id="loginButton" value="Login" name="loginButton" />
    </form>';
  }
  ?>
  
  </div>
</div> 


