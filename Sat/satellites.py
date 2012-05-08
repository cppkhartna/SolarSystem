#! /usr/bin/env python2
# coding=utf-8
from mechanize import Browser
from BeautifulSoup import BeautifulSoup

AU = 149597870.691
c = 500

class Satellite:
    def __init__(self, name, a, e, M0, n, O, i, w):
        self.name, self.a, self.e, self.M0, self.n, self.O, self.i, self.w =  name, a, e, M0, n, O, i, w
    def __repr__(self):
        return repr((self.name, self.a, self.e, self.M0, self.n, self.O,
                self.i, self.w)) 
    def serialize(self):
        print "<Satellite name=\""+self.name+"\""
        print "   a=\""+self.a+"\" e=\""+self.e+"\" M0=\""+self.M0+"\" n=\""+self.n+"\""
        print "   O=\""+self.O+"\" i=\""+self.i+"\" w=\""+self.w+"\" >"
        print "   <Body radius=\"1737.10\" texture=\"Textures/Satellites/moon.bmp\" />"
        #print "   <Body radius=\"1737.10\" texture=\"Textures/Satellites/"+self.name+".bmp\" />"
        print "</Satellite>"



def Retrieve(url):
    mech = Browser()
    page = mech.open(url)

    html = page.read()
    soup = BeautifulSoup(html)
    table = soup.table
    #table = soup.table.table
    data = [ map(str, row.findAll("td")) for row in table.findAll("tr") ]

    for i in range(len(data)):
        for j in range(len(data[i])):
            soup = BeautifulSoup(data[i][j].replace("<br />", "\n"))
            parse = soup.td.getText()
            data[i][j] = parse

    return data

def Parse(data):
    satellites = []
    for j in range(len(data)):
        name = data[j][0]
        a = str(float(data[j][1])/AU*c)
        e = str(float(data[j][2]))
        w = str(float(data[j][3]))
        M0 = str(float(data[j][4]))
        i = str(float(data[j][5]))
        n = str(float(data[j][7])*36525)
        O = str(float(data[j][8]))
        sat = Satellite(name, a, e, M0, n, O, i, w)
        sat.serialize()

url = "file:///home/cppkhartna/Projects/APCe/Sat/jupiter.html"
data = Retrieve(url)
Parse(data)

#print data
