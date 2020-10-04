//Área Total = h[y0/2 + y1 + y2 + y3 + ... + yn-1 + yn/2]

int main(void){

    int h; //altura do trapezio
    int a, b; //ponto inicial e final, respectivamente
    int n; //quantidade de trapézios
    int area_total;

    h = (b-a/n);
    area_total = (f(a)+f(b))/2;

    for (int i = 1; i < n; i++)
    {
        x_i = a+i*h;
        area_total += f(x_i);
    }
    area_total = h*area_total;

    return 0;
}