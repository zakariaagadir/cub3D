#ifndef CUBE_H
#define CUBE_H

#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>


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

typedef struct s_elements
{
    char    *no;
    char    *so;
    char    *ea;
    char    *we;
    t_color *f;
    t_color *c;
    t_map   *map;
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
