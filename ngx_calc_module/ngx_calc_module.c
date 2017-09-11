#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h> 

static char *ngx_calc(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);

static ngx_command_t ngx_calc_commands[] = {
	{
		ngx_string("calc"),
		NGX_HTTP_LOC_CONF | NGX_CONF_NOARGS,
		ngx_calc,
		0,
		0,
		NULL
	},

	ngx_null_command
};

static ngx_http_module_t ngx_calc_module_ctx = {
	NULL,
	NULL,

	NULL,
	NULL,

	NULL,
	NULL,

	NULL,
	NULL
};

ngx_module_t ngx_calc_module = {
	NGX_MODULE_V1,
	&ngx_calc_module_ctx,
	ngx_calc_commands,
	NGX_HTTP_MODULE,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NGX_MODULE_V1_PADDING
};

static ngx_str_t ngx_calc_type = ngx_string("text/plain");

static ngx_int_t ngx_calc_handler(ngx_http_request_t *r) {
	ngx_http_complex_value_t cv;

	if (!(r->method & (NGX_HTTP_GET | NGX_HTTP_HEAD))) {
		return NGX_HTTP_NOT_ALLOWED;
	}

	ngx_memzero(&cv, sizeof(ngx_http_complex_value_t));

	ngx_str_set(&cv.value, "this is calc module program!");


	return ngx_http_send_response(r, NGX_HTTP_OK, &ngx_calc_type, &cv);
}

static char * ngx_calc(ngx_conf_t *cf, ngx_command_t *cmd, void *conf) {
	ngx_http_core_loc_conf_t *clcf;

	clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
	clcf->handler = ngx_calc_handler;

	return NGX_CONF_OK;
}
