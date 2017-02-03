alias P = Complex!(double);
alias Cir = Tuple!(P, double);

double norm(in P x) pure {
    return x.re*x.re+x.im*x.im;
}

double cross(in P x, in P y) pure {
    return (conj(x)*y).im;
}
