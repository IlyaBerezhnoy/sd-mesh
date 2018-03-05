#include <stdlib.h>
#include <time.h>
#include "peernode.h"

#define PEER_TABLE_SIZE	511
#define PEER_ADR_CNT	3

typedef struct sPeer {
	Peer peer;
	struct sPeer *pNext;
} PeerNode;

PeerNode* PHT[PEER_TABLE_SIZE];

static unsigned int get_hash(const IPV6_TYPE uuid);
//static int pnt_compare(PeerNode* node1, PeerNode* node2);

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
	PeerNode* pn = PHT[get_hash(uuid)];			
	if(pn == NULL) return TRUE;	

	PeerNode** lp = &PHT[hash];	
	for( ; pn != NULL; pn = pn->pNext )
	{
		if (id_cmp(uuid, pn->peer.uuid) == 0)
		{
			lp = &pn->pNext;
			free(pn);
			return TRUE;
		}
		*lp = pn->pNext;
	}
	return TRUE;
}

void pnt_free()
{
	PeerNode* pn = NULL;
	PeerNode* tmp = NULL;
	for(int i = 0; i < PEER_TABLE_SIZE; i++)
	{
		pn = PHT[i];
		while(pn != NULL)
		{
			tmp = pn->pNext;
			free(pn);
			pn = tmp;
		}
		PHT[i] = NULL;
	}
}

void get_peer_view(char *pBuf, Peer *peer)
{
	//out ipv6
	unsigned int i = 0;
	unsigned int* pID = peer->uuid;
    sprintf(pBuf, "%04X:%04X:%04X:%04X:%04X:%04X:%04X:%04X\t", pUUID[i++], pUUID[i++], pUUID[i++], pUUID[i++], pUUID[i++], pUUID[i++], pUUID[i++], pUUID[i++]);
    
    pBuf += strlen(pBuf);        
    pID = peer->address1.ip;
    unsigned int port = peer->address1.port;
    sprintf(pBuf, "%d.%d.%d.%d:%d\t", pID[i++], pID[i++], pID[i++], pID[i++], port);
    
    pBuf += strlen(pBuf);    
    i = 0;
    pID = peer->address2.ip;
    port = peer->address2.port;
    sprintf(pBuf, "%d.%d.%d.%d:%d\t", pID[i++], pID[i++], pID[i++], pID[i++], port);    
}

void pnt_dump(unsigned int deep)
{		
	int deep_control = deep > 0;
	char buf[256];	
	PeerNode* pn = NULL;
	Peer* peer = NULL;
	print("UUID\t\t\t\t|IP:Port1\t\t\t\t|IP:Port2\r\n");
	print("|-----------------------------------------------------------------------------------------------------------------------------|\r\n");
	for (int i = 0; i < PEER_TABLE_SIZE; i++,deep--) 
    {    	
    	pn = DHT[i];
    	while(pn != NULL)
    	{        			
    		get_peer_view(buf, pn->peer);
    		strcat(buf, "\r\n");
    		print(buf);
    		pn = pn->pNext;

    		if(deep_control && --deep == 0)
    			return;
    	}    	
    }    	
    print("|-----------------------------------------------------------------------------------------------------------------------------|\r\n");
}