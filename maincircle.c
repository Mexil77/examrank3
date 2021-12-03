#include "mini_paint.h"

void	ft_freeall(t_board *b)
{
	size_t	i;

	if (b->board)
	{
		i = -1;
		while (b->board[++i])
			free (b->board[i]);
		free (b->board);
	}
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_error(char *err, t_board *b, FILE *fd)
{
	if (fd)
		fclose(fd);
	write(1,err,ft_strlen(err));
	ft_freeall(b);
	return (1);
}

int	ft_fillboard(t_board *b)
{
	int	i;
	int	j;

	b->board = malloc(sizeof(char *) * (b->h + 1));
	if (!b->board)
		return (1);
	b->board[b->h] = NULL;
	i = -1;
	while (++i < b->h)
	{
		b->board[i] = malloc(sizeof(char) * (b->w + 1));
		if (!b->board[i])
			return (1);
		b->board[i][b->w] = '\0';
	}
	i = -1;
	while (++i < b->h)
	{
		j = -1;
		while (++j < b->w)
			b->board[i][j] = b->bc;
	}
	return (0);
}

float	ft_distance(t_board *b, float x, float y)
{
	return (sqrtf(powf(b->xc - x, 2) + powf(b->yc - y, 2)));
}

void	ft_printcircle(t_board *b)
{
	int	i;
	int	j;

	i = -1;
	while (b->board[++i])
	{
		j = -1;
		while (b->board[i][++j])
		{
			if (b->type == 'C' && ft_distance(b, j, i) <= b->r)
				b->board[i][j] = b->c;
			if (b->type == 'c' && ft_distance(b, j, i) <= b->r && ft_distance(b, j, i) > b->r - 1)
				b->board[i][j] = b->c;
		}
	}
}

int	ft_paint(t_board *b, FILE *fd)
{
	int	ret;
	int	scan;

	ret = 0;
	while ((scan = fscanf(fd, "%c %f %f %f %c\n", &b->type, &b->xc, &b->yc, &b->r, &b->c)) == 5)
	{
		if ((b->type != 'c' && b->type != 'C') || b->r <= 0)
			ret = 1;
		else
			ft_printcircle(b);
	}
	if (scan > 0)
		ret = 1;
	return (ret);
}

void	ft_printdraw(t_board *b)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (b->board[++i])
	{
		j = -1;
		while (b->board[i][++j])
			write(1, &b->board[i][j], 1);
		write(1, "\n", 1);
	}
}

int	main(int argc, char **argv)
{
	FILE	*fd;
	t_board	board;

	board.board = NULL;
	if (argc < 2 || argc > 2)
		return (ft_error("Error: argument\n", &board, NULL));
	if (!(fd = fopen(argv[1], "r")))
		return (ft_error("Error: Operation file corrupted\n", &board, fd));
	if (fscanf(fd, "%d %d %c\n", &board.w, &board.h, &board.bc) < 3)
		return (ft_error("Error: Operation file corrupted\n", &board, fd));
	if (board.w < 0 || board.w >= 300 || board.h < 0 || board.h >= 300)
		return (ft_error("Error: Operation file corrupted\n", &board, fd));
	if (ft_fillboard(&board))
		return (ft_error("Error: Operation file corrupted\n", &board, fd));
	if (ft_paint(&board, fd))
		return (ft_error("Error: Operation file corrupted\n", &board, fd));
	ft_printdraw(&board);
	ft_freeall(&board);
	fclose(fd);
	return (0);
}
