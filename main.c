// WebUI C - Minimal Example

#include "webui.h"
#include "myLog.h"


//#define printf log_to_file

#define MyWindow 	(1)
#define MySecondWindow  (2)

void exit_app(webui_event_t* e)
{
	// close all opened windows
	webui_exit(); 
}

const void* filesHandler(const char* filename, int* length)
{
    printf("filesHandler\n");
    return NULL;  
}

void my_function_with_response(webui_event_t* e)
{
    //// JavaScript:
	// my_function_with_response(number, 2).then(...)

	long long number = webui_get_int(e); // Or webui_get_int_at(e, 0);
	long long times = webui_get_int_at(e, 1);

	long long res = number * times;
	printf("my_function_with_response: %lld * %lld = %lld\n", number, times, res);

	// Send back the response to JavaScript
	webui_return_int(e, res);
}

void my_function_string(webui_event_t* e)
{
    //JavaScript
    //my_function_string('Hello', 'World'); 
    const char* str_1 = webui_get_string(e); // Or webui_get_string_at(e, 0);
    const char* str_2 = webui_get_string_at(e, 1);

    printf("my_function_string 1: %s\n", str_1); // Hello
	printf("my_function_string 2: %s\n", str_2); // World

}



void events(webui_event_t* e) {

    // This function gets called every time
    // there is an event
    printf("events. \n");

    if (e->event_type == WEBUI_EVENT_CONNECTED)
        printf("Connected. \n");
    else if (e->event_type == WEBUI_EVENT_DISCONNECTED)
        printf("Disconnected. \n");
    else if (e->event_type == WEBUI_EVENT_MOUSE_CLICK)
        printf("Click. \n");
    else if (e->event_type == WEBUI_EVENT_NAVIGATION) {
        const char* url = webui_get_string(e);
        printf("Starting navigation to: %s \n", url);

        // Because we used `webui_bind(MyWindow, "", events);`
        // WebUI will block all `href` link clicks and sent here instead.
        // We can then control the behaviour of links as needed.
        webui_navigate(e->window, url);
    }
}



int main() {
    initialize_log_file();
     // Redirect stdout and stderr to the console
   
	// create new window 
	webui_new_window_id(MyWindow); 
    printf("start. \n");
	//bind html element ids with a c function 
	webui_bind(MyWindow, "Exit", exit_app); 

	//bind events 
	webui_bind(MyWindow, "", events); 
    webui_bind(MyWindow, "my_function_with_response", my_function_with_response);
	// Set the `.ts` and `.js` runtime
    webui_set_runtime(MyWindow, Deno);
   
     // Set a custom files handler
    webui_set_file_handler(MyWindow, filesHandler);

    // Set window size
    webui_set_size(MyWindow, 800, 800);

    // Set window position
    webui_set_position(MyWindow, 200, 200);

    // Show a new window
    // webui_set_root_folder(MyWindow, "_MY_PATH_HERE_");
    // webui_show_browser(MyWindow, "index.html", Chrome);
    webui_show(MyWindow, "index.html");
    
    
    // Wait until all windows get closed
    webui_wait();

    // Free all memory resources (Optional)
    webui_clean();

	return 0;
}

#if defined(_MSC_VER)
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) { return main(); }
#endif
