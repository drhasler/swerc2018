#define db double
#define pt struct point
#define seg struct segment

pt {
    db x,y;
    point() {}
    point(db x,db y) { this->x = x; this->y = y; }
    point operator+(const point& other) const { return point(x+other.x,y+other.y); }
    point operator-(const point& other) const { return point(x-other.x,y-other.y); }
    point operator*(const db& k) const { return point(k*x,k*y); }
};

// inlining ???
db cross(const pt& p1,const pt& p2) { return p1.x*p2.y-p1.y*p2.x; }
db  dot (const pt& p1,const pt& p2) { return p1.x*p2.x+p1.y*p2.y; }

// line is a seg
seg {
    // seg contains pts from a to a+d
	pt a,d;
    segment() {}
    // segment by endpoints
    segment(db x1,db y1,db x2,db y2) : a(x1,y1), d(x2-x1,y2-y1) {}
};

pt intersect(const seg& s1,const seg& s2) {
    // if parallel -> div by 0 error
    // assert(cross(s1.d,s2.d))
    return s1.a + s1.d * (cross(s2.a-s1.a,s2.d)/cross(s1.d,s2.d));
}

// p is a point of the line
bool inseg(const seg& s,const pt& p) { return dot(p-s.a,s.d)>=0 && dot(p-s.a-s.d,s.d)<=0; }

pt projection(seg& s,pt& p) {
    seg orth;
    orth.a = p;
    orth.d = point(-s.d.y,s.d.x);
    return intersect(s,orth);
}

// true if p1 p2 in counter clockwise
bool turn0(const pt& p1,const pt& p2) { return cross(p1,p2)>0; }
struct turn {
    pt center;
    turn(pt& p) { center = p; }
    bool operator() (pt& p1,pt& p2) { return cross(p1-center,p2-center)>0; }
};

struct ngon {
    int n;
    pt* pts; // in counter clockwise order
    ngon(int n,pt* pts) { this->n=n; this->pts=pts; }
    db area() {
        db ans = 0;
        for (int i=1;i<n-1;i++) ans += cross(pts[i]-pts[0],pts[i+1]-pts[0]);
        return ans/2;
    }
    void convexify() { // output is counter clockwise
        for (int i=1;i<n;i++) if (pts[i]<pts[0]) swap(pts[i],pts[0]);
        sort(pts+1,pts+n,turn(pts[0]));
        int cnt=0;
        for (int i=2;i<n;i++) {
            while (cnt>=0 && turn0(pts[i]-pts[cnt],pts[cnt+1]-pts[cnt])) cnt--;
            cnt++; swap(pts[i],pts[cnt+1]);
        }
        while (cnt>=0 && turn0(pts[0]-pts[cnt],pts[cnt+1]-pts[cnt])) cnt--;
        n = cnt+2;
    }
};
