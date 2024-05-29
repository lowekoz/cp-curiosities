#author: lowko527
#about problem: Chinese reminder theorem two equations
#time complexity: O(log(min(n,m))
#mem complexity: O(1)
#usage instruction: Provided is an additional function chinese_remainder_theorem that takes values a,n,b,m and calculates x s.t. x cong. a mon n, x cong. b mod m
# Additional Desc. something curious happens with cpp mod calculations it seems(?)
def extended_gcd(a, b):
    if a == 0:
        return b, 0, 1
    else:
        gcd, p, q = extended_gcd(b % a, a)
        return gcd, q - (b // a) * p, p

def chinese_remainder_theorem(a, n, b, m):
    gcd, p, q = extended_gcd(n, m)
    lcd = (n * m) // gcd
    x = ((a * m * q) + (b * n * p)) // gcd % lcd
    return x, lcd

def main():
    test_cases = int(input())
    for _ in range(test_cases):
        a, n, b, m = map(int, input().split())
        result = chinese_remainder_theorem(a, n, b, m)
        print(*result)

if __name__ == "__main__":
    main()