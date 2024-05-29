/*
author: lowko527
about problem: Modular arithmetic is not uncommon to use in calculations with large numbers, provided is a general mod int class used if the modular number n is prime, also GCD and ext_GCD alg.
time complexity: O(log(min(a, b)) (from gcd)
mem complexity: O(1)
usage instruction: Mint used as normal type, see desc of GCD and extended GCD.
assumptions:
*/


#ifndef TEMPLATE
#include<bits/stdc++.h>
using namespace std;

const char nl = '\n';
#define _ << " " <<
const int INF = INT_MAX;
// const int MOD = (int)1e9 + 7;
long long MOD = (long long)1e18;
#endif

template<typename T>
void prp(vector<pair<T, T>>& a) {
    for (auto& p : a) {
        cout << "{" << p.first << " " << p.second << "}" << " ";
    }
    cout << nl;
}

// Modular int class with built in operations (operating under mod MOD, inverse function functions only if MOD i prime)
struct Mint {
    //static_assert(MOD < (long long)1e10, "Custom Mint console message: assert err, MOD greater than or eq. to 1e10");
private:
    long long value; // om vore public


public:
    Mint() {
        this->value = 0;
    }

    //implicit conversion, med denna constructor kan konverta long long till Mints.
    Mint(long long init_value) {
        if (init_value < 0 || init_value > MOD) init_value %= MOD;
        this->value = init_value;
    }

    // referens, ta via pointer och behöver dereferera -> operation som tar tid.
    //Struct kopierar bara fiedls, och vi har bara en long long så borde gå ca. lika snabbt
    friend bool operator==(const Mint a, const Mint b) {
        return a.value == b.value;
    }

    // förutsätter value inom [0..MOD-1]
    bool operator!=(const Mint rhs) {
        return !(*this == rhs); // kallar på den övre func. Notera att denna metod, kan vara smidig för uppbyggnad av större structs för att maintaina logik.
        // howev. då bör du ha referenser om många fält s.a. inte onädigt mycket kopierande
    }

    bool operator<(Mint rhs) {
        return value < rhs.value;
    }

    // eftersom += antar att vi ändrar på this->value, därför &
    Mint& operator+=(const Mint rhs) {
        this->value += rhs.value;
        if ((this->value >= MOD)) this->value -= MOD;
        return *this;
    }

    // eftersom båda är Mint:s så vet vi att det räcker med att adeera MOD en gång tops om negativ
    Mint& operator-=(const Mint rhs) {
        this->value -= rhs.value;
        if ((this->value < 0)) this->value += MOD;
        return *this;
    }

    Mint& operator*=(const Mint rhs) {
        this->value *= rhs.value; //1e9*1e9 is close to max ~ 9*1e18
        if ((this->value >= MOD)) this->value %= MOD;

        //assert(); // debug and correction purposes if want implemented

        return *this;
    }

    // kongruens ekvation a/b kong. x mod m, vill åt x som i a kong. bx (mod m) är b^{-1}*a
    Mint& operator/=(const Mint rhs) {
        return *this *= rhs.getInverse();
    }

    friend Mint pow(Mint a, long long p) {
        Mint ans = 1; assert(p >= 0);
        for (; p; p /= 2, a *= a) if (p & 1) ans *= a;
        return ans;
    }

    //friend Mint pow(Mint us, long long p); // i och med detta får pow från utsidan komma åt privata variabler


    // Fermats sats för att beräkna multiplicative modulär inversen
    // a^{p-1} kong. 1 mod p om p är prim.
    // finns bara en modulär invers förutsatt att gcd(MOD,a) = 1.
    //https://blogarithms.github.io/articles/2019-01/fermats-theorem
    Mint getInverse() const {
        //value have somehow recieved a factor MOD, which unables us from calculating mod inv.
        assert(value != 0); // inverse does not exist, happens when denominator in choose function contains the term MOD in its multiplication. n-k<MOD, k<MOD

        // using Fermats little theorem, NOTE THAT fermats little theorem gives a number cong. 1 % MOD, therefore -2
        // example, we have A cong. 6x mod 13, now fermats holds for 6 and 13 hence 6^12 is congruent to 1 mod 13
        // hence, A*6^11 is our answer for x, bc. 6*6^11 gives 1 cong, then * A.
        return pow(*this, MOD - 2);
    }


    // för att kunna printa till stdout - alt ta value till long long
    //friend ostream& operator<<
    /*operator long long() {
            return this->value;
    }*/ // implicit conversion tillåter andra template implementerade functioner att göra assumptions om vilka types vi nu kan ta, eftersom de bara kan implicit convertas
    // dvs. är egentligen en long long men long long kan tolkas som long double och därav overload problem?

    // måste dock long long () varje gång printa
    explicit operator long long() {
        return this->value;
    }

    // const i detta sammanhang declarerat efter (), säger att det du utför function på är const qualified, därav kommer aldrig att korrigera object.
    // icke const kan convertas till const och fortsatt som om inget ändrats...
    Mint operator-() const {
        return Mint(-value);
    }
    Mint& operator--() {
        return *this -= 1; // this är Mint för vilket -= är definerat
    }
    Mint& operator++() {
        return *this += 1; // this är Mint för vilket -= är definerat
    }

    // före eller efter?
    Mint operator++(int) { Mint temp; temp.value = value++; return temp; }
    Mint operator--(int) { Mint temp; temp.value = value--; return temp; }

    // OBS! difference in order is significant
    // int + Mint != Mint + int ground level
    friend Mint operator+(Mint a, const Mint& b) { return a += b; } // implicit vänsta värdet sig själv
    friend Mint operator-(Mint a, const Mint& b) { return a -= b; }
    friend Mint operator*(Mint a, const Mint& b) { return a *= b; }
    friend Mint operator/(Mint a, const Mint& b) { return a /= b; }


    static long long choose(long long a, long long b) {

        if (b > a) return 0;
        if (a < 0 || b < 0) return 0;

        unsigned long long n = 1;
        for (int i = 1; i < a + 1; i++) {
            n *= i;
            n %= MOD;
        }

        // täljare 0?
        unsigned long long denom = 1;
        for (int i = 1; i < b + 1; i++) {
            denom *= i;
            denom %= MOD;
        }
        for (int i = 1; i < a - b + 1; i++) {
            denom *= i;
            denom %= MOD;
        }

        Mint x(n);
        Mint y(denom);
        return (x.value * (long long)y.getInverse()) % MOD;
    }

    long long getValue() {
        return value;
    }
};


/**
 * Computes the greatest common divisor (GCD) of two numbers a and b using the Euclidean Algorithm.
 *
 * @param a The first number for which the GCD is to be computed. Should be a non-negative integer.
 * @param b The second number for which the GCD is to be computed. Should be a non-negative integer.
 * @return The greatest common divisor of a and b.
 */
long long gcd(long long a, long long b) {
    if (b > a) {
        std::swap(a, b);
    }
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}


/**
 * Computes the greatest common divisor (GCD) of two numbers a and b using the Extended Euclidean Algorithm.
 * It also finds coefficients x and y such that ax + by = gcd(a, b).
 *
 * @param a The first number for which the GCD is to be computed.
 * @param b The second number for which the GCD is to be computed.
 * @param x A reference to a long long variable where the coefficient x will be stored.
 * @param y A reference to a long long variable where the coefficient y will be stored.
 * @return The greatest common divisor of a and b.
 */
long long gcdExtended(long long a, long long b, long long& x, long long& y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    long long x1, y1;
    long long gcd = gcdExtended(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return gcd;
}

/**
 * Computes the modular multiplicative inverse of x under modulo n using the Extended Euclidean Algorithm.
 * The modular inverse is an integer y such that (x * y) % n == 1.
 *
 * @param x The number for which the modular inverse is to be computed.
 * @param n The modulus.
 * @return The modular multiplicative inverse of x under modulo n. If the inverse does not exist, -1 is returned.
 */
long long modInverse(long long x, long long n) {
    long long inv, y;
    long long gcd = gcdExtended(x, n, inv, y);
    if (gcd != 1) {
        return -1;
    }
    else {
        return (inv % n + n) % n;
    }
}

int main() {
    cin.tie(0); ios_base::sync_with_stdio(0);

    long long n, t;
    while (cin >> n >> t && !(n == 0 && t == 0)) {
        char op; long long a, b;
        for (int i = 0; i < t; i++) {
            cin >> a >> op >> b;
            MOD = n;
            Mint aa(a); Mint bb(b);
            if (op == '+') {
                aa += bb;
                cout << (long long)aa << nl;
            }
            else if (op == '-') {
                aa -= bb;
                cout << (long long)aa << nl;
            }
            else if (op == '*') {
                aa *= bb;
                cout << (long long)aa << nl;
            }
            else {
                // bb coprime n check
                int rgcd = gcd(n, b);
                if (rgcd != 1) {
                    cout << -1 << nl;
                }
                else {
                    auto rr = modInverse(b, n);
                    bb = Mint(rr);
                    aa *= bb;
                    cout << (long long)aa << nl;
                }
            }
        }
    }

}

/*


*/

