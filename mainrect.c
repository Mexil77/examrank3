#include "micro_paint.h"

void	ft_print(t_board *b);

size_t	ft_strlen(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while(str[i])
		i++;
	return (i);
}

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

int	ft_error(char *err, t_board *b, FILE *fd)
{
	if (fd)
		fclose(fd);
	write(1, err, ft_strlen(err));
	ft_freeall(b);
	return (1);
}

int ft_fillboard(t_board *b)
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
	while (b->board[++i])
	{
		j = -1;
		while (++j < b->w)
			b->board[i][j] = b->bc;
	}
	return (0);
}

void	ft_draw(t_board *b)
{
	int	i;
	int	j;

	i = -1;
	while (b->board[++i])
	{
		j = -1;
		while (b->board[i][++j])
		{
			if (b->type == 'R' && j >= b->xi && j <= (b->xi + b->rw)
				&& i >= b->yi && i <= (b->yi + b->rh))
				b->board[i][j] = b->c;
			if (b->type == 'r' && (((j - b->xi) < 1 && (j - b->xi) >= 0 && i >= b->yi && i <= (b->yi + b->rh))
				|| ((i - b->yi) < 1 && (i - b->yi) >= 0 && j >= b->xi && j <= (b->xi + b->rw))
				|| (((b->xi + b->rw) - j) < 1 && ((b->xi + b->rw) - j) >= 0 && i >= b->yi && i <= (b->yi + b->rh))
				|| (((b->yi + b->rh) - i) < 1 && ((b->yi + b->rh) - i) >= 0 && j >= b->xi && j <= (b->xi + b->rw))))
				b->board[i][j] = b->c;
		}
	}
}

int	ft_drawrect(t_board *b, FILE *fd)
{
	int	scan;

	while ((scan = fscanf(fd, "%c %f %f %f %f %c\n", &b->type, &b->xi, &b->yi, &b->rw, &b->rh, &b->c)) == 6)
	{
		if ((b->type != 'r' && b->type != 'R') || b->rw <= 0 || b->rh <= 0)
			return (1);
		else
			ft_draw(b);
	}
	if (scan > -1)
		return (1);
	return (0);
}

void	ft_print(t_board *b)
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
	if (argc != 2)
		return (ft_error("Error: argument\n", &board, NULL));
	if (!(fd = fopen(argv[1], "r")))
		return (ft_error("Error: Operation file corrupted\n", &board, fd));
	if (fscanf(fd, "%d %d %c\n", &board.w, &board.h, &board.bc) < 3)
		return (ft_error("Error: Operation file corrupted\n", &board, fd));
	if (board.w <= 0 || board.w > 300 || board.h <= 0 || board.h > 300)
		return (ft_error("Error: Operation file corrupted\n", &board, fd));
	if (ft_fillboard(&board))
		return (ft_error("Error: Operation file corrupted\n", &board, fd));
	if (ft_drawrect(&board, fd))
		return (ft_error("Error: Operation file corrupted\n", &board, fd));
	ft_print(&board);
	fclose(fd);
	ft_freeall(&board);
	return (0);
}