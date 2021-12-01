#ifndef MINI_PAINT_H
# define MINI_PAINT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

typedef struct s_board
{
	char	**board;
	int		w;
	int		h;
	char	bc;
	char	type;
	float	xc;
	float	yc;
	float	r;
	char	c;
}	t_board;

#endif