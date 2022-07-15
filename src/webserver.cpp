#include <webserver.h>
#include <variables.h>
#include <webpage_index.h>
#include <esp_log.h>

static const char* TAG = "webserver";


esp_err_t index_handler(httpd_req_t *req)
{
    httpd_resp_send(req, (char*)pages_webpage_index_html, pages_webpage_index_html_len);
    return ESP_OK;
}

#define JSON_BEGIN(ptr) *(ptr++) = '{'
#define JSON_END(ptr) *(ptr++) = '}'; *(ptr++) = '\0'
#define JSON_INT(ptr, name, val) ptr += sprintf(ptr, "\"%s\":%d", name, val)
#define JSON_FLOAT(ptr, name, val, prec) ptr += sprintf(ptr, "\"%s\":%." #prec "f", name, val)
#define JSON_COMMA(ptr) *(ptr++) = ','
esp_err_t status_handler(httpd_req_t *req)
{
    char resp[512] = "";
    char *ptr = resp;

    JSON_BEGIN(ptr);
    JSON_INT(ptr, "err", (int)err); JSON_COMMA(ptr);
    JSON_FLOAT(ptr, "power", powerInput, 1); JSON_COMMA(ptr);
    JSON_FLOAT(ptr, "voltageInput", voltageInput, 1); JSON_COMMA(ptr);
    JSON_FLOAT(ptr, "voltageOutput", voltageOutput, 1); JSON_COMMA(ptr);
    JSON_FLOAT(ptr, "currentInput", currentInput, 1); JSON_COMMA(ptr);
    JSON_FLOAT(ptr, "currentOutput", currentOutput, 1); JSON_COMMA(ptr);
    JSON_FLOAT(ptr, "energy", energy_wh, 1); JSON_COMMA(ptr);
    JSON_INT(ptr, "temperature", temperature); JSON_COMMA(ptr);
    JSON_INT(ptr, "paused", chargingPause);
    JSON_END(ptr);

    httpd_resp_set_type(req, "application/json");
    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

esp_err_t buttons_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "buttons POST handler");

    char content[100];

    // truncate if header too long
    size_t recv_size = req->content_len;
    if(recv_size > sizeof(content)) recv_size = sizeof(content);

    int ret = httpd_req_recv(req, content, recv_size);
    if (ret <= 0) {
        if (ret == HTTPD_SOCK_ERR_TIMEOUT) {
            httpd_resp_send_408(req);
        }
        return ESP_FAIL;
    }

    ESP_LOGI(TAG, "POST data: %s", content);
    if(strcmp(content, "action=stop") == 0){
        ESP_LOGI(TAG, "pausing charging");
        chargingPause = true;
    } else if(strcmp(content, "action=start") == 0){
        ESP_LOGI(TAG, "unpausing charging");
        chargingPause = false;
    }

    return index_handler(req);
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

httpd_uri_t uri_buttons = {
    .uri      = "/",
    .method   = HTTP_POST,
    .handler  = buttons_handler,
    .user_ctx = NULL
};


httpd_handle_t start_webserver(void)
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t server = NULL;

    if (httpd_start(&server, &config) == ESP_OK) {
        httpd_register_uri_handler(server, &uri_index);
        httpd_register_uri_handler(server, &uri_status);
        httpd_register_uri_handler(server, &uri_buttons);
    }

    return server;
}
