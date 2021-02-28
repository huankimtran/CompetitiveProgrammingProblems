from sys import stdin

def func(s, last):
    if(0<s and s<1):
        return 1
    d = int(s)
    if(s<(d+tf)):
        return d
    if(s>(d+tr)):
        return d+1
    if(last<(d+tr)):
        return d
    else:
        return d+1
        

tf = float(input())
tr = float(input())
last = 0
for line in stdin:
  s=float(line.strip())
  print(func(s, last))
  d = int(s)
  if(s<(d+tf) or s>(d+tr)):
    last = s
  


