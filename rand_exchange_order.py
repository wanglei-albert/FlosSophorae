# this demo shows how to adapt the Probality Theory into data set ordering
import random

#  check the randomly hit element with its pre-element and post-element and change their order if need
#  issues: still uncertain when to stop the process as soon as the input data having been in order as expected
def sort_rand(lp, t):
    l = lp
    l_sz = len(l)
    for n in range(t):
        i = random.randint(1, l_sz - 2)
        if l[i] < l[i-1]:
            l[i - 1 ], l[i] = l[i], l[i - 1]
        if l[i] > l[i + 1]:
            l[i], l[i+1] = l[i + 1], l[i]

    return l

if __name__ == '__main__':

    l = []
    for i in range(30):
        l.append(random.randint(-300, 300))
    print('****** origin list *******')
    print(l)
    
    for i in range(len(l), len(l) * len(l)):
        print('%d iterations**********'%(i))
        print(sort_rand(l, i))
