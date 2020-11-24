Lab6
Super hard for while I finally feel I understand what was requested.
Make sure you have mole.exe in daemon directory for it to call and create the long.
The reason being is when its waiting for signals it wont write initially.

./spiritd

ps -axj | grep "spiritd" <~~~ Check ppid if init or systemmd owns

running the next line will post text to a log file from mole
kill -(USR1 or USR2) daemonPID

to close
kill -TERM daemonPID
