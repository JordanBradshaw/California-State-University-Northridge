import pickle
import re

from bs4 import BeautifulSoup


soup = BeautifulSoup(html_doc,'html.parser')
soup = str(soup.find_all(string=re.compile("@")))
soup = soup.replace("None", "")
soup = re.sub('\,\d*\,','',soup)
print(re.sub('[:!()]*\w*label(\w|\:|\!|\(|\)|\^)*','',soup))



## WORKING HTML PARSER
soup = BeautifulSoup(html_doc,'html.parser')
temp = soup.find_all('div',dir="ltr")
for item in temp:
    print(item.get_text())
