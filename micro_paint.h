#ifndef MICRO_PAINT_H
# define MICRO_PAINT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

typedef struct s_board
{
	char	**board;
	int		w;
	int		h;
	char	bc;
	char	type;
	float	xi;
	float	yi;
	float	rw;
	float	rh;
	char	c;
}	t_board;

#endif