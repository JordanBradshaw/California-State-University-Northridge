
from itertools import combinations

totalKeys = ("StudentNumber","StudentFName","StudentLName","Class","Grade","Semester")
keyList = []
for combCount in range(2,7):
    comb = combinations(["StudentNumber","StudentFName","StudentLName","Class","Grade","Semester"],combCount)
    for i in list(comb):
        if i.count("Class") != 0 and i.count("StudentNumber") != 0:
            keyList.append(i)

keyList.reverse()


###TRIVIAL GENERATOR!
def trivPermRunner(tempKey):
    for i in range(1,len(tempKey)+1):
        rightSideComb = combinations(tempKey,i)
        for comb in rightSideComb:
            key = "{" + ', '.join(item) + "} " + "-->" + " {" + ', '.join(comb) + "}"
            print(key)

###NON-TRIVIAL GENERATOR!
def nonTrivPermRunner(tempKey):
    differenceKey = set(totalKeys) ^ set(tempKey)
    for i in range(1,len(differenceKey)+1):
        rightSideComb = combinations(differenceKey,i)
        for comb in rightSideComb:
            key = "{" + ', '.join(item) + "} " + "-->" + " {" + ', '.join(comb) + "}"
            print(key)
    pass

###FOR TRIV
print("Trivial:")
for item in keyList:
    trivPermRunner(item)
for key in totalKeys:
    print("{" + key + "} " + "-->" + " {" + key + "}")
    
###FOR NON TRIV
print("Non-Trivial:")
for item in keyList:
    nonTrivPermRunner(item)
