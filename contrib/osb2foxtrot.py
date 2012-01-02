#!/usr/bin/env python

from xml.etree.ElementTree import parse
import sys, re, hashlib
from pysqlite2 import dbapi2 as sqlite

if len(sys.argv) <3:
  print "usage:"
  print "./osb2foxtrot gpxfile poidbfile"
  print "  gpxfile: a file in the OSB GPX file format, containing bug information"
  print "  poidbfile: usually poi.db, or any other wellformed foxtrotgps poi sqlite database file"
  sys.exit(1)

def escapeQuote(str):
  """escapes single quotes by double single quote, sqlite style"""
  return str.replace('\'', '\'\'');

gpx = open(sys.argv[1])
xml = parse(gpx).getroot()

con = sqlite.connect(sys.argv[2]) 
cur = con.cursor()

for wpt in xml:
  if wpt.tag=="{http://www.topografix.com/GPX/1/1}wpt":
    data = {} # dictionary holding all relevant data to be written into database
    # transfer lat, lon into dictionary directly
    for item in wpt.items():
      data[item[0]]=item[1]
    # transfer information from the sublevel tags into dictionary
    for sub in wpt:
      if sub.tag=="{http://www.topografix.com/GPX/1/1}desc":
        data['desc']=sub.text
    # build the query
    idmd5 = hashlib.md5(data['lon']+data['lat']).hexdigest()[0:18] #not the format foxtrotgps uses
    query = "insert into poi (idmd5, lon, lat, keywords, visibility, cat, subcat, price_range, extended_open, desc) values ('"+idmd5+"', '"+data['lon']+"', '"+data['lat']+"', 'OpenStreetBug', 0.0, 14.0, 2.0, 3.0, 0.0, '"+escapeQuote(data['desc'])+"')" #foxtrotgps crashes if some of these remain NULL.
    cur.execute(query)


con.commit()

