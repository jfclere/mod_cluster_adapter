#include "ap_config.h"
#include "ap_provider.h"
#include "httpd.h"
#include "http_core.h"
#include "http_config.h"
#include "http_log.h"
#include "http_protocol.h"
#include "http_request.h"

#include "apr_strings.h"

static int mod_cluster_adapter_trans(request_rec *r)
{
    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_DEBUG, 0, r->server,
                "proxy_cluster_trans for %d %s %s uri: %s args: %s unparsed_uri: %s",
                 r->proxyreq, r->filename, r->handler, r->uri, r->args, r->unparsed_uri);
    if (strcmp(r->uri, "/toto") == 0) {
        r->filename =  apr_pstrcat(r->pool, "proxy:balancer://", "mycluster" , r->uri, NULL);
        r->handler = "proxy-server";
        r->proxyreq = PROXYREQ_REVERSE;
        return OK; /* Mod_proxy will process it */
    }
    return DECLINED;
}

static void mod_cluster_adapter_hooks(apr_pool_t *p)
{
   static const char * const aszPre[]={ "mod_manager.c", "mod_rewrite.c", NULL };
   static const char * const aszPre2[] = { "mod_proxy.c", NULL};

   ap_hook_translate_name(mod_cluster_adapter_trans, aszPre, aszPre2, APR_HOOK_MIDDLE);
}

/* Module declaration */

module AP_MODULE_DECLARE_DATA mod_cluster_adapter_module = {
    STANDARD20_MODULE_STUFF,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    mod_cluster_adapter_hooks      /* register hooks */
};
