struct Vis {
    struct Col {
        int r, g, b;
    };
    FILE* fp;
    D off, f;
    Vis(string s, D d, D u) : off(d), f(1000 / (u - d)) {
        fp = fopen(s.c_str(), "w");
        fprintf(
                fp,
                "<html><head><script>"
                "onload = function draw() {"
                "var cv = document.getElementById('c');"
                "var ct = cv.getContext('2d');");
    }
    D norm(D x) { return (x - off) * f; }
    void set_col(Col c) {
        fprintf(fp, "ct.fillStyle = \"rgb(%d, %d, %d)\";", c.r, c.g, c.b);
        fprintf(fp, "ct.strokeStyle = \"rgb(%d, %d, %d)\";", c.r, c.g, c.b);
    }
    void line(L l, Col col = {0, 0, 0}) {
        set_col(col);
        fprintf(fp,
                "ct.beginPath();"
                "ct.moveTo(%Lf, %Lf);"
                "ct.lineTo(%Lf, %Lf);"
                "ct.closePath();"
                "ct.stroke();",
                norm(l.s.x), norm(l.s.y), norm(l.t.x), norm(l.t.y));
    }
    void point(P p, Col col = {0, 0, 0}) {
        set_col(col);
        fprintf(fp,
                "ct.beginPath();"
                "ct.arc(%Lf, %Lf, 2, 0, Math.PI * 2, true);"
                "ct.fill();",
                norm(p.x), norm(p.y));
    }
    ~Vis() {
        fprintf(fp,
                "}</script></head><body>"
                "<canvas id=\"c\" width=\"1000\" height=\"1000\">"
                "</canvas></body></html>");
        fclose(fp);
    }
};
