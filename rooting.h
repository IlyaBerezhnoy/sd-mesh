#ifndef ROOTING_H
#define ROOTING_H

#include "peernode.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sRootingEntity{
	Peer peer;
	IPV6_TYPE net_mask;
	unsigned short shared;		/* how many peers have this node in its root table */
	short hits_per100;			/* moving average of paths found for last 100 requests */
	unsigned short path_get;
	unsigned short path_req;
	//unsigned short metric;	//average of time response
	int overloaded;
	time_t reply_time;          /* time of last correct reply received */
    time_t pinged_time;         /* time of last request */	
    int pinged;                 /* how many requests we sent since last reply */
	sRootingEntity* pNext;
} RootingEntity;

// typedef struct {
// 	RootingEntity ent;
// 	RootingEntity* pNext;
// } RootingNode;

RootingEntity* rt_insert(RootingEntity* head, Peer* src_peer);
RootingEntity* rt_free(RootingEntity* node);
void rt_sort(RootingEntity* head, int (*f_comparator)(RootingEntity*, RootingEntity*));
RootingEntity* rt_get_node(RootingEntity* root, IPV6_TYPE uuid);
void rt_dump(RootingEntity *root, unsigned int deep);

#ifdef __cplusplus
}
#endif

#endif