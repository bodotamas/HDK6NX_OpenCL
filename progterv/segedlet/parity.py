def parity(x):
    """Parity - recursive version"""
    if x == 0:
        return 1
    elif x % 2 == 0:
        y = parity(x - 1)
        y = y + x
        return y
    else:
        y = parity(x - 1)
        y = y * x
        return y


def parity2(x):
    """Parity - iterative version"""
    y = 1
    for i in range(x + 1):
        if i % 2 == 0:
            y += i
        else:
            y *= i
    return y


for i in range(10):
    print('{} -> {}'.format(i, parity(i)))

for i in range(10):
    print('{} -> {}'.format(i, parity2(i)))
