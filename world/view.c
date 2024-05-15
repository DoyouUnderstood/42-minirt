#include "../include/main.h"
#include "../include/mathematique.h"
#include "../include/shape.h"

// Fonction view_transform
t_matrix	view_transform(t_tuple from, t_tuple to, t_tuple up)
{
	t_tuple forward = vector_normalize(tuple_subtract(to, from));
	t_tuple upn = vector_normalize(up);
	t_tuple left = vector_cross(forward, upn);
	t_tuple true_up = vector_cross(left, forward);
	t_matrix trans = matrix_translation(-from.x, -from.y, -from.z);
	t_matrix orientation = matrix((float[4][4]){{left.x, left.y, left.z, 0.0f},
			{true_up.x, true_up.y, true_up.z, 0.0f}, {-forward.x, -forward.y,
			-forward.z, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}});

	return (matrix_multiply(orientation, trans));
}