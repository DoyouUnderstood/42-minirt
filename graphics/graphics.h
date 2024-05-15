/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltd <ltd@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:55:03 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/15 17:45:01 by ltd              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "../include/light.h"
# include "../include/mathematique.h"
# include "../include/pattern.h"
# include "../include/types.h"
# include <stdint.h>

typedef struct s_object			t_object;
typedef struct s_intersection	t_intersection;
typedef struct s_ray			t_ray;
typedef struct s_world			t_world;

typedef struct s_specular_params
{
	t_tuple						lightv;
	t_tuple						normalv;
	t_tuple						eyev;
	const t_material			*material;
	const t_light				*light;
}								t_specular_params;

// ===== PATTERN =====

t_pattern						*checker_pattern_create(t_color color1,
									t_color color2);

t_pattern						*ring_pattern_create(t_color color1,
									t_color color2);
t_color							ring_at(const t_pattern *pattern,
									t_tuple point);

t_pattern						*gradient_pattern_create(t_color color1,
									t_color color2);
t_color							gradient_at(const t_pattern *pattern,
									t_tuple point);

void							set_pattern_transform(t_pattern *pattern,
									t_matrix transform);
t_pattern						*stripe_pattern_create(t_color color1,
									t_color color2);
t_pattern						stripe_pattern(t_color a, t_color b);
t_color							stripe_at(const t_pattern *pattern,
									t_tuple point);
t_color							stripe_at_object(const t_pattern *pattern,
									const t_object *object, t_tuple point);

t_color							convert_color_255_to_1(int r, int g, int b);
t_color							color_create(double r, double g, double b);
bool							color_eq(t_color c1, t_color c2);
t_color							color_at(t_world *world, t_ray *ray,
									int remaining);
t_color							color_add(t_color c1, t_color c2);
t_color							color_multiply(t_color c1, t_color c2);
t_color							color_multiply_alternativ(t_color c1,
									t_color c2);
t_color							color_multiply_scalar(t_color c, double scalar);
uint32_t						color_to_rgb(float red, float green,
									float blue);
t_light							*light_create(t_color color, t_tuple position,
									double diffuse);
t_color							calculate_color(t_intersection *closest_hit,
									t_ray *ray, t_light *light);
t_material						*material_create_default(t_color *color,
									double reflectiv, t_pattern *pattern);

typedef struct s_lighting
{
	t_material					*material;
	t_object					*object;
	t_light						*light;
	t_tuple						*position;
	t_tuple						*eyev;
	t_tuple						*normalv;
	bool						in_shadow;
}								t_lighting;

t_color							calculate_ef_c(const t_lighting *params);
t_color							calculate_ambient(t_color ef_c,
									double ambient_intensity);
t_color							calculate_diffuse(t_color ef_c,
									double light_dot_normal, double intensity);
t_color							calculate_specular(t_specular_params *params);
t_specular_params				prepare_specular_params(t_lighting *params,
									t_tuple lightv);
t_color							lighting(t_lighting *params);
t_object						*parse_cylinder(char **parts, t_object *obj);
t_pattern						*set_pattern(char *part1, char *part2,
									char *part3);
t_object						*parse_cube(char **parts);
#endif