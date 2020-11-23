#!/bin/bash
if [[ $(/usr/bin/id -u) -ne 0 ]]; then
    echo "Script must be running as root. Exiting..."
    exit
fi

if [[ ! -d "websiteCode" ]]; then
	echo "Please place your website files in the directory \"websiteCode\" before proceeding. Exiting..."
	exit
fi

apt update # Updating software list
DEBIAN_FRONTEND=noninteractive apt full-upgrade -y # Upgrading software on the operating system
DEBIAN_FRONTEND=noninteractive apt install -y openssh-server apache2 mysql-server php libapache2-mod-php php-mysql php-curl dnsutils # Installing required software
sed -i -e 's/index.html/index.php index.html/g' /etc/apache2/mods-enabled/dir.conf # Adding index.php as an option for Apache2
systemctl restart apache2 # Restarting Apache2 to make the above configuration take effect
mysql -e "create user '424Admin'@'localhost' identified by '424Group';" # Creating a user for the webserver
mysql -e "create database 424Admin;" # Creating a database for the webserver
mysql -e "create table 424Admin.tbl_users(user_id INT NOT NULL PRIMARY KEY AUTO_INCREMENT, email VARCHAR(120) NULL, password VARCHAR(200) NULL, security_question MEDIUMTEXT NULL, security_answer TEXT NULL, profile_name VARCHAR(100) NULL, google_auth_code VARCHAR(16) NULL, created_at VARCHAR(15) NULL, last_login VARCHAR(15), total_logins INT NOT NULL;" # Creating a table to store user credentials
#mysql -e "create table 424Admin.lockout(id INT NOT NULL PRIMARY KEY AUTO_INCREMENT, username VARCHAR(50) NOT NULL UNIQUE, num_fails INT DEFAULT 0)" # Creating separate table for lockout system
#mysql -e "create table 424Admin.email_verification(id INT NOT NULL PRIMARY KEY AUTO_INCREMENT, email VARCHAR(100) NOT NULL UNIQUE, ver_key VARCHAR(255) NOT NULL);" # Creating separate table for email verification
#mysql -e "create table 424Admin.password_reset(id INT NOT NULL PRIMARY KEY AUTO_INCREMENT, email VARCHAR(100) NOT NULL UNIQUE, ver_key VARCHAR(255) NOT NULL);" # Creating separate table for password resets
#mysql -e "create table 424Admin.sign_on_logs(id INT NOT NULL PRIMARY KEY AUTO_INCREMENT, username VARCHAR(100) NOT NULL, success BOOLEAN NOT NULL, time DATETIME DEFAULT CURRENT_TIMESTAMP);" # Creating separate table for sign on logs
#mysql -e "grant insert on 424Admin . users to '424Admin'@'localhost';" # Granting permission to insert registration data to the webserver user
#mysql -e "grant update on 424Admin . users to '424Admin'@'localhost';" # Granting permission to update registration data to the webserver user
#mysql -e "grant select on 424Admin . users to '424Admin'@'localhost';" # Granting permission to view registration data to the webserver user
#mysql -e "grant insert on 424Admin . email_verification to '424Admin'@'localhost';" # Granting permission to insert data to the webserver user
#mysql -e "grant update on 424Admin . email_verification to '424Admin'@'localhost';" # Granting permission to update data to the webserver user
#mysql -e "grant select on 424Admin . email_verification to '424Admin'@'localhost';" # Granting permission to view data to the webserver user
#mysql -e "grant delete on 424Admin . email_verification to '424Admin'@'localhost';" # Granting permission to delete data to the webserver user
#mysql -e "grant insert on 424Admin . lockout to '424Admin'@'localhost';" # Granting permission to insert data to the webserver user
#mysql -e "grant update on 424Admin . lockout to '424Admin'@'localhost';" # Granting permission to update data to the webserver user
#mysql -e "grant select on 424Admin . lockout to '424Admin'@'localhost';" # Granting permission to view data to the webserver user
#mysql -e "grant insert on 424Admin . password_reset to '424Admin'@'localhost';" # Granting permission to insert data to the webserver user
#mysql -e "grant update on 424Admin . password_reset to '424Admin'@'localhost';" # Granting permission to update data to the webserver user
#mysql -e "grant select on 424Admin . password_reset to '424Admin'@'localhost';" # Granting permission to view data to the webserver user
#mysql -e "grant delete on 424Admin . password_reset to '424Admin'@'localhost';" # Granting permission to delete data to the webserver user
#mysql -e "grant insert on 424Admin . sign_on_logs to '424Admin'@'localhost';" # Granting permission to insert logs to the webserver user
#mysql -e "grant select on 424Admin . sign_on_logs to '424Admin'@'localhost';" # Granting permission to view logs to the webserver user
mysql -e "flush privileges;" # Updating the privileges to make the above configuration take effect

rm -rf /var/www/*
cp -r websiteCode/* /var/www/
chown -R root:www-data /var/www/* # Ownership limited to root & www-data

chmod -R 2750 /var/www/* # Permissions s.t. all new files are owned by groupdir so our webserver can read them; other has no perms in case accounts are compromised on server
rm -rf /root/.bash_history /root/.mysql_history # Removing histories to prevent users from reading the passwords saved in history
