/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gfx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 22:13:45 by kyork             #+#    #+#             */
/*   Updated: 2016/11/15 22:53:44 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GFX_H
# define FT_GFX_H

# define RGB_TO_MLX(r,g,b) ((b << 16) | (g << 8) | (r << 0))

typedef float		t_mat[4][4];
typedef float		t_vec2[2];
typedef float		t_vec3[3];

typedef struct		s_img {
	void			*mlx_img;
	char			*buf;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	int				num_lines;
}					t_img;

# define VEC_X 0
# define VEC_Y 1
# define VEC_Z 2

void				ft_mat_bzero(t_mat m);
void				ft_mat_id(t_mat m);
void				ft_mat_mul(t_mat a, t_mat b, t_mat out);
void				ft_mat_vecmul(t_mat m, t_vec3 src, t_vec3 dst);
void				ft_mat_translate(t_mat m, t_vec3 offset);
void				ft_mat_rotate(t_mat m, float theta, float phi, float psi);
void				ft_mat_scale(t_mat m, t_vec3 factors);

t_vec2				*ft_vec_new2(float x, float y);
t_vec3				*ft_vec_new3(float x, float y);

t_img				*ft_img_new(void *mlx, int width, int height);
void				ft_grid_downsample(t_img *out, t_img *in, int factor);

#endif
