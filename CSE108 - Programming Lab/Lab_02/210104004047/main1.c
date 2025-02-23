#include <stdio.h>
#include <math.h>

#define PI 3.14

int main(){

    int lenght, width, height, radius;
    float surface_area, volume, slant_height;

    /* Getting lenght from user */
    printf("----------- PART 1 -----------\n\n");
    printf("Enter the edge lenght for cube: ");
    scanf("%d", &lenght);

    /* Calculating area and volume by using given formula */
    surface_area = 6 * lenght * lenght;
    volume = lenght * lenght * lenght;

    printf("Surface Area = %.2f, Volume = %.2f\n", surface_area, volume);
    printf("\n");

    /* Getting lenght, width, height from user */
    printf("Enter side lenght for rectengular prism: ");
    scanf("%d", &lenght);  

    printf("Enter side width: ");
    scanf("%d", &width);

    printf("Enter side height: ");
    scanf("%d", &height);

    /* Calculating area and volume by using given formula */
    surface_area = 2 * (lenght * width + lenght * height + width * height);
    volume = lenght * width * height;

    printf("Surface Area = %.2f, Volume = %.2f\n", surface_area, volume);
    printf("\n");

    /* Getting radius from user */
    printf("Enter the radius for sphere: ");
    scanf("%d", &radius);

    /* Calculating area and volume by using given formula */
    surface_area = 4 * PI * radius * radius;
    volume = PI * radius * radius * radius * 4 / 3;

    printf("Surface Area = %.2f, Volume = %.2f\n", surface_area, volume);
    printf("\n");

    /* Getting radius and height from user */
    printf("Enter the radius for cone: ");
    scanf("%d", &radius);

    printf("Enter the height: ");
    scanf("%d", &height);   

    /* Calculating area and volume by using given formula */
    slant_height = sqrt((radius * radius) + (height * height));
    surface_area = PI * radius * (slant_height + radius);
    volume = PI * radius * radius * height / 3;

    printf("Surface Area = %.2f, Volume = %.2f\n", surface_area, volume); 
    printf("\n\n");

    return (0);
}