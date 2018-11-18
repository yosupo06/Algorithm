/**
Convex Hull Trick
Params:
    T = value type
    queryType = if queries are increase, use CHMode.incr.
                if queries are decrease, use CHMode.decr.
 */
template<class T>
struct ConvexHull {
    using L = array<T, 2>;
    static T value(L l, T x) { return l[0]*x + l[1]; }

    bool que_incr;
    ConvexHull(bool _que_incr) : que_incr(_que_incr) {}

    deque<L> lines;
    // can remove mid?
    static bool is_need(L mid, L left, L right) {
        assert(left[0] <= mid[0] && mid[0] <= right[0]);
        return (right[0]-mid[0])*(left[1]-mid[1]) < (mid[0]-left[0])*(mid[1]-right[1]);
    }

    void insert_front(L l) {
        if (lines.empty()) {
            lines.push_front(l);
            return;
        }
        assert(l[0] <= lines[0][0]);
        if (l[0] == lines[0][0]) {
            if (l[1] <= lines[0][1]) return;
            lines.pop_front();
        }
        while (lines.size() >= 2 && !is_need(lines.front(), l, lines[1])) {
            lines.pop_front();
        }
        lines.push_front(l);
    }
    void insert_back(L l) {
        if (lines.empty()) {
            lines.push_back(l);
            return;
        }
        assert(lines.back()[0] <= l[0]);
        if (lines.back()[0] == l[0]) {
            if (l[1] <= lines.back()[1]) return;
            lines.pop_back();
        }
        while (lines.size() >= 2 && !is_need(lines.back(), lines[lines.size()-2], l)) {
            lines.pop_back();
        }
        lines.push_back(l);
    }
    /**
    Insert line
    line's degree must be minimum or maximum
     */
    void insert_line(L line) {
        if (lines.empty()) {
            lines.push_back(line);
            return;
        }
        if (line[0] <= lines[0][0]) insert_front(line);
        else if (lines.back()[0] <= line[0]) insert_back(line);
        else assert(false); //line's degree must be minimum or maximum
    }
    /// get maximum y
    long max_y(T x) {
        assert(lines.size());
        if (que_incr) {
            while (lines.size() >= 2 &&
                   value(lines[0], x) <= value(lines[1], x)) {
                lines.pop_front();
            }
            return value(lines.front(), x);
        } else {
            while (lines.size() >= 2 &&
                   value(lines[lines.size()-2], x) >= value(lines.back(), x)) {
                lines.pop_back();
            }
            return value(lines.back(), x);
        }
    }
};
