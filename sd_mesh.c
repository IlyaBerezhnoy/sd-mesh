#include <stdio.h>
#include <stdlib.h>

#include "rooting.h"
#include "sd_mesh.h"

#define MAX(x, y) ((x) >= (y) ? (x) : (y))
#define MIN(x, y) ((x) <= (y) ? (x) : (y))

static FAILED_NODE_REQUEST_FUNC_TYPE failedNodeRequestClbck = NULL;
static SEND_DATA2NODES_FUNC_TYPE sendToClbck = NULL;
static SDM_ERROR_CODE last_err_no = SDM_ENONE;

#define SET_ERR_NO(ERR_CODE) (last_err_no=ERR_CODE)

struct network_request {
    unsigned int rid;    
    int cmd;    
    IPV6_TYPE src_uuid;
    unsigned short src_port;
    int hop_len;
    unsigned int data_len; 
    unsigned char *data;
};

struct network_response {
    unsigned int rid;
    int cmd;
	IPV6_TYPE dest_uuid;
    unsigned short dest_port;
    int hop_len;
    unsigned int data_len; 
    unsigned char *data;
};

static RootingEntity* rootingTable = NULL;
static PeerNode* leafTable = NULL;
static Peer* self = NULL;

void sdm_reg_failed_node_request_callback(FAILED_NODE_REQUEST_FUNC_TYPE customClbck)
{
	failedNodeRequestClbck = customClbck;
}

void sdm_reg_send_data_callback(SEND_DATA2NODES_FUNC_TYPE customClbck)
{
	sendToClbck = customClbck;
}

SDM_ERROR_CODE sdm_get_last_errno()
{
	return last_err_no;
}

//first initiating node
int sdm_init(IPV6_TYPE uuid, IPV4_TYPE ip, PORT_TYPE port)
{
    if(rootingTable > 0 || leafTable > 0 || self == NULL) 
    {
		SET_ERR_NO(SDM_EBUSY);
        return FALSE;
    }

    self = new_peer(uuid, ip, port);
    leafTable = pnt_insert(NULL, self);

    return sdm_hello();
}

int sdm_uninit()
{
 	if(rootingTable == NULL && leafTable == NULL && self == NULL) 
 	{
		SET_ERR_NO(SDM_INVAL);
        return FALSE;
    }	

    rt_free(rootingTable);
    pnt_free(leafTable);

    return TRUE;
}

int sdm_hello()
{
	//introduce yourself
	return TRUE;
}

int sdm_ping(IPV6_TYPE uuid)
{

}

int sdm_insert_node(IPV6_TYPE uuid, IPV4_TYPE ip, PORT_TYPE port)
{

}

int sdm_handler(unsigned char* in_buf, const unsigned int in_buf_len, unsigned int* out_sleep)
{

}

unsigned int sdm_search_peer(IPV6_TYPE uuid)
{

}

SDM_SEARCH_STATUS sdm_get_search_peer_status(const unsigned int req_handle)
{

}

unsigned int sdm_get_nodes_cnt()
{

}

RootingEntity* sdm_get_nodes()
{

}

int sdm_blacklisted()
{
	//todo implement
	return FALSE;
}

void sdm_dump_tables()
{
	//todo implement
	return FALSE;
}

int sdm_send_sys_info(unsigned long cpu_freq, unsigned int core_cnt, unsigned int ram_size)
{
	//todo implement
	return FALSE;
}
