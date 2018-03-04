#include <stdlib.h>
#include <time.h>
#include "peernode.h"

#define PEER_TABLE_SIZE	513
#define PEER_ADR_CNT	3

typedef struct sPeer {
	Peer peer;
	struct sPeer *pNext;
} PeerNode;

PeerNode* PHT[PEER_TABLE_SIZE];

static unsigned int get_hash(const IPV6_TYPE uuid);

static int pnt_compare(PeerNode* node1, PeerNode* node2);

Peer* new_peer(IPV6_TYPE uuid, IPV4_TYPE ip, PORT_TYPE port) {
	Peer* inst = malloc(sizeof(Peer));
	if(inst != NULL) {
		memset(inst, 0, sizeof(Peer));
		memcpy(inst->uuid, uuid, sizeof(IPV6_TYPE));
		memcpy(inst->address1.ip, ip, sizeof(IPV4_TYPE));
		memcpy(&inst->address1.port, port, sizeof(PORT_TYPE));
	}
	return inst;
}

void free_peer(Peer* inst) {
	free(inst);
	inst = NULL;
}

void generate_peer_uuid(IPV6_TYPE uuid) {
	if(uuid != NULL)
	{
		time_t t;
		srand((unsigned)time(&t));
		int *pid = (int*)uuid;
		for (char i = 0; i < sizeof(IPV6_TYPE) / sizeof(int); i++) {
			*pid++ = rand();
		}
		uuid[6] = 0x40 | (uuid[6] & 0xf);
		uuid[8] = 0x80 | (uuid[8] & 0x3f);
	}
	return uuid;
}

int id_cmp(const IPV6_TYPE id1, const IPV6_TYPE id2)
{
    return memcmp(id1, id2, sizeof(IPV6_TYPE));
}

static unsigned int get_hash(const IPV6_TYPE uuid)
{
	unsigned int hash = 0;
	unsigned char* p = uuid;
	unsigned char* end = uuid+sizeof(IPV6_TYPE);
	for (; p < end; p++)
		hash += *p;
	return hash % PEER_TABLE_SIZE;
}

Peer* pnt_lookup(const IPV6_TYPE uuid)
{
	unsigned int hash = get_hash(uuid);
	PeerNode* pn = PHT[hash];
	for (; pn != NULL; pn = pn->pNext)
	{
		if (id_cmp(uuid, pn->peer.uuid) == 0)
			return &pn->peer;		
	}
	return NULL;
}

Peer* pnt_insert(const IPV6_TYPE uuid, const IPV4_TYPE ip, const PORT_TYPE port)
{
	PeerNode* pn =  pnt_lookup(uuid);
	if (pn == NULL)
	{
		//new element
		if ((pn = malloc(sizeof(PeerNode))) == NULL)
			return NULL;
		unsigned int hash = get_hash(uuid);
		memcpy(pn->peer.uuid, uuid, sizeof(IPV6_TYPE));
		pn->pNext = PHT[hash];
		PHT[hash] = pn;
 	}
	
	memcpy(pn->peer.address1.ip, ip, sizeof(IPV4_TYPE));
	memcpy(pn->peer.address1.port, &port, sizeof(PORT_TYPE));

	return &pn->peer;	
}

int pnt_delete_node(const IPV6_TYPE uuid)
{

	PeerNode* tmp = NULL;
	if(node != NULL)
	{
		PeerNode* nodePrev = node->pPrev;
		PeerNode* nodeNext = node->pNext;
		free(node);
		if(nodePrev != NULL)
		{
			nodePrev->pNext = nodeNext;
			tmp = nodePrev;
		}
		
		if(nodeNext != NULL)
		{
			nodeNext->pPrev = nodePrev;
			if(tmp == NULL)
				tmp = nodeNext;	
		}				
	}
	return tmp;
}

PeerNode* pnt_free(PeerNode* root)
{
	if(root == NULL)	return NULL;
	
	while(root->pPrev != NULL)
		root = root->pPrev;

	PeerNode* tmp = NULL;
	while(root != NULL) {
		tmp = root;
		root = root->pNext;
		free(tmp);
	}
	return root;
}

void pnt_dump(PeerNode *node, unsigned int deep)
{
	print("UUID\t\t|IP:Port1\t\t|IP:Port2\n");
    for ( ; node != NULL && deep > 0; node = node->pNext, deep-- ) 
    {
    	//todo print uuid and ip port
    	
    }    	
}