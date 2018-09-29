class SieveMatrix(object):
    FILTERED = -99
    def __init__(self, dimIn=20):
        if dimIn < 2 or dimIn > 20:
            raise RuntimeError("Error: bad matrix size. Must be [2 .. 20].")
        self.size = dimIn
        self.matrix = []
        self.matrix = list(range(self.size))
        start = 1
        for row in range(self.size):
            self.matrix[row] = list(range(start, start + self.size))
            start += self.size

    def filterMatrix(self, num):
        if num < 2:
            return

        for i in range(self.size):
            for j in range(self.size):
                if self.matrix[i][j] % num == 0 and self.matrix[i][j] != num:
                    self.matrix[i][j] = SieveMatrix.FILTERED

    def __str__(self):
        s = ''
        for row in self.matrix:
            for element in row:
                if element == SieveMatrix.FILTERED:
                    s += '    '
                else:
                    s += "{0:>4}".format(element)
            s += '\n'
        return s

if __name__ == "__main__":

    print("\nconstructor attempt 1x1. return with error message")
    try:
        m = SieveMatrix(1)
    except RuntimeError as e:
        print(e)
    print("\nconstructor attempt 0x0. return with error message")
    try:
        m = SieveMatrix(0)
    except RuntimeError as e:
        print(e)
    print("\nconstructor attempt -2x-2. return with error message")
    try:
        m = SieveMatrix(-2)
    except RuntimeError as e:
        print(e)
    print("\nconstructor attempt 21x21. return with error message")
    try:
        m = SieveMatrix(21)
    except RuntimeError as e:
        print(e)

    print("\nconstructor makes 5x5, filter 2's.  Must leave 2 and delete all other evens")
    m = SieveMatrix(5)
    m.filterMatrix(2)
    print(m)

    print("\nfilter 3's, 4's and 5's  Must leave primes only, 1,2,3 5 still present.")
    m.filterMatrix(3)
    m.filterMatrix(4)
    m.filterMatrix(5)
    print(m)

    print("\nfilter 0, 1, -1, -99, no crases no more items deleted")
    m.filterMatrix(0)
    m.filterMatrix(1)
    m.filterMatrix(-1)
    m.filterMatrix(-99)
    print(m)

    print("constructor makes 5x5, filter 0, 1, -1, 25, 26 no crashes no items deleted")
    m = SieveMatrix(5)
    m.filterMatrix(0)
    m.filterMatrix(1)
    m.filterMatrix(-1)
    m.filterMatrix(25)
    m.filterMatrix(26)
    print(m)

    print("default constructor makes 20x20 and __str__ prints it correctly")
    m = SieveMatrix()
    print(m)











