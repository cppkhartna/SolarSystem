#! /usr/bin/env python2
# coding=utf-8
from mechanize import Browser
from BeautifulSoup import BeautifulSoup

AU = 149597870.691
jupiter = 200
saturn = 500
uranus = 350
c = uranus

class Satellite:
    def __init__(self, name, a, e, M0, n, O, i, w, rad):
        self.name, self.a, self.e, self.M0, self.n, self.O, self.i, self.w, self.rad =  name, a, e, M0, n, O, i, w, rad
    def __repr__(self):
        return repr((self.name, self.a, self.e, self.M0, self.n, self.O,
                self.i, self.w, self.rad)) 
    def serialize(self):
        print "<Satellite name=\""+self.name+"\""
        print "   a=\""+self.a+"\" e=\""+self.e+"\" M0=\""+self.M0+"\" n=\""+self.n+"\""
        print "   O=\""+self.O+"\" i=\""+self.i+"\" w=\""+self.w+"\" >"
        print "   <Body radius=\""+self.rad+"\" texture=\"Textures/Satellites/"+self.name.lower()+".bmp\" />"
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
        #rad = str(float(data[j][14])) # other
        rad = str(float(data[j][11])) # uranus
        sat = Satellite(name, a, e, M0, n, O, i, w, rad)
        sat.serialize()

#url = "file:///home/cppkhartna/Projects/APCe/SolarSystem/Sat/jupiter.html"
#url = "file:///home/cppkhartna/Projects/APCe/SolarSystem/Sat/saturn.html"
url = "file:///home/cppkhartna/Projects/APCe/SolarSystem/Sat/uranus.html"
data = Retrieve(url)
Parse(data)

#print data
