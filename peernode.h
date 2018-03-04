#ifndef Peer_H
#define Peer_H

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char IPV6_TYPE[16];
typedef unsigned char IPV4_TYPE[4];
typedef unsigned short PORT_TYPE;


#define IPV6_SIZE (sizeof(IPV6_TYPE)/sizeof(unsigned char))
#define IPV4_SIZE (sizeof(IPV4_TYPE)/sizeof(unsigned char))


typedef struct{
	PORT_TYPE port;
	IPV4_TYPE ip;	
} Address;

typedef struct{
	IPV6_TYPE uuid;
	Address address1;
	Address address2;		
} Peer;


Peer* new_peer(IPV6_TYPE uuid, IPV4_TYPE ip, PORT_TYPE port);
void free_peer(Peer* peer);
void generate_peer_uuid(IPV6_TYPE uuid);
int id_cmp(const IPV6_TYPE id1, const IPV6_TYPE id2);
Peer* pnt_insert(Peer* new_peer);
Peer* pnt_delete_node(IPV6_TYPE uuid);
Peer* pnt_free(IPV6_TYPE uuid);
Peer* pnt_get_peer(IPV6_TYPE uuid);
void pnt_dump(unsigned int deep);

#ifdef __cplusplus
}
#endif

#endif Peer_H