#from shutil import copyfile
#copyfile('/Users/AuTo/AppData/Roaming/discord/Cookies', '/Users/AuTo/Desktop/tempCookies')
import shutil	
import hashlib
blocksize = 65536

def copyFile(src, dest):
    try:
        shutil.copy(src, dest)
        print('got here')
    # eg. src and dest are the same file
    except shutil.Error as e:
        print('Error: %s' % e)
    # eg. source or destination doesn't exist
    except IOError as e:
        print('Error: %s' % e.strerror)
src = '/Users/AuTo/AppData/Roaming/discord/Cookies'
des = '/Users/AuTo/Desktop/tempCookies'

def sha256sum(filename):
    h  = hashlib.sha256()
    b  = bytearray(128*1024)
    mv = memoryview(b)
    with open(filename, 'rb', buffering=0) as f:
        for n in iter(lambda : f.readinto(mv), 0):
            h.update(mv[:n])
    return h.hexdigest()



filename1 = 'file1.txt'
fileA = open(src, 'rb')
chunk = fileA.read(blocksize)
print(sha256sum(fileA))
filename2 = 'file5.txt'
fileB = open(des, 'wb')

shutil.copyfileobj(fileA, fileB)


