import random
for x in range(10000):
    c = range(5)
    random.shuffle(c)
    print ''.join(str(x) for x in c)
