#include "webui.h"

void my_function_string(webui_event_t* e) {
    const char* str_1 = webui_get_string(e); // Or webui_get_string_at(e, 0);
    const char* str_2 = webui_get_string_at(e, 1);

    printf("my_function_string 1: %s\n", str_1); // Hello
    printf("my_function_string 2: %s\n", str_2); // World
}

void my_function_integer(webui_event_t* e) {
    size_t count = webui_get_count(e);
    printf("my_function_integer: There is %zu arguments in this event\n", count); // 4

    long long number_1 = webui_get_int(e); // Or webui_get_int_at(e, 0);
    long long number_2 = webui_get_int_at(e, 1);
    long long number_3 = webui_get_int_at(e, 2);

    printf("my_function_integer 1: %lld\n", number_1); // 123
    printf("my_function_integer 2: %lld\n", number_2); // 456
    printf("my_function_integer 3: %lld\n", number_3); // 789

    double float_1 = webui_get_float_at(e, 3);

    printf("my_function_integer 4: %f\n", float_1); // 12345.6789
}

void my_function_boolean(webui_event_t* e) {
    bool status_1 = webui_get_bool(e); // Or webui_get_bool_at(e, 0);
    bool status_2 = webui_get_bool_at(e, 1);

    printf("my_function_boolean 1: %s\n", (status_1 ? "True" : "False")); // True
    printf("my_function_boolean 2: %s\n", (status_2 ? "True" : "False")); // False
}

void my_function_raw_binary(webui_event_t* e) {
    const unsigned char* raw_1 = (const unsigned char*)webui_get_string(e); // Or webui_get_string_at(e, 0);
    const unsigned char* raw_2 = (const unsigned char*)webui_get_string_at(e, 1);

    int len_1 = (int)webui_get_size(e); // Or webui_get_size_at(e, 0);
    int len_2 = (int)webui_get_size_at(e, 1);

    // Print raw_1
    printf("my_function_raw_binary 1 (%d bytes): ", len_1);
    for (size_t i = 0; i < len_1; i++)
        printf("0x%02x ", raw_1[i]);
    printf("\n");

    // Check raw_2 (Big)
    // [0xA1, 0x00..., 0xA2]
    bool valid = false;
    if (raw_2[0] == 0xA1 && raw_2[len_2 - 1] == 0xA2)
        valid = true;

    // Print raw_2
    printf("my_function_raw_binary 2 big (%d bytes): valid data? %s\n", len_2, (valid ? "Yes" : "No"));
}

void my_function_with_response(webui_event_t* e) {
    long long number = webui_get_int(e); // Or webui_get_int_at(e, 0);
    long long times = webui_get_int_at(e, 1);

    long long res = number * times;
    printf("my_function_with_response: %lld * %lld = %lld\n", number, times, res);

    // Send back the response to JavaScript
    webui_return_int(e, res);
}

// c -> js 
void my_function_count(webui_event_t* e)
{
    // This function gets called every time the user clicks on "my_function_count"

	// Create a buffer to hold the response
    char response[64]; 
    //run java script 
    if(!webui_script(e->window, "return GetCount();", 0, response, 64)){
        if(!webui_is_shown(e->window))
            printf("Window closed.\n"); 
        else 
            printf("JavaScript Error: %s\n", response); 
        return; 
    }

    // get the count 
    int count = atoi(response); 

    // Increment 
    count++; 

    // Generate a javascript 
    char js[64]; 
    sprintf(js, "SetCount(%d);", count); 

    //run javaScript(Quick Way)
    webui_run(e->window, js); 
}

int main() {
    // Create a window
    size_t my_window = webui_new_window();

    // Bind HTML elements with C functions
    webui_bind(my_window, "my_function_string", my_function_string);
    webui_bind(my_window, "my_function_integer", my_function_integer);
    webui_bind(my_window, "my_function_boolean", my_function_boolean);
    webui_bind(my_window, "my_function_with_response", my_function_with_response);
    webui_bind(my_window, "my_function_raw_binary", my_function_raw_binary);
    webui_bind(my_window, "my_function_count", my_function_count); 
    // Show the window
    webui_show(my_window, "index.html"); // webui_show_browser(my_window, "index.html", Chrome);

    // Wait until all windows get closed
    webui_wait();

    // Free all memory resources (Optional)
    webui_clean();

    return 0;
}

#if defined(_MSC_VER)
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) { return main(); }
#endif
