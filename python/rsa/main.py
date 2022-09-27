def is_primary(num):
    for i in range(2, int(num / 2)):
        if num % i == 0:
            return False
    return True

def are_primary(num1, num2):
    for i in range(2, min(num1, num2) + 1):
        if num1 % i == 0 and num2 % i == 0:
            return False
    return True

def generate_primary_nums(max, cout):
    arr = [i for i in range(max + 1)]

    i = 2
    while i <= max:
        if arr[i] != 0:
            j = i * 2
            while j <= max:
                arr[j] = 0
                j += i
        i += 1
    arr = list(set(arr))
    return arr[-cout:]

def generate_primary_nums2(max, min, cout):
    arr = []
    for i in range(min, max+1):
        if is_primary(i):
            arr += [i]
    return arr[-cout:]

def generate_n(p, q):
    return p * q

def generate_m(p, q):
    return (p - 1) * (q - 1)

def generate_d(m, low_limit = 10):
    for i in range(low_limit, m):
        if are_primary(i, m):
            return i
    return -1

def generate_e(d, m):
    e = 1
    while e * d % m != 1:
        e += 1
    return e


print(generate_e(generate_d(1000, 40), 1000))
print(generate_primary_nums2(100000, 1, 2))