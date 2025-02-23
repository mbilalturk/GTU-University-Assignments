#include <stdio.h>
#include <math.h>
#define SIZE_1 3
#define SIZE_2 1

/* PART 1 */
typedef struct {
    double values[SIZE_1][SIZE_1];
    double determinant;
} matrix;

void print_matrix(matrix initial_matrix);
void inverse_matrix(matrix *initial_matrix, matrix*inverted_matrix);
void determinant_of_matrix(matrix initial_matrix);

/* PART 2 */
typedef struct {
    double values[SIZE_2][SIZE_2][SIZE_1];
    double angle;
} vector;

double find_orthogonal(vector vec_1, vector vec_2, vector *output_vec);

/* PART 3 */
typedef struct{
    double coefficient;
} third_order_polynomial;

void polynomial_get_integral(third_order_polynomial p1, third_order_polynomial p2, int a, int b);

int main(){
    /* PART 1 */
    matrix initial_matrix;
    matrix inverted_matrix;

    /* Assign values to matrix */
    initial_matrix.values[0][0] = 1.0000;
    initial_matrix.values[0][1] = 0.9134;
    initial_matrix.values[0][2] = 0.2785;
    initial_matrix.values[1][0] = 0.9058;
    initial_matrix.values[1][1] = 0.6324;
    initial_matrix.values[1][2] = 0.5469;
    initial_matrix.values[2][0] = 0.1270;
    initial_matrix.values[2][1] = 0.0975;
    initial_matrix.values[2][2] = 0.9575;

    inverse_matrix(&initial_matrix, &inverted_matrix);
    
    print_matrix(initial_matrix);  
    print_matrix(inverted_matrix);

    // /* PART 2 */
    vector A, B;
    vector output_vec;

    /* Initial values to matrix */
    A.values[0][0][0] = 1.000;
    A.values[0][0][1] = 2.000;
    A.values[0][0][2] = 3.000;

    B.values[0][0][0] = 0.500;
    B.values[0][0][1] = 1.500;
    B.values[0][0][2] = 2.500;

    find_orthogonal(A, B, &output_vec);

    printf("A: [%.3lf, %.3lf, %.3lf]\n", A.values[0][0][0], A.values[0][0][1], A.values[0][0][2]);
    printf("B: [%.3lf, %.3lf, %.3lf]\n", B.values[0][0][0], B.values[0][0][1], B.values[0][0][2]);
    printf("Angle: %.3lf\n", output_vec.angle);

    /* PART 3 */
    double a[2],b[2],c[2],d[2],x,y;
    int i;

    /* Take input from user */
    for(i=0; i<2; i++){
        printf("Enter two third-degree polynomial [ax^3+bx^2+cx+d]: \n");
        printf("a: ");
        scanf("%lf", &a[i]);
        printf("b: ");
        scanf("%lf", &b[i]);
        printf("c: ");
        scanf("%lf", &c[i]);
        printf("d: ");
        scanf("%lf", &d[i]);
    }

    printf("Enter range [x,y]: \n");
    printf("x: ");
    scanf("%lf", &x);
    printf("y: ");
    scanf("%lf", &y);

    /* Print polynomials */
    printf("First polynomial: %.0lfx^3+%.0lfx^2+%.0lfx+%.0lf \n", a[0], b[0], c[0], d[0]);
    printf("Second polynomial: %.0lfx^3+%.0lfx^2+%.0lfx+%.0lf \n", a[1], b[1], c[1], d[1]);
    printf("Range: [%.2lf,%.2lf]\n", x, y);

    return(0);
}

void print_matrix(matrix initial_matrix){
    int i, j;
    
    /* Print matrix */
    for(i = 0; i<SIZE_1; i++){
        for(j=0; j<SIZE_1; j++){
            printf("%.4lf   ", initial_matrix.values[i][j]);
        }
        printf("\n");
    }

    determinant_of_matrix(initial_matrix);
}

void inverse_matrix(matrix *initial_matrix, matrix *inverted_matrix){    
   /* Calculate inverse matrix */
    inverted_matrix->values[0][0] = initial_matrix->values[1][1]*initial_matrix->values[2][2]-initial_matrix->values[1][2]*initial_matrix->values[2][1];
    inverted_matrix->values[0][1] = -(initial_matrix->values[1][0]*initial_matrix->values[2][2]-initial_matrix->values[1][2]*initial_matrix->values[2][0]);
    inverted_matrix->values[0][2] = initial_matrix->values[1][0]*initial_matrix->values[2][1]-initial_matrix->values[1][1]*initial_matrix->values[2][0];
    inverted_matrix->values[1][0] = -(initial_matrix->values[0][1]*initial_matrix->values[2][2]-initial_matrix->values[0][2]*initial_matrix->values[2][1]);
    inverted_matrix->values[1][1] = initial_matrix->values[0][0]*initial_matrix->values[2][2]-initial_matrix->values[0][2]*initial_matrix->values[2][0];
    inverted_matrix->values[1][2] = initial_matrix->values[0][0]*initial_matrix->values[2][1]-initial_matrix->values[0][1]*initial_matrix->values[2][0];
    inverted_matrix->values[2][0] = initial_matrix->values[0][1]*initial_matrix->values[1][2]-initial_matrix->values[0][2]*initial_matrix->values[1][1];
    inverted_matrix->values[2][1] = -(initial_matrix->values[1][0]*initial_matrix->values[2][1]-initial_matrix->values[1][1]*initial_matrix->values[2][0]);
    inverted_matrix->values[2][2] = initial_matrix->values[0][0]*initial_matrix->values[1][1]-initial_matrix->values[0][1]*initial_matrix->values[1][0];

}

void determinant_of_matrix(matrix initial_matrix){
    double x,y,z;
    double determinant;
    
    x = initial_matrix.values[0][0]*((initial_matrix.values[1][1]*initial_matrix.values[2][2])-(initial_matrix.values[1][2]*initial_matrix.values[2][1]));
    y = initial_matrix.values[0][1]*((initial_matrix.values[1][0]*initial_matrix.values[2][2])-(initial_matrix.values[1][2]*initial_matrix.values[2][0]));
    z = initial_matrix.values[0][2]*((initial_matrix.values[1][0]*initial_matrix.values[2][1])-(initial_matrix.values[1][1]*initial_matrix.values[2][0]));

    initial_matrix.determinant = x-y+z;
    printf("Determinant: %.4lf\n\n", initial_matrix.determinant);
}

double find_orthogonal(vector vec_1, vector vec_2, vector *output_vec){
    double dot;
    double magnitude_1, magnitude_2;

    /* Calculate dot product and magtitude */
    dot = (vec_1.values[0][0][0]*vec_2.values[0][0][0])+(vec_1.values[0][0][1]*vec_2.values[0][0][1])+(vec_1.values[0][0][2]*vec_2.values[0][0][2]);
    magnitude_1 = sqrt((vec_1.values[0][0][0]*vec_1.values[0][0][0])+(vec_1.values[0][0][1]*vec_1.values[0][0][1])+(vec_1.values[0][0][2]*vec_1.values[0][0][2]));
    magnitude_2 = sqrt((vec_2.values[0][0][0]*vec_2.values[0][0][0])+(vec_2.values[0][0][1]*vec_2.values[0][0][1])+(vec_2.values[0][0][2]*vec_2.values[0][0][2]));

    output_vec->angle = acos(dot/(magnitude_1*magnitude_2));
}

void polynomial_get_integral(third_order_polynomial p1, third_order_polynomial p2, int a, int b){

}