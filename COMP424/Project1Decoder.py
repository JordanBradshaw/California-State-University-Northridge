from itertools import permutations
import math
       #6204315
key = "7315426"
englishWords = {}
cipherText = "KUHPVIBQKVOSHWHXBPOFUXHRPVLLDDWVOSKWPREDDVVIDWQRBHBGLLBBPKQUNRVOHQEIRLWOKKRDD"
def loadDictionary():
    dictionaryFile = open('dict.txt')
    englishWords = {}
    for word in dictionaryFile.read().split('\n'):
        englishWords[word] = None
    dictionaryFile.close()
    return englishWords

englishDictionary = loadDictionary()

#CAESAR SHIFT FUNCTION
def manualCaesarShift(shift):
    secondListCipher = []
    firstListCipher = list(cipherText)
    for letter in firstListCipher:
        intTemp = ord(letter)
        if (intTemp - shift) < 65:
            intTemp = (intTemp - shift) + 26
        else:
            intTemp -= shift
        charTemp = chr(intTemp)
        
        secondListCipher.append(charTemp)
    return secondListCipher

shiftedCipherText = (manualCaesarShift(3))
print(''.join(shiftedCipherText))

UPPERLETTERS = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
LETTERS_AND_SPACE = UPPERLETTERS + UPPERLETTERS.lower() + ' \t\n'



def testEnglish(message):
    message = message.lower()
    matches = 0
    for x in englishDictionary:
        if (message.find(x) != -1):
            matches += 1
    if matches >= 30: return True
    else: return False

def decryptMessage(cipher,tempPerm):
    key = tempPerm
    msg = ""
    k_indx = 0
    msg_indx = 0
    msg_len = float(len(cipher)) 
    msg_lst = list(cipher)
    col = len(key)
    row = int(math.ceil(msg_len / col))
    key_lst = sorted(list(key)) 
    dec_cipher = [] 
    for _ in range(row): 
        dec_cipher += [[None] * col] 
    for _ in range(col): 
        curr_idx = key.index(key_lst[k_indx]) 
        for j in range(row): 
            if (msg_indx < msg_len):
                dec_cipher[j][curr_idx] = msg_lst[msg_indx] 
            else:
                dec_cipher[j][curr_idx] = '' #KEPT THROWING NULL POINTS WITH None SO FILLED IT WITH ''
            msg_indx += 1
        k_indx += 1
    try: 
        msg = ''.join(sum(dec_cipher, [])) 
    except TypeError: 
        raise TypeError("This program cannot", 
                        "handle repeating words.")
    null_count = msg.count('_') 
    if null_count > 0: 
        return msg[: -null_count] 
    return msg

#PERMUTATION GENERATOR
for x in range(2,8):
    numList = list(range(0,x))
    permList = permutations(numList)
    for i in list(permList):
        currString = decryptMessage(shiftedCipherText,i)
        if (testEnglish(currString) == True):
            print(currString)