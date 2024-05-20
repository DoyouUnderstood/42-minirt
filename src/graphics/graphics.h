/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:55:03 by erabbath          #+#    #+#             */
/*   Updated: 2024/05/20 12:00:49 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "color.h"
# include "../include/light.h"
# include "../include/mathematique.h"
# include "../include/pattern.h"
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

t_pattern						*stripe_pattern_create(t_color color1,
									t_color color2);
t_pattern						stripe_pattern(t_color a, t_color b);
t_color							stripe_at(const t_pattern *pattern,
									t_tuple point);
t_color							stripe_at_object(const t_pattern *pattern,
									const t_object *object, t_tuple point);

t_color							color_at(t_world *world, t_ray *ray,
									int remaining);
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