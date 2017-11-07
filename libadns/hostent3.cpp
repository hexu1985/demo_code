#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <string.h>
#include <poll.h>
#include "adns.h"

void print_answer(adns_answer *answer)
{
    assert(answer);
    printf("answer of %s:\n", answer->owner);
    if (answer->status != adns_s_ok) {
        printf("    %s\n", adns_strerror(answer->status));
        return;
    }
    printf("    nrrs = %d\n", answer->nrrs);
    int nrrs = answer->nrrs;
    if (nrrs <= 0)
        return;

    int rrn = 0;
    const char *rrp = NULL;
    char *datastr = NULL;
    for (rrn = 0, rrp = (const char *) answer->rrs.untyped; rrn < nrrs; ++rrn, rrp += answer->rrsz) {
        adns_status st = adns_rr_info(answer->type, NULL, NULL, NULL, rrp, &datastr);
        if (st != adns_s_ok) {
            continue;
        }

        printf("    %d, rr = %s\n", rrn+1, datastr);
        free(datastr);
    }
}

int main(int argc, char **argv)
{
    adns_state ads;  
    adns_initflags flags;    
    //    flags = (adns_initflags) (adns_if_nosigpipe | adns_if_noerrprint);
    flags = (adns_initflags) (adns_if_nosigpipe | adns_if_noautosys);
    int err = 0;
    err = adns_init(&ads, flags, NULL); // step 1
    if (err != 0) {
        printf("adns_init error!\n");
        exit(1);
    }

    adns_query qu = NULL;  
    adns_queryflags quflags;
//    quflags = (adns_queryflags) (adns_qf_want_ipv4 | adns_qf_cname_loose | adns_qf_owner);
    quflags = (adns_queryflags) (adns_qf_cname_loose | adns_qf_owner);
    for (int i = 1; i < argc; ++i) {
        const char *host = argv[i];
        qu = NULL;
        err = adns_submit(ads, host, (adns_rrtype) adns_r_a, quflags, NULL, &qu);  // step 2, if need ipv6 addr, use adns_r_aaaa
        if (err != 0) {
            printf("adns_submit error for \'%s\'!\n", host);
            exit(1);
        }
    }

    adns_answer *answer;  
    int n = argc-1;
    int r;
    const int OPEN_MAX = 1024;
    struct pollfd fds[OPEN_MAX];
    int nfds = OPEN_MAX;
    int timeout_ms = 0;
    while (true) {
        adns_beforepoll(ads, fds, &nfds, &timeout_ms, 0);
        r = poll(fds, nfds, timeout_ms);
        if (r == -1) {
            if (errno == EINTR) continue;
            printf("poll error: %s\n", strerror(errno));
            exit(1);
        }
        adns_afterpoll(ads, fds, nfds, 0);

        while (true) {
            qu = NULL;  // must do this
            err = adns_check(ads, &qu, &answer, NULL);  // step 4
            if (err != 0) {
                if (err == EAGAIN)
                    break;
                printf("adns_check error!\n");
                exit(1);
            }

            print_answer(answer);   // step 5
            free(answer);
            --n;
            if (n == 0)
                break;
        }

        if (n == 0)
            break;
    }

    adns_finish(ads);       // step 6

    exit(0);
}

