#include	"dg_cli.h"

void
dg_cli(FILE *fp, int sockfd, const sockaddr *pservaddr, socklen_t servlen)
{
	int	n;
    const int MAXLINE = 8192;
	char	sendline[MAXLINE], recvline[MAXLINE + 1];

	while (Fgets(sendline, MAXLINE, fp) != NULL) {

		Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);

		n = Recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);

		recvline[n] = 0;	/* null terminate */
		Fputs(recvline, stdout);
	}
}
