import math


count = 1

while count < 1000 :
    isprime = True
    
    for x in range(2, int(math.sqrt(count) + 1)):
        if count % x == 0: 
            isprime = False
            break
    
    if isprime:
        print(count)
    
    count += 1



