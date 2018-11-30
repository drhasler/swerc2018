from sys import stdin, stdout

lines = stdin.readlines()
n = lines[0]
n = int(n)

score = 0
for line in lines[1:]:
    a,b = line.split()
    a = int(a)
    b = int(b)
    if a>b:
        score +=1
    elif a<b:
        score -=1

stdout.write("done\n")
