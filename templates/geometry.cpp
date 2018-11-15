struct point {
    double x,y;
};

// lines are segments
struct seg {
    point p1,p2;
    // both segments, line intersect
    pair<bool,point> intersect(struct seg &other);
    point projection(struct point p);
    point symmetric(struct point p);
    double dist(struct point p);
};

struct ngon {
    int n;
    point *pts;
    double area();
    struct ngon convex();
};
