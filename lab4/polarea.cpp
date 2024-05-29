/*
author: lowko527
about problem: Simple polygon area calculation with shoelace formula
time complexity: O(n) 
mem complexity: O(n)
usage instruction: provided is a class Point which represents pointsin the euclidiean plane. Further, function polygon area and getOrder are provided operating on arrs of point. 

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

class Point {
public:
    int x, y;

    // Constructor
    Point(int x_val = 0, int y_val = 0) : x(x_val), y(y_val) {}


    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }

    Point operator-(const Point& other) const {
        return Point(x - other.x, y - other.y);
    }

    // scaling
    Point operator*(int scalar) const {
        return Point(x * scalar, y * scalar);
    }

    // scaling
    Point operator/(int scalar) const {
        if (scalar != 0)
            return Point(x / scalar, y / scalar);
        else {
            std::cerr << "Division by zero!" << std::endl;
            return Point();
        }
    }

    int scalarProduct(const Point& other) const {
        return x * other.x + y * other.y;
    }

    int crossProduct(const Point& other) const {
        return x * other.y - y * other.x;
    }

    // Euclidean distance between two points
    double distance(const Point& other) const {
        int dx = x - other.x;
        int dy = y - other.y;
        return sqrt(dx * dx + dy * dy);
    }

    // Angle in radians
    double angle(const Point& other) const {
        double dot_prod = scalarProduct(other);
        double mag_product = sqrt(x * x + y * y) * sqrt(other.x * other.x + other.y * other.y);
        if (mag_product == 0) {
            // zero vector undefined , just give 0.0 bac
            return 0.0;
        }
        return acos(dot_prod / mag_product);
    }
};

// Calculate the area of a simple polygon formed by the given points using the shoelace formula
double polygonArea(const std::vector<Point>& points) {
    int n = points.size();
    double area = 0.0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        area += (points[i].x * points[j].y- points[j].x * points[i].y);
    }
    return std::abs(area) / 2.0;
}


/**
 * Determine the order (clockwise, counterclockwise, or collinear) of a set of points.
 *
 * @param points A vector of Point objects representing the vertices of the polygon.
 * @return The order of the points: Clockwise, Counterclockwise, or Collinear.
 *
 * This function calculates the sum of the cross-products of consecutive edges of the polygon formed by the given points.
 * If the sum is positive, the points are in counterclockwise order.
 * If the sum is negative, the points are in clockwise order.
 * If the sum is zero, the points are collinear.
 */
string getOrder(const std::vector<Point>& points) {
    int n = points.size();
    double sum = 0.0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        sum += points[i].crossProduct(points[j]);
    }
    if (sum > 0.0) {
        return "CCW";
    }
    else if (sum < 0.0) {
        return "CW";
    }
    else {
        return "Collinear";
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cout << fixed << setprecision(1);
    int n; 
    while (cin >> n && n!= 0) {

        vector<Point> a(n);
        for (int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            Point p(x,y);
            a[i] = p;
        }
        auto ar = polygonArea(a);
        auto di = getOrder(a);
        
        cout << di _ ar << nl;
    }
}

/*
1
151 783 57 278

7 35 3 18 33 26 6 2
17 12 19 20 21 22 18

*/
