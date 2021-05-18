import winreg
import ctypes

INTERNET_SETTINGS = winreg.OpenKey(winreg.HKEY_CURRENT_USER,
                                   r'Software\Microsoft\Windows\CurrentVersion\Internet Settings', 0,
                                   winreg.KEY_ALL_ACCESS)


def set_key(name, value, type):
    winreg.SetValueEx(INTERNET_SETTINGS, name, 0, type, value)


# 0 FOR OFF 1 FOR ON !!!
set_key('ProxyEnable', 0, winreg.REG_DWORD)
set_key('ProxyServer', "localhost:8080", winreg.REG_SZ)

# KEEP SETTINGS AFTER REFRESH
INTERNET_OPTION_REFRESH = 37
INTERNET_OPTION_SETTINGS_CHANGED = 39

internet_set_option = ctypes.windll.Wininet.InternetSetOptionW

internet_set_option(0, INTERNET_OPTION_SETTINGS_CHANGED, 0, 0)
internet_set_option(0, INTERNET_OPTION_REFRESH, 0, 0)
