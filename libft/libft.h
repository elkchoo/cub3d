/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Elkan Choo <echoo@42mail.sutd.edu.sg>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:14:04 by echoo             #+#    #+#             */
/*   Updated: 2025/12/26 17:27:58 by Elkan Choo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdarg.h>
# include <stdint.h>
# include <stddef.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list			*ft_lstnew(void *content);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstdelone(t_list *lst, void (*del)(void*));
int				ft_lstsize(t_list *lst);
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));

int				ft_atoi(const char *str);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t nmemb, size_t size);
int				ft_isalpha(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
char			*ft_itoa(int n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memset(void *s, int c, size_t n);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);
char			**ft_split(char const *str, char c);
char			*ft_strchr(const char *s, int c);
char			*ft_strdup(const char *s);
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlcat(char *dest, const char *src, size_t size);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlen(const char *str);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*ft_strrchr(const char *s, int c);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);
int				ft_tolower(int c);
int				ft_toupper(int c);

// ft_printf
int				ft_prtchar(char c, va_list *ap, int *count);
int				ft_printf(const char *s, ...);
int				ft_prtnbr(int n, int *count);
int				ft_prtptr(va_list *ap, int *count, char c);
int				ft_prtstr(char *s, int *count);
int				ft_prtuint(unsigned int n, int *count);
int				ft_prt_hex(char c, uintptr_t num, int *count);
void			ft_utohextoa(uintptr_t num, char *string, char *base);
char			*ft_utoa(unsigned int n);

// ft_dprintf
int				ft_dprtchar(int fd, char c, va_list *ap, int *count);
int				ft_dprintf(int fd, const char *s, ...);
int				ft_dprtnbr(int fd, int n, int *count);
int				ft_dprtptr(int fd, va_list *ap, int *count, char c);
int				ft_dprtstr(int fd, char *s, int *count);
int				ft_dprtuint(int fd, unsigned int n, int *count);
int				ft_dprt_hex(int fd, char c, uintptr_t num, int *count);

// GNL
// GNL returns NULL if EOF or if an error occurs. So, GNL cannot detect errors
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char			*get_next_line(int fd);
char			*calc_return(int n_eof, char *buf);
char			*get_next_line(int fd);
int				calc_leftover(char **buf, size_t *len,
					int *newline_index, char **leftover);
int				read_fd(char **buf, size_t *len, int *newline_index, int fd);
int				store_leftover(char **buf, size_t len,
					int newline_index, char **leftover);
int				ft_newline(char *str, int i);
void			ft_gnl_strlcpy(char *dst, const char *src, size_t size);

// OWN FUNCTIONS

long long int	ft_atoll(const char *str);

// n is number of ints, NOT number of bytes
/**
 * @param s Array of ints to search for
 * @param c Int to search for
 * @param n Number of ints in the array
 * @return Returns a pointer to the first occurrence of the integer, returns
 * NULL if the int is not found.
 */
int				*ft_intchr(const int *s, const int c, const size_t n);

// Duplicates the integer array.
/**
 * @param i pointer to the array
 * @param len number of elements in the array
 * @return Returns a pointer to the duplicated array, returns NULL if malloc
 * fails
 */
int				*ft_int_arr_dup(const int *i, size_t len);

// returns the int difference between x and y
unsigned int	ft_idim(int x, int y);

// sets the value of all ints pointed to by the function to zero. num is the
// number of values you're passing into it. Make sure you're passing pointers
// to the function, as that's what the function expects, and the function can't
// edit your ints otherwise
void			ft_set_zero(int num, ...);

// Replaced str_1 with a string of str_1 and str_2 combined. Returns 0 on
// failure, 1 upon success. str_1 MUST be freeable.
int				ft_merge_strings(char **str_1, char *str_2);

// Does the same as merge strings, but appends up to 10 strings (can increase
// if I really want to, but I probably won't need to) to str_1. Takes the
// strings as variadic variables, thus the var name.
/**
 * @param str_1 Pointer to the first string
 * @param str_count Numer of strings to append
 * @return Returns 0 on failure, 1 on success
 */
int				ft_merge_strings_var(char **str_1, int str_count, ...);

// Returns an array of elements contained in a t_list list. The array can be
// is malloced and must be freed. So, if content points to an int, this will
// return an array of all ints in the linked list.
void			*ft_t_list_to_array(t_list *list, size_t content_size);

// Fully reads the file in the file descriptor, ensuring no leftovers remain.
void			ft_flush(int fd);

// Fully frees an array[][]. Array MUST be NULL terminated
void			ft_free_arrays(char **array);

// Now evaluates each character in a given formula, so that split conditions
// can be more easily customised
char			**ft_split_f(char const *str, int (is_sep)(char));

// Yiyuan library functions

/* ************************************************************************** */
/*                           Vector / dynamic array                           */
/* ************************************************************************** */

/**
 * @brief Dynamic array (vector) with automatic resizing.
 *
 * Provides O(1) amortized push/pop at the end and O(1) random access.
 * Elements are stored contiguously for cache efficiency.
 */
typedef struct s_vec
{
	void	*data;
	size_t	len;
	size_t	cap;
	size_t	elem_size;
}			t_vec;

/**
 * @brief Create a new vector with specified element size and initial capacity.
 * @param elem_size Size of each element in bytes. Must be > 0.
 * @param init_cap Initial capacity. If 0, defaults to a reasonable size.
 * @return Pointer to new vector, or NULL on failure.
 */
t_vec		*ft_vec_new(size_t elem_size, size_t init_cap);

/**
 * @brief Append an element to the end of the vector.
 * @param vec Pointer to vector.
 * @param elem Pointer to element to copy.
 * @return 1 on success, 0 on failure.
 * @note Grows capacity automatically when full. O(1) amortized.
 */
int			ft_vec_push(t_vec *vec, const void *elem);

/**
 * @brief Remove and optionally return the last element.
 * @param vec Pointer to vector.
 * @param out Output buffer for removed element. Can be NULL to discard.
 * @return 1 on success, 0 if vector is NULL or empty.
 */
int			ft_vec_pop(t_vec *vec, void *out);

/**
 * @brief Get pointer to element at index.
 * @param vec Pointer to vector.
 * @param index Index of element (0-based).
 * @return Pointer to element, or NULL if out of bounds/NULL.
 */
void		*ft_vec_get(t_vec *vec, size_t index);

/**
 * @brief Set element at index by copying from elem.
 * @param vec Pointer to vector.
 * @param index Index of element to set.
 * @param elem Pointer to new element value.
 * @return 1 on success, 0 if out of bounds or NULL args.
 */
int			ft_vec_set(t_vec *vec, size_t index, const void *elem);

/**
 * @brief Free all memory associated with a vector.
 * @param vec Pointer to vector. Safe to call with NULL.
 */
void		ft_vec_free(t_vec *vec);

/**
 * @brief Reset vector to empty state without freeing memory.
 * @param vec Pointer to vector. Safe to call with NULL.
 */
void		ft_vec_clear(t_vec *vec);

/**
 * @brief Ensure vector has at least new_cap capacity.
 * @param vec Pointer to vector.
 * @param new_cap Minimum capacity required.
 * @return 1 on success, 0 on failure.
 * @note Does nothing if current capacity >= new_cap.
 */
int			ft_vec_reserve(t_vec *vec, size_t new_cap);

/**
 * @brief Insert an element at the specified index.
 * @param vec Pointer to vector.
 * @param index Index where element will be inserted.
 * @param elem Pointer to element to copy.
 * @return 1 on success, 0 on failure.
 * @note Elements at index and beyond are shifted right. O(n).
 */
int			ft_vec_insert(t_vec *vec, size_t index, const void *elem);

/* ************************************************************************** */
/*                              2D Vector Math                                */
/* ************************************************************************** */

typedef struct s_vec2
{
	double	x;
	double	y;
}			t_vec2;

/**
 * @brief Create a 2D vector from components.
 * @param x X component.
 * @param y Y component.
 * @return New vector with specified components.
 */
t_vec2		ft_vec2_new(double x, double y);

/**
 * @brief Add two 2D vectors component-wise.
 * @param a First vector.
 * @param b Second vector.
 * @return Sum of vectors (a.x + b.x, a.y + b.y).
 */
t_vec2		ft_vec2_add(t_vec2 a, t_vec2 b);

/**
 * @brief Subtract vector b from vector a.
 * @param a First vector.
 * @param b Second vector.
 * @return Difference (a.x - b.x, a.y - b.y).
 */
t_vec2		ft_vec2_sub(t_vec2 a, t_vec2 b);

/**
 * @brief Multiply vector by scalar.
 * @param v Vector to scale.
 * @param s Scalar multiplier.
 * @return Scaled vector (v.x * s, v.y * s).
 */
t_vec2		ft_vec2_scale(t_vec2 v, double s);

/**
 * @brief Compute dot product of two vectors.
 * @param a First vector.
 * @param b Second vector.
 * @return Dot product (a.x * b.x + a.y * b.y).
 */
double		ft_vec2_dot(t_vec2 a, t_vec2 b);

/**
 * @brief Compute vector magnitude.
 * @param v Vector.
 * @return Length √(x² + y²).
 */
double		ft_vec2_len(t_vec2 v);

/**
 * @brief Compute squared length (avoids sqrt).
 * @param v Vector.
 * @return Squared length x² + y².
 */
double		ft_vec2_len_sq(t_vec2 v);

/**
 * @brief Normalize vector to unit length.
 * @param v Vector to normalize.
 * @return Unit vector with same direction, or zero vector if input is zero.
 */
t_vec2		ft_vec2_norm(t_vec2 v);

/**
 * @brief Distance between two points.
 * @param a First point.
 * @param b Second point.
 * @return Distance |b - a|.
 */
double		ft_vec2_dist(t_vec2 a, t_vec2 b);

/**
 * @brief Linear interpolation between two vectors.
 * @param a Start vector (t=0).
 * @param b End vector (t=1).
 * @param t Interpolation parameter.
 * @return Interpolated vector a + t * (b - a).
 */
t_vec2		ft_vec2_lerp(t_vec2 a, t_vec2 b, double t);

/**
 * @brief Rotate vector by angle (radians).
 * @param v Vector to rotate.
 * @param angle Rotation angle in radians.
 * @return Rotated vector.
 */
t_vec2		ft_vec2_rotate(t_vec2 v, double angle);

#endif
