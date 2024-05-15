#include "../include/main.h"
#include "../include/mathematique.h"
#include "../include/shape.h"

// Fonction view_transform
t_matrix	compute_orientation(t_tuple forward, t_tuple upn, t_tuple from)
{
	t_tuple		left;
	t_tuple		true_up;
	t_matrix	trans;
	t_matrix	orientation;

	left = vector_cross(forward, upn);
	true_up = vector_cross(left, forward);
	trans = matrix_translation(-from.x, -from.y, -from.z);
	orientation = matrix((float[4][4]){{left.x, left.y, left.z, 0.0f},
			{true_up.x, true_up.y, true_up.z, 0.0f}, {-forward.x, -forward.y,
			-forward.z, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}});
	return (matrix_multiply(orientation, trans));
}

t_matrix	view_transform(t_tuple from, t_tuple to, t_tuple up)
{
	t_tuple	forward;
	t_tuple	upn;

	forward = vector_normalize(tuple_subtract(to, from));
	upn = vector_normalize(up);
	return (compute_orientation(forward, upn, from));
}
