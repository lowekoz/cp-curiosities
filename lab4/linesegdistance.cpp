/*
author: lowko527
about problem: Calculates the minimal distance between two line segments (case work impl. with helper functions)
time complexity: O(1) 
mem complexity: O(1)
usage instruction: provided is a function minDistanceLineSegToLineSeg that take two line segments and calculates min distance.

Additional Desc.
"Is this in 2 dimensions? If so, the answer is simply the shortest of the
distance between point A and line segment CD, B and CD, C and AB or D and AB.
So it's a fairly simple "distance between point and line" calculation"
(if the distances are all the same, then the lines are parallel).

Templated GFG Base -
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

template<typename T>
bool onSegment(const pair<T, T>& p, const pair<T, T>& q, const pair<T, T>& r) {
    return (q.first <= std::max(p.first, r.first) && q.first >= std::min(p.first, r.first) &&
        q.second <= std::max(p.second, r.second) && q.second >= std::min(p.second, r.second));
}

template<typename T>
bool doSegmentsIntersect(const pair<T, T>& p1, const pair<T, T>& p2, const pair<T, T>& q1, const pair<T, T>& q2) {
    // Orientation function to find the orientation of triplet (p, q, r)
    // Returns 0 if colinear, 1 if clockwise, and -1 if counterclockwise
    auto orientation = [](const pair<T, T>& p, const pair<T, T>& q, const pair<T, T>& r) {
        T val = (q.second - p.second) * (r.first - q.first) - (q.first - p.first) * (r.second - q.second);
        return (val == 0) ? 0 : (val > 0) ? 1 : -1;
    };

    // Check if the orientations of the four endpoints are different
    int o1 = orientation(p1, p2, q1);
    int o2 = orientation(p1, p2, q2);
    int o3 = orientation(q1, q2, p1);
    int o4 = orientation(q1, q2, p2);

    if ((o1 != o2) && (o3 != o4)) {
        // Segments intersect
        return true;
    }

    // Special cases for colinear segments
    if ((o1 == 0) && onSegment(p1, q1, p2)) return true;
    if ((o2 == 0) && onSegment(p1, q2, p2)) return true;
    if ((o3 == 0) && onSegment(q1, p1, q2)) return true;
    if ((o4 == 0) && onSegment(q1, p2, q2)) return true;

    return false;
}

template<class T>
long double edist(pair<T, T>& p1, pair<T, T>& p2) {
    return sqrt(pow((p1.first - p2.first), 2) + pow((p1.second - p2.second), 2));
}

template<class T>
long double minDistanceLineSegToPoint(pair<T, T> A, pair<T, T> B, pair<T, T> E)
{

    // vector AB
    pair<T, T> AB;
    AB.first = B.first - A.first;
    AB.second = B.second - A.second;

    // vector BP
    pair<T, T> BE;
    BE.first = E.first - B.first;
    BE.second = E.second - B.second;

    // vector AP
    pair<T, T> AE;
    AE.first = E.first - A.first,
        AE.second = E.second - A.second;

    // Variables to store dot product
    long double AB_BE, AB_AE;

    // Calculating the dot product
    AB_BE = (AB.first * BE.first + AB.second * BE.second);
    AB_AE = (AB.first * AE.first + AB.second * AE.second);

    // Minimum distance from
    // point E to the line segment
    long double reqAns = 0;

    // BE is directed same direction as AB => point B is closest
    if (AB_BE > 0) {

        // Finding the magnitude
        long double y = E.second - B.second;
        long double x = E.first - B.first;
        reqAns = sqrt(x * x + y * y);
    }

    // AB and AE are different directions => point A is closest
    else if (AB_AE < 0) {
        long double y = E.second - A.second;
        long double x = E.first - A.first;
        reqAns = sqrt(x * x + y * y);
    }

    // Case E is within perpendicular range
    else {

        // Finding the perpendicular distance
        long double x1 = AB.first;
        long double y1 = AB.second;
        long double x2 = AE.first;
        long double y2 = AE.second;
        long double mod = sqrt(x1 * x1 + y1 * y1);

        if (mod == 0) {
            // Do know they are not collinear already case 1 1 1 1 1 2 1 2
            if (A == B) {
                return edist(A, E);
            }
        }

        reqAns = abs(x1 * y2 - y1 * x2) / mod;
    }
    return reqAns;
}

/**
 * Calculate the minimum distance between two line segments.
 *
 * @param p1 The first endpoint of the first line segment.
 * @param p2 The second endpoint of the first line segment.
 * @param q1 The first endpoint of the second line segment.
 * @param q2 The second endpoint of the second line segment.
 * @return The minimum distance between the two line segments.
 */
template<class T>
long double minDistanceLineSegToLineSeg(const pair<T, T>& p1, const pair<T, T>& p2, const pair<T, T>& q1, const pair<T, T>& q2) {
    if (doSegmentsIntersect(p1, p2, q1, q2)) {
        return 0;
    }

    long double ans = minDistanceLineSegToPoint(p1, p2, q1);
    ans = min(ans, minDistanceLineSegToPoint(p1, p2, q2));
    ans = min(ans, minDistanceLineSegToPoint(q1, q2, p1));
    ans = min(ans, minDistanceLineSegToPoint(q1, q2, p2));

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cout << fixed << setprecision(2);
    int n; cin >> n;
    pair<int, int> a, b, a2, b2;
    while (n--) {
        cin >> a.first >> a.second;
        cin >> b.first >> b.second;
        cin >> a2.first >> a2.second;
        cin >> b2.first >> b2.second;

        long double ans = minDistanceLineSegToLineSeg(a, b, a2, b2);
        cout << ans << nl;
    }
}
