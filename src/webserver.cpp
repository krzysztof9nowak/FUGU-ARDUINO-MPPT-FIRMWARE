#include <webserver.h>
#include <variables.h>





esp_err_t index_handler(httpd_req_t *req)
{
    const char resp[] = "URI GET Response";
    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}


#define JSON_BEGIN(ptr) *(ptr++) = '{'
#define JSON_END(ptr) *(ptr++) = '}'; *(ptr++) = '\0'
#define JSON_INT(ptr, name, val) ptr += sprintf(ptr, "\"%s\":%d", name, val)
#define JSON_FLOAT(ptr, name, val, prec) ptr += sprintf(ptr, "\"%s\":%." #prec "f", name, val)
#define JSON_COMMA(ptr) *(ptr++) = ','
esp_err_t status_handler(httpd_req_t *req)
{
    char resp[2048] = "";
    char *ptr = resp;

    JSON_BEGIN(ptr);
    JSON_INT(ptr, "Hello", 123); JSON_COMMA(ptr);
    JSON_FLOAT(ptr, "time", 45.1234567, 3);
    JSON_END(ptr);

    httpd_resp_set_type(req, "application/json");
    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

httpd_uri_t uri_index = {
    .uri      = "/",
    .method   = HTTP_GET,
    .handler  = index_handler,
    .user_ctx = NULL
};

httpd_uri_t uri_status = {
    .uri      = "/status",
    .method   = HTTP_GET,
    .handler  = status_handler,
    .user_ctx = NULL
};

httpd_handle_t start_webserver(void)
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t server = NULL;

    if (httpd_start(&server, &config) == ESP_OK) {
        httpd_register_uri_handler(server, &uri_index);
        httpd_register_uri_handler(server, &uri_status);
    }

    return server;
}
