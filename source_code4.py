x = 5
y = 10
if x + y <= 5 and y != (x+(y-a)): print(x) # should be a semantic error
else: print(y)