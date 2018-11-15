#define db double
#define pt struct point
#define seg struct segment

pt {
    db x,y;
    point() {}
    point(db x,db y) { this->x = x; this->y = y; }
    point operator+(const point& other) const { return point(this->x+other.x,this->y+other.y); }
    point operator-(const point& other) const { return point(this->x-other.x,this->y-other.y); }
    point operator*(const db& x) const { return point(this->x*x,this->y*y); }
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
