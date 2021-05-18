import re
import requests

f = open("output.txt", "r")
lineArray = f.readlines()
index = 0

# IF DOES NOT CONTAIN GET MAKE EMPTY STRING
for line in lineArray:
    if line.find("GET") == -1 or line.find("x-super-properties") == -1 or line.find("messages?limit=50") == -1:
        lineArray[index] = ""
    index += 1

### EMPTY LINE CLEANER
while lineArray.count("") > 0:
    lineArray.remove("")

for item in lineArray:
    print(item)

referProp, superProp, authProp, cookieProp = "", "", "", ""
##REGEX
for line in lineArray:
    referProp = re.findall("referer,\d+\:[\w\.\:\/\@]+", line)
    superProp = re.findall("x-super-properties,\d+\:\w+\=", line)
    authProp = re.findall("authorization,\d+\:[\w\.]+", line)
    cookieProp = re.findall("cookie,\d+\:\_\_[\w\=\;\s\-]+", line)
    print("Hello")
    print(referProp)
    print(superProp)
    print(authProp)
    print(cookieProp)

##BREAK DOWN TO GET STRINGS
referIndex = referProp[0].index("@me")
referId = referProp[0][referIndex + 4:]
referIdString = "https://discord.com/api/v8/channels/" + referId + "/messages"

superIndex = superProp[0].index(":")
superIdString = superProp[0][superIndex + 1:]

authIndex = authProp[0].index(":")
authIdString = authProp[0][authIndex + 1:]

cookieIndex = cookieProp[0].index(":")
cookieIdString = cookieProp[0][cookieIndex + 1:] + ""

print(referIdString)
print(superIdString)
print(authIdString)
print(cookieIdString)

a = requests.get(
    referIdString,
    headers={
        "x-super-properties": superIdString,
        "authorization": authIdString,
        "accept-language": "en-US",
        "user-agent": "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) discord/0.0.309 Chrome/83.0.4103.122 Electron/9.3.5 Safari/537.36",
        "accept": "*/*",
        "sec-fetch-site": "same-origin",
        "sec-fetch-mode": "cors",
        "sec-fetch-dest": "empty",
        "referer": "https://discord.com/channels/@me",
        "accept-encoding": "gzip, deflate",
        "cookie": cookieIdString,
    },
)
tempA = str(a.content)
# print(tempA)
idList = re.findall('"id"\: "\d+"', tempA)
messageId = idList[-2][7:-1]


# print(messageId)
def messageStringBuilder(messID):
    return referIdString + "?before=" + messID


newreferIdString = referIdString + "?before=" + messageId
print(newreferIdString)


def recursiveGetRequest(ref, sup, auth, cookie, currentMessageId):
    b = requests.get(
        ref,
        headers={
            "x-super-properties": sup,
            "authorization": auth,
            "accept-language": "en-US",
            "user-agent": "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) discord/0.0.309 Chrome/83.0.4103.122 Electron/9.3.5 Safari/537.36",
            "accept": "*/*",
            "sec-fetch-site": "same-origin",
            "sec-fetch-mode": "cors",
            "sec-fetch-dest": "empty",
            "referer": "https://discord.com/channels/@me",
            "accept-encoding": "gzip, deflate",
            "cookie": cookie,
        },
    )
    tempB = str(b.content)
    idList = re.findall('"id"\: "\d+"', tempB)
    try:
        nextMessageId = idList[-2][7:-1]
    except IndexError:
        return (None, None), None
    return (currentMessageId, b.content), nextMessageId


byteList = []
nextMessage = idList[-2][7:-1]
# for runner in range(0,6):
returnTup = 0
while nextMessage != None:
    try:
        newreferIdString = messageStringBuilder(nextMessage)
        returnTup, nextMessage = recursiveGetRequest(newreferIdString, superIdString, authIdString, cookieIdString,
                                                     nextMessage)
        print(returnTup)
    except:
        break
