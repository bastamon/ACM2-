#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>
#include <cassert>
using namespace std;

#define maxn 10000 
#define INF 0x7FFFFFFF
#define MAX_YNODE maxn * 50 
#define MAX_XNODE maxn * 4

struct Point {
    int x, y, z;
    Point(int xx = 0, int yy = 0, int zz = 0) : 
        x(xx), y(yy), z(zz) {}
}px[maxn], py[maxn], pz[maxn];

int n;

bool cmp_x(const Point &a, const Point &b) {
    if (a.x != b.x) return a.x < b.x;
    if (a.y != b.y) return a.y < b.y;
    return a.z < b.z;
}
bool cmp_y(const Point &a, const Point &b) {
    if (a.y != b.y) return a.y < b.y;
    if (a.z != b.z) return a.z < b.z;
    return a.x < b.x;
}
bool cmp_z(const Point &a, const Point &b) {
    if (a.z != b.z) return a.z < b.z;
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

struct YNode {
    int left, right;
    YNode *left_child, *right_child;
    vector<int>points;

    void build(const vector<Point*>&p, int l, int r);
    bool query(int y1, int z1, int y2, int z2);

} ynodes[MAX_YNODE];
int ynode_count;

struct XNode {
    int left, right;
    XNode *left_child, *right_child;
    vector<Point*>points;
    YNode *brother;

    void build(Point p[], int l, int r);
    bool query(int x1, int y1, int z1, int x2, int y2, int z2);

}*root, xnodes[MAX_XNODE];
int xnode_count;

struct Determinator {
    int x1, x2;
    int y1, y2;
    int z1, z2;

    Determinator(int xx1 = 0, int xx2 = 0, int yy1 = 0, int yy2 = 0, int zz1 = 0, int zz2 = 0) :
        x1(xx1), x2(xx2), y1(yy1), y2(yy2), z1(zz1), z2(zz2) {}

    void update(const Determinator &rhs) {
        x1 = min(x1, rhs.x1);
        x2 = max(x2, rhs.x2);
        y1 = min(y1, rhs.y1);
        y2 = max(y2, rhs.y2);
        z1 = min(z1, rhs.z1);
        z2 = max(z2, rhs.z2);
    }
    void update(const Point &p) {
        x1 = min(x1, p.x);
        x2 = max(x2, p.x);
        y1 = min(y1, p.y);
        y2 = max(y2, p.y);
        z1 = min(z1, p.z);
        z2 = max(z2, p.z);
    }
};
Determinator smaller_x[maxn], larger_x[maxn];
Determinator smaller_y[maxn], larger_y[maxn];
Determinator smaller_z[maxn], larger_z[maxn];

void initialize(Point p[], Determinator smaller[], Determinator larger[]) {
    smaller[0] = Determinator(p[0].x, p[0].x, p[0].y, p[0].y, p[0].z, p[0].z);     
    for (int i = 1; i < n; ++i) {
        smaller[i] = smaller[i - 1];
        smaller[i].update(p[i]);
    }

    larger[n - 1] = Determinator(p[n - 1].x, p[n - 1].x, p[n - 1].y, 
            p[n - 1].y, p[n - 1].z, p[n - 1].z);
    for (int i = n - 2; i >= 0; --i) {
        larger[i] = larger[i + 1];
        larger[i].update(p[i]);
    }
}

Determinator get_determinator(const vector<Determinator> &candidates) {
    Determinator ret = candidates[0];
    for (int i = 1; i < candidates.size(); ++i) {
        ret.update(candidates[i]);
    }
    return ret;
}

//length is half of the length of the cubic
bool is_valid(int length) {
    for (int i = 0; i < n; ++i) {
        Point x1(px[i].x - length, -INF, -INF);
        Point x2(px[i].x + length, INF, INF);
        Point y1(-INF, px[i].y - length, -INF);
        Point y2(INF, px[i].y + length, INF);
        Point z1(-INF, -INF, px[i].z - length);
        Point z2(INF, INF, px[i].z + length);

        vector<Determinator>candidates;

        int ix1 = lower_bound(px, px + n, x1, cmp_x) - px - 1;
        if (ix1 >= 0) candidates.push_back(smaller_x[ix1]);
        int ix2 = upper_bound(px, px + n, x2, cmp_x) - px;
        if (ix2 < n) candidates.push_back(larger_x[ix2]);

        int iy1 = lower_bound(py, py + n, y1, cmp_y) - py - 1;
        if (iy1 >= 0) candidates.push_back(smaller_y[iy1]);
        int iy2 = upper_bound(py, py + n, y2, cmp_y) - py;
        if (iy2 < n) candidates.push_back(larger_y[iy2]);

        int iz1 = lower_bound(pz, pz + n, z1, cmp_z) - pz - 1;
        if (iz1 >= 0) candidates.push_back(smaller_z[iz1]);
        int iz2 = upper_bound(pz, pz + n, z2, cmp_z) - pz;
        if (iz2 < n) candidates.push_back(larger_z[iz2]);

        if (candidates.empty()) {
            return true;
        }

        Determinator determinator = get_determinator(candidates);

        int qx1 = determinator.x2 - length;
        int qx2 = determinator.x1 + length;
        int qy1 = determinator.y2 - length;
        int qy2 = determinator.y1 + length;
        int qz1 = determinator.z2 - length;
        int qz2 = determinator.z1 + length;
        if (qx1 <= qx2 && qy1 <= qy2 && qz1 <= qz2 && 
                root->query(qx1, qy1, qz1, qx2, qy2, qz2)) {
            return true;
        }
    }
    return false;
}

int main() {
	freopen("zhugeliang.in", "r", stdin);
	freopen("zhugeliang.out", "w", stdout);
    int start_time = clock();
    int t;
    scanf("%d", &t);
    assert(0 < t && t <= 15);
    while (t--) {
        scanf("%d", &n);
        assert(0 < n && n <= 10000);
        int leftmost = INF, rightmost = -INF;
        int bottom = INF, top = -INF;
        int back = INF, front = -INF;
        for (int i = 0; i < n; ++i) {
            scanf("%d%d%d", &px[i].x, &px[i].y, &px[i].z);
            assert(abs(px[i].x) <= 100000);
            assert(abs(px[i].y) <= 100000);
            assert(abs(px[i].z) <= 100000);
            pz[i] = py[i] = px[i];
            leftmost = min(leftmost, px[i].x);
            rightmost = max(rightmost, px[i].x);
            bottom = min(bottom, px[i].y);
            top = max(top, px[i].y);
            back = min(back, px[i].z);
            front = max(front, px[i].z);
        }
        sort(px, px + n, cmp_x);
        sort(py, py + n, cmp_y);
        sort(pz, pz + n, cmp_z);
        initialize(px, smaller_x, larger_x);
        initialize(py, smaller_y, larger_y);
        initialize(pz, smaller_z, larger_z);

        xnode_count = 0;
        ynode_count = 0;
        root = &xnodes[xnode_count++];
        root->build(px, 0, n - 1);

        int low = 0, high = max(top - bottom, max(rightmost - leftmost,
                    front - back)), ans; 
        while (low <= high) {
            int mid = (low + high) >> 1;
            if (is_valid(mid)) {
                high = mid - 1;
                ans = mid;
            } else {
                low = mid + 1;
            }
        }
        cout << (long long)ans * ans * ans * 8 << endl;
    }
    fprintf(stderr, "time: %d\n", clock() - start_time);
}
void YNode::build(const vector<Point*>&p, int l, int r) {
    points.clear();
    left = p[l]->y, right = p[r]->y;
    if (left == right) {
        left_child = right_child = NULL;
        for (int i = l; i <= r; ++i) {
            points.push_back(p[i]->z);
        }
        return;
    }
    int m = (l + r) >> 1;
    left_child = &ynodes[ynode_count++];
    right_child = &ynodes[ynode_count++];
    left_child->build(p, l, m);
    right_child->build(p, m + 1, r);

    for (int i = 0, j = 0; i < left_child->points.size() || 
            j < right_child->points.size();) {
        if (i < left_child->points.size() && (j >= right_child->points.size() || 
                    left_child->points[i] < right_child->points[j])) {
            points.push_back(left_child->points[i++]);
        } else {
            points.push_back(right_child->points[j++]);
        }
    }
}
bool YNode::query(int y1, int z1, int y2, int z2) {
    if (y2 < left || y1 > right) {
        return false;
    }
    if (y1 <= left && right <= y2) {
        int a = lower_bound(points.begin(), points.end(), z1) - points.begin();
        int b = upper_bound(points.begin(), points.end(), z2) - points.begin();
        return b != a;
    }
    if (left_child->query(y1, z1, y2, z2)) return true;
    else return right_child->query(y1, z1, y2, z2);
}
void XNode::build(Point p[], int l, int r) {
    points.clear();
    left = p[l].x, right = p[r].x;
    if (left == right) {
        left_child = right_child = NULL;
        for (int i = l; i <= r; ++i) { 
            points.push_back(&p[i]);
        }
        brother = &ynodes[ynode_count++];
        brother->build(points, 0, points.size() - 1);
        return;
    }
    int m = (l + r) >> 1;
    left_child = &xnodes[xnode_count++];
    right_child = &xnodes[xnode_count++];
    left_child->build(p, l, m);
    right_child->build(p, m + 1, r);

    for (int i = 0, j = 0; i < left_child->points.size() || 
            j < right_child->points.size();) {
        if (i < left_child->points.size() && (j >= right_child->points.size() || 
                    cmp_y(*(left_child->points[i]), *(right_child->points[j])))) {
            points.push_back(left_child->points[i++]);
        } else {
            points.push_back(right_child->points[j++]);
        }
    }
    brother = &ynodes[ynode_count++];
    brother->build(points, 0, points.size() - 1);
}
bool XNode::query(int x1, int y1, int z1, int x2, int y2, int z2) {
    if (x2 < left || x1 > right) {
        return false;
    }
    if (x1 <= left && right <= x2) {
        return brother->query(y1, z1, y2, z2);
    }
    if (left_child->query(x1, y1, z1, x2, y2, z2)) return true;
    else return right_child->query(x1, y1, z1, x2, y2, z2);
}
