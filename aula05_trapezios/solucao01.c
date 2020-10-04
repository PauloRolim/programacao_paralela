int main(void){

    int h; //altura do trapézio
    int n; //número de trapezios
    
    int a, b, n, area_total;

    h = (b-a/n);
    area_total = (f(a)+f(a+h)) * h/2;

    for (int i = 1; i < n; i++) {
        x_i = a+i*h;
        area_total += (f(x_i) + f(x_i+h)) * h/2;
    }
    
    return 0;
}