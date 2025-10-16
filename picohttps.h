/* Pico HTTPS request example *************************************************
 *                                                                            *
 *  An HTTPS client example for the Raspberry Pi Pico W                       *
 *                                                                            *
 *  A simple yet complete example C application which sends a single request  *
 *  to a web server over HTTPS and reads the resulting response.              *
 *                                                                            *
 ******************************************************************************/

#ifndef PICOHTTPS_H
#define PICOHTTPS_H



/* Options ********************************************************************/

// Wireless region
//
//  `country` argument to cyw43_arch_init_with_country().
//
//  For best performance, set to local region.
//
//  https://www.raspberrypi.com/documentation/pico-sdk/networking.html#CYW43_COUNTRY_
//
#define PICOHTTPS_INIT_CYW43_COUNTRY                CYW43_COUNTRY_SWEDEN

// Wireless network SSID
#define PICOHTTPS_WIFI_SSID                         "Aydil"

// Wireless network connection timeout
//
//  `timeout` argument to cyw43_arch_wifi_connect_timeout_ms().
//
//  https://www.raspberrypi.com/documentation/pico-sdk/networking.html
//
#define PICOHTTPS_WIFI_TIMEOUT                      30000           // ms

// Wireless network password
//
//  N.b. _Strongly_ recommend setting this from the environment rather than
//  here. Environment values will have greater precedence. See CMakeLists.txt.
//
#ifndef PICOHTTPS_WIFI_PASSWORD
#define PICOHTTPS_WIFI_PASSWORD                     "12345678"
#endif // PICOHTTPS_WIFI_PASSWORD

// HTTP server hostname
#define PICOHTTPS_HOSTNAME                          "webhook.site"

// DNS response polling interval
//
//  Interval with which to poll for responses to DNS queries.
//
#define PICOHTTPS_RESOLVE_POLL_INTERVAL             100             // ms

// Certificate authority root certificate
//
//  CA certificate used to sign the HTTP server's certificate. DER or PEM
//  formats (char array representation).
//
//  This is most readily obtained via inspection of the server's certificate
//  chain, e.g. in a browser.
//

// #define PICOHTTPS_CA_ROOT_CERT \
// "-----BEGIN CERTIFICATE----- \n" \
// "MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw\n" \
// "TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh\n" \
// "cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4\n" \
// "WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu\n" \
// "ZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY\n" \
// "MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc\n" \
// "h77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+\n" \
// "0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U\n" \
// "A5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW\n" \
// "T8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH\n" \
// "B5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFvu396j3x+UC\n" \
// "B5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf1b0SHzUv\n" \
// "KBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWn\n" \
// "OlFuhjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTn\n" \
// "jh8BCNAw1FtxNrQHusEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbw\n" \
// "qHyGO0aoSCqI3Haadr8faqU9GY/rOPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CI\n" \
// "rU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV\n" \
// "HRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY9umbbjANBgkq\n" \
// "hkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL\n" \
// "ubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ\n" \
// "3BebYhtF8GaV0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KK\n" \
// "NFtY2PwByVS5uCbMiogziUwthDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5\n" \
// "ORAzI4JMPJ+GslWYHb4phowim57iaztXOoJwTdwJx4nLCgdNbOhdjsnvzqvHu7Ur\n" \
// "TkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nxe5AW0wdeRlN8NwdC\n" \
// "jNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZAJzVc\n" \
// "oyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq\n" \
// "4RgqsahDYVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPA\n" \
// "mRGunUHBcnWEvgJBQl9nJEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57d\n" \
// "emyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=\n" \
// "-----END CERTIFICATE-----\n"

#define PICOHTTPS_CA_ROOT_CERT \
"-----BEGIN CERTIFICATE-----\n" \
"MIIDhzCCAm+gAwIBAgIUNWFKjUu/NxmnftsKeAyrPhUuHX0wDQYJKoZIhvcNAQEL\n" \
"BQAwUzELMAkGA1UEBhMCU0cxEjAQBgNVBAgMCVNpbmdhcG9yZTEYMBYGA1UECgwP\n" \
"TXkgT3JnYW5pemF0aW9uMRYwFAYDVQQDDA0xOTIuMTY4LjY4LjUxMB4XDTI1MTAx\n" \
"NDA5MzgyMVoXDTI2MTAxNDA5MzgyMVowUzELMAkGA1UEBhMCU0cxEjAQBgNVBAgM\n" \
"CVNpbmdhcG9yZTEYMBYGA1UECgwPTXkgT3JnYW5pemF0aW9uMRYwFAYDVQQDDA0x\n" \
"OTIuMTY4LjY4LjUxMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAj7w7\n" \
"mAsOvc9vAD5Eyxf/NuAOwgQsRKpxcjVk9vmT2cuCLe2+vNEOU9NYMTVVeenbmcOX\n" \
"CX9YK3sjoNF3EKuMTBXEoXLx0anURc7B8DJYzQMj5AdKJ5MdeCF+CzbK14BupHRq\n" \
"vuHE51DK6QJNlLnGJTv+O8SNx6bX1D0mt26xpsOG05eenJfkB4G6BkSUtVsCsZ8E\n" \
"uMcg3KHK3IUVgBofHCYenRuC8izEFie27ReXD99R2haRUSdS5aPnlvbtwFwg8lM2\n" \
"Z7SvF7Nd7l2mZJM8jOHoTryIzou2DZbXiuf+f85zaFpEcCOsPwvdTPegAnyY03bf\n" \
"910m9DK3BAZxk293OwIDAQABo1MwUTAdBgNVHQ4EFgQUTjepmk7MEla77c0dmd2D\n" \
"u4fTY70wHwYDVR0jBBgwFoAUTjepmk7MEla77c0dmd2Du4fTY70wDwYDVR0TAQH/\n" \
"BAUwAwEB/zANBgkqhkiG9w0BAQsFAAOCAQEAJtsmlKs7kGkglpv0sxZDhIHkJL5S\n" \
"AeFKPqyGs5r5ORL+A8UafL5WpiQJRObGvtFhetrRjKaIQnofnwXCMQGQhCOoYskU\n" \
"18ZqIorgjmJDmXJxJVTTZ3l99S7nX9ZFVVmOIbyjhto7U/XlcFMU4VG99k+GndTL\n" \
"0iGNDg+aSCaRcotySDj/QMgaFDMU35dN0bnZiRZicrl/oWB/sKOToWBUrC7WEkYV\n" \
"iau2RU0TFHWqtwJ2JAEAs1pXHX/xBtOCsWBlOzcPfQrp4/PlgB/ACgVVxrWsZRvz\n" \
"782u+qh78kSFqiTMMjgftpfQ/UeHi+c/AQ7vCFhV2qfVCHECaOqJFLj+CA==\n" \
"-----END CERTIFICATE-----\n"






//
//  or
//
//#define PICOHTTPS_CA_ROOT_CERT                                       \
//"-----BEGIN CERTIFICATE-----\n"                                      \
//"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/\n" \
//"-----END CERTIFICATE-----\n"

// TCP + TLS connection establishment polling interval
//
//  Interval with which to poll for establishment of TCP + TLS connection
//
#define PICOHTTPS_ALTCP_CONNECT_POLL_INTERVAL       100             // ms

// TCP + TLS idle connection polling interval
//
//  Interval with which to poll application (i.e. call registered polling
//  callback function) when TCP + TLS connection is idle.
//
//  The callback function should be registered with altcp_poll(). The polling
//  interval is given in units of 'coarse grain timer shots'; one shot
//  corresponds to approximately 500 ms.
//
//  https://www.nongnu.org/lwip/2_1_x/group__altcp.html
//
#define PICOHTTPS_ALTCP_IDLE_POLL_INTERVAL          2               // shots

// HTTP request
//
//  Plain-text HTTP request to send to server
//
#define PICOHTTPS_BODY \
    "{\n" \
    "  \"tokenCode\": \"tokenTest\",\n" \
    "  \"tokenData\": \"This message is sent from Base HQ 2 in Punggol.\"\n" \
    "}"







// HTTP response polling interval
//
//  Interval with which to poll for HTTP response from server.
//
#define PICOHTTPS_HTTP_RESPONSE_POLL_INTERVAL       100             // ms

// Mbed TLS debug levels
//
//  Seemingly not defined in Mbed TLS‽
//
//  https://github.com/Mbed-TLS/mbedtls/blob/62e79dc913325a18b46aaea554a2836a4e6fc94b/include/mbedtls/debug.h#L141
//
#define PICOHTTPS_MBEDTLS_DEBUG_LEVEL               3


/* Macros *********************************************************************/

// Array length
#define LEN(array) (sizeof array)/(sizeof array[0])



/* Data structures ************************************************************/

// lwIP errors
//
//  typedef here to make source of error code more explicit
//
typedef err_t lwip_err_t;

// Mbed TLS errors
//
//  typedef here to make source of error code more explicit
//
typedef int mbedtls_err_t;

// TCP connection callback argument
//
//  All callbacks associated with lwIP TCP (+ TLS) connections can be passed a
//  common argument. This is intended to allow application state to be accessed
//  from within the callback context. The argument should be registered with
//  altcp_arg().
//
//  The following structure is used for this argument in order to supply all
//  the relevant application state required by the various callbacks.
//
//  https://www.nongnu.org/lwip/2_1_x/group__altcp.html
//
struct altcp_callback_arg{

    // TCP + TLS connection configurtaion
    //
    //  Memory allocated to the connection configuration structure needs to be
    //  freed (with altcp_tls_free_config) in the connection error callback
    //  (callback_altcp_err).
    //
    //  https://www.nongnu.org/lwip/2_1_x/group__altcp.html
    //  https://www.nongnu.org/lwip/2_1_x/group__altcp__tls.html
    //
    struct altcp_tls_config* config;

    // TCP + TLS connection state
    //
    //  Successful establishment of a connection needs to be signaled to the
    //  application from the connection connect callback
    //  (callback_altcp_connect).
    //
    //  https://www.nongnu.org/lwip/2_1_x/group__altcp.html
    //
    bool connected;

    // Data reception acknowledgement
    //
    //  The amount of data acknowledged as received by the server needs to be
    //  communicated to the application from the connection sent callback
    //  (callback_altcp_sent) for validatation of successful transmission.
    //
    u16_t acknowledged;

};



/* Functions ******************************************************************/

// Initialise standard I/O over USB
//
//  @return         `true` on success
//
bool init_stdio(void);

// Initialise Pico W wireless hardware
//
//  @return         `true` on success
//
bool init_cyw43(void);

// Connect to wireless network
//
//  @return         `true` on success
//
bool connect_to_network(void);

// Resolve hostname
//
//  @param ipaddr   Pointer to an `ip_addr_t` where the resolved IP address
//                  should be stored.
//
//  @return         `true` on success
//
bool resolve_hostname(ip_addr_t* ipaddr);

// Free TCP + TLS protocol control block
//
//  Memory allocated for a protocol control block (with altcp_tls_new) needs to
//  be freed (with altcp_close).
//
//  @param pcb      Pointer to a `altcp_pcb` structure to be freed
//
void altcp_free_pcb(struct altcp_pcb* pcb);

// Free TCP + TLS connection configuration
//
//  Memory allocated for TCP + TLS connection configuration (with
//  altcp_tls_create_config_client) needs to be freed (with
//  altcp_tls_free_config).
//
//  @param config   Pointer to a `altcp_tls_config` structure to be freed
//
void altcp_free_config(struct altcp_tls_config* config);

// Free TCP + TLS connection callback argument
//
//  The common argument passed to lwIP connection callbacks must remain in
//  scope for the duration of all callback contexts (i.e. connection lifetime).
//  As such, it cannot be declared with function scope when registering the
//  callback, but rather should be allocated on the heap. This implies the
//  allocated memory must be freed on connection close.
//
//  @param arg      Pointer to a `altcp_callback_arg` structure to be freed
//
void altcp_free_arg(struct altcp_callback_arg* arg);

// Establish TCP + TLS connection with server
//
//  @param ipaddr   Pointer to an `ip_addr_t` containing the server's IP
//                  address
//  @param pcb      Double pointer to a `altcp_pcb` structure where the
//                  protocol control block for the established connection
//                  should be stored.
//
//  @return         `true` on success
//
bool connect_to_host(ip_addr_t* ipaddr, struct altcp_pcb** pcb);

// Send HTTP request
//
//  @param pcb      Pointer to a `altcp_pcb` structure containing the TCP + TLS
//                  connection PCB to the server.
//
//  @return         `true` on success
//
bool send_request(struct altcp_pcb* pcb, const char *body);

// DNS response callback
//
//  Callback function fired on DNS query response.
//
//  Registered with dns_gethostbyname().
//
//  https://www.nongnu.org/lwip/2_1_x/group__dns.html
//
void callback_gethostbyname(
    const char* name,
    const ip_addr_t* resolved,
    void* ipaddr
);

// TCP + TLS connection error callback
//
//  Callback function fired on TCP + TLS connection fatal error.
//
//  Registered with altcp_err().
//
//  https://www.nongnu.org/lwip/2_1_x/group__altcp.html
//
void callback_altcp_err(void* arg, lwip_err_t err);

// TCP + TLS connection idle callback
//
//  Callback function fired on idle TCP + TLS connection.
//
//  Registered with altcp_err().
//
//  https://www.nongnu.org/lwip/2_1_x/group__altcp.html
//
lwip_err_t callback_altcp_poll(void* arg, struct altcp_pcb* pcb);

// TCP + TLS data acknowledgement callback
//
//  Callback function fired on acknowledgement of data reception by server over
//  a TCP + TLS connection.
//
//  Registered with altcp_sent().
//
//  https://www.nongnu.org/lwip/2_1_x/group__altcp.html
//
lwip_err_t callback_altcp_sent(void* arg, struct altcp_pcb* pcb, u16_t len);

// TCP + TLS data reception callback
//
//  Callback function fired on reception of data from server over a TCP +
//  TLS connection.
//
//  Registered with altcp_recv().
//
//  https://www.nongnu.org/lwip/2_1_x/group__altcp.html
//
lwip_err_t callback_altcp_recv(
    void* arg,
    struct altcp_pcb* pcb,
    struct pbuf* buf,
    lwip_err_t err
);

// TCP + TLS connection establishment callback
//
//  Callback function fired on successful establishment of TCP + TLS connection.
//
//  Registered with altcp_connect().
//
//  https://www.nongnu.org/lwip/2_1_x/group__altcp.html
//
lwip_err_t callback_altcp_connect(
    void* arg,
    struct altcp_pcb* pcb,
    lwip_err_t err
);



#endif //PICOHTTPS_H
