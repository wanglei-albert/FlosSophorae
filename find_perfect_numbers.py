import math

def get_factors_of_num(d):
    if d <= 1:
        # numbers no bigger than 1 is not a perfect number
        return []

    # we use set here to make all facts unique,
    # eg. 6's factors include 1&6, 2&3, 3&2, both 2 and 3 count twice, which is unexpected
    facts = {1}
    for i in range(2, math.ceil(d / 2)):
        if 0 == d % i:
            facts.add(i)
            facts.add(d / i)

    return facts


def get_sum(nums):
    return sum(nums)

def is_perfect_num(d):
    return d == get_sum(get_factors_of_num(d))

if __name__ == '__main__':
    for i in range(1, 1000):
        if is_perfect_num(i):
            print(f'{i} is a perfect number')
        # uncomment the following lines if you would not mind to be disturbed 
        #else:
        #    print(f'{i} is not a perfect number')
