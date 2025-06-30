#ifndef CUBE_H
#define CUBE_H

#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <mlx.h>
#include <sys/wait.h>

#define window_px 16
#define window_py 16
#define wall_color 0x00FF0000
#define player_color 0x00FFFF00
#define player_raduis 7


typedef struct s_color
{
    int a;
    int b;
    int c;
}t_color;


typedef struct s_map
{
    int rows;
    int colomns;
    char **map;
}t_map;


typedef struct s_player
{
    int x;
    int px;
    int y;
    int py;
    char    *direction;
}t_player;

typedef struct s_draw
{
    void    *mlx;
    void    *win;
    void    *wall_img;
    void    *player_img;
}t_draw;

typedef struct s_elements
{
    t_draw  *drawing;
    char    *no;
    char    *so;
    char    *ea;
    char    *we;
    t_color *f;
    t_color *c;
    t_map   *map;
    t_player    *player;
}t_elements;


void        parcing_mn(int ac, char **argv);
void        map(char **argv);
int         copy_map(char *line, int fd);
int         upload_map(char **argv);
void        strlen_exit(void);
void        ft_error(const char *str);
void        ft_error_el(const char *str);
int         ff_strlen(const char *str);
t_elements  *getter(void);
void        ft_bzero(void *s, size_t n);
int         extruct_map(char *line, int fd);
int         start_map(char *line, int fd);
char        *ft_strnext( char *haystack, const char *needle);
int         extruct_elements(char *line);
int         extruct_them(char *line);
void        cheack_map(void);
void        print_map(t_elements *element);
void        deb_map(void);


//player
void        set_up_player(void);
void        deb_map(void);
void        inisialise_dr(void);
void        set_up_player(void);
void        render_frame(void);
// get_next_line

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif


char	*get_next_line(int fd);
size_t	ft_strlen(char *s);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*reset_res(char *reserve);
char	*read_mine(int fd);
char	*get_line(char *reserve);
void	ft_memcpy(char *s1, char *s2, size_t i);

// libft
char	**ft_split(char const *s, char c);
int     ft_atoi(const char *str);






#endif
