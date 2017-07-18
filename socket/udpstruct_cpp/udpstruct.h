#ifndef	UDPSTRUCT_H
#define	UDPSTRUCT_H

struct Request {
	uint16_t v1;
	uint8_t v2;
	uint16_t v3;
} __attribute__ ((__packed__));

struct Response {
	uint16_t ret;
} __attribute__ ((__packed__));

#endif
