#ifndef SD_MESH_H
#define SD_MESH_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE -1
#endif

typedef enum {	SDM_ENONE=0,
				SDM_EBUSY,
				SDM_INVAL,
				SDM_ERR_SEARCH_TIMEOUT
			} SDM_ERROR_CODE;

typedef enum {	SDM_SEARCH_REQUEST_FAILED=0,
				SDM_SEARCH_REQUEST_PENDING,
				SDM_SEARCH_REQUEST_SUCCESS,
				SDM_SEARCH_REQUEST_UNKNOWN
			} SDM_SEARCH_STATUS;

typedef enum {WEAK_NODE_MODE=0, SUPER_NODE_MODE} NodeOperatingMode;  
typedef struct {
	NodeOperatingMode node_mode;
	unsigned int capacity_rate;
	time_t ts_registry;
} NodeConfig;

typedef void (*FAILED_NODE_REQUEST_FUNC_TYPE)(IPV6_TYPE* );
typedef void (*SEND_DATA2NODES_FUNC_TYPE)(unsigned char*, unsigned int);

SDM_ERROR_CODE sdm_get_last_errno();
//first initiating node procedure
int sdm_init(IPV6_TYPE uuid, IPV4_TYPE ip, PORT_TYPE port);
int sdm_send_sys_info(unsigned long cpu_freq, unsigned int core_cnt, unsigned int ram_size);
int sdm_uninit();
int sdm_hello();
int sdm_ping(IPV6_TYPE uuid);
int sdm_insert_node(IPV6_TYPE uuid, IPV4_TYPE ip, PORT_TYPE port);
int sdm_handler(in_buf, in_buf_len, out_sleep);
unsigned int sdm_search_peer(IPV6_TYPE uuid);
SDM_SEARCH_STATUS sdm_get_search_peer_status(const unsigned int req_handle);
unsigned int sdm_get_nodes_cnt();
RootingEntity* sdm_get_nodes();
int sdm_blacklisted();
void sdm_dump_tables();
void sdm_reg_failed_node_request_callback(FAILED_NODE_REQUEST_FUNC_TYPE customClbck);
void sdm_reg_send_data_callback(SEND_DATA2NODES_FUNC_TYPE sendToClbck);

#ifdef __cplusplus
}
#endif

#endif
