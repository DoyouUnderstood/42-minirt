#include "../include/graphics.h"
#include <stdint.h>

// fonction pour ajouter des couleurs.
t_color color_add(t_color c1, t_color c2) 
{
    t_color result;

    result.r = c1.r + c2.r;
    result.g = c1.g + c2.g;
    result.b = c1.b + c2.b;

    return (result);
}

// Fonction pour la multiplication de deux couleurs normalisées
t_color color_multiply(t_color c1, t_color c2) 
{
    t_color result;
    result.r = c1.r * c2.r;
    result.g = c1.g * c2.g;
    result.b = c1.b * c2.b;

    return (result);
}

/// fonction alternative pour la multiplication de couleurs.
t_color color_multiply_alternativ(t_color c1, t_color c2) 
{
    t_color result;
    result.r = (c1.r / 255.0) * (c2.r / 255.0) * 255;
    result.g = (c1.g / 255.0) * (c2.g / 255.0) * 255;
    result.b = (c1.b / 255.0) * (c2.b / 255.0) * 255;
    return (result);
}

t_light *light_create(t_color color, t_tuple position)
{
    t_light *light; 

    light = malloc(sizeof(t_light));
    light->intensity = color;
    light->pos = position;
    return (light);
}

// Fonction pour multiplier une couleur par un scalaire.
t_color color_multiply_scalar(t_color c, double scalar) 
{
    t_color result;

    result.r = c.r * scalar;
    result.g = c.g * scalar;
    result.b = c.b * scalar;

    return (result);
}

// Convertit une couleur du format flottant (dans l'intervalle [0,1] pour chaque composante) vers un format RGB entier sur 3 octets.
uint32_t color_to_rgb(float red, float green, float blue) 
{
    red = fmax(0, fmin(red, 1));
    green = fmax(0, fmin(green, 1));
    blue = fmax(0, fmin(blue, 1));

    uint8_t r = (uint8_t)(red * 255);
    uint8_t g = (uint8_t)(green * 255);
    uint8_t b = (uint8_t)(blue * 255);

    return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}

#include <math.h>

#define COLOR_EPSILON 0.0001

// Fonction pour comparer deux couleurs avec une certaine tolérance
bool color_eq(t_color c1, t_color c2) {
    return fabs(c1.r - c2.r) < COLOR_EPSILON &&
           fabs(c1.g - c2.g) < COLOR_EPSILON &&
           fabs(c1.b - c2.b) < COLOR_EPSILON;
}


// Fonction pour créer une couleur
t_color color_create(double r, double g, double b) {
    t_color new_color;
    new_color.r = r;
    new_color.g = g;
    new_color.b = b;
    return new_color;
}
