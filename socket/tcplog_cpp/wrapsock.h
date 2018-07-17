#ifndef	__unp_wrapsock_h
#define	__unp_wrapsock_h

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "error.h"

#define	SA	struct sockaddr

/* Define to 1 if you have the `inet6_rth_init' function. */
//#define HAVE_INET6_RTH_INIT 1

#ifdef HAVE_POLL 
#include <poll.h>
#endif

/* #define HAVE_EPOLL 1 */

#ifdef HAVE_EPOLL
#include <sys/epoll.h>
#endif

			/* prototypes for our socket wrapper functions: see {Sec errors} */
int		 Accept(int, SA *, socklen_t *);
void	 Bind(int, const SA *, socklen_t);
void	 Connect(int, const SA *, socklen_t);
void	 Getpeername(int, SA *, socklen_t *);
void	 Getsockname(int, SA *, socklen_t *);
void	 Getsockopt(int, int, int, void *, socklen_t *);
void	 Listen(int, int);
#ifdef	HAVE_POLL
int		 Poll(struct pollfd *, unsigned long, int);
#endif
ssize_t	 Readline(int, void *, size_t);
ssize_t	 Readn(int, void *, size_t);
ssize_t	 Recv(int, void *, size_t, int);
ssize_t	 Recvfrom(int, void *, size_t, int, SA *, socklen_t *);
ssize_t	 Recvmsg(int, struct msghdr *, int);
int		 Select(int, fd_set *, fd_set *, fd_set *, struct timeval *);
void	 Send(int, const void *, size_t, int);
void	 Sendto(int, const void *, size_t, int, const SA *, socklen_t);
void	 Sendmsg(int, const struct msghdr *, int);
void	 Setsockopt(int, int, int, const void *, socklen_t);
void	 Shutdown(int, int);
int		 Sockatmark(int);
int		 Socket(int, int, int);
void	 Socketpair(int, int, int, int *);
void	 Writen(int, void *, size_t);

#ifdef  HAVE_EPOLL
int      Epoll_create(int);
int      Epoll_create1(int);
int      Epoll_ctl(int, int, int, struct epoll_event *);
int      Epoll_wait(int, struct epoll_event *, int, int);
#endif

#endif

