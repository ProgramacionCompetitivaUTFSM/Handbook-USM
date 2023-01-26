// Recuerda que si quieres sumar varias areas factoriza 1/2
// Para numeros enteros, solo hay que cambiar el tipo de dato
double area(const vector<Point>& fig) {
    double res = 0;
    for (unsigned i = 0; i < fig.size(); i++) {
        Point p = i ? fig[i - 1] : fig.back();
        Point q = fig[i];
        res += (p.x - q.x) * (p.y + q.y);
    }
    return fabs(res) / 2;
}