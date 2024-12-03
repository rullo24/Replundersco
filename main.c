#include <windows.h>
#include <stdio.h>
#include <stdbool.h>

#define USER_INPUT_MAX 255

int copy_to_win_clipboard(const char *text) {
    int res = 0;
    bool cb_used = false;

    if (!OpenClipboard(NULL)) {
        fprintf(stderr, "ERROR: OpenClipboard()\n");
        res = -1;
        goto out;
    }
    cb_used = true; // setting clipboard used var for cleanup on func exit

    // clear current clipboard content
    EmptyClipboard();

    // calc size of text (inc. \0)
    size_t text_len = strlen(text) + 1; // presume text is NULL terminated as it comes from fgets call
    HGLOBAL h_global = GlobalAlloc(GMEM_MOVEABLE, text_len);
    if (h_global == NULL) {
        fprintf(stderr, "ERROR: GlobalAlloc()\n");
        res = -2;
        goto out;
    }

    // copy text into allocated mem
    char *p_clipboard_data = (char*)GlobalLock(h_global);
    memcpy(p_clipboard_data, text, text_len);
    GlobalUnlock(h_global);

    // set clipboard data
    if (SetClipboardData(CF_TEXT, h_global) == NULL) {
        fprintf(stderr, "ERROR: SetClipboardData()\n");
        res = -3;
        goto out;
    }

out:
    if (cb_used) {
        CloseClipboard();
    }
    return res;
}

// presume string is NULL terminated as it comes from fgets
int replace_all_spaces_with_underscore(char *text, size_t text_size) {
    // iterating over each char in the string
    for (size_t i=0; i < text_size; i++) {
        if (text[i] == ' ') {
            text[i] = '_';
        }
    }
    
    return 0;
}

int main(int argc, char *argv[]) {
    (void)argv; // touching var to avoid warning
    if (argc > 1) {
        fprintf(stderr, "ERROR: Arguments provided.\nUse: ./replundersco\n");
        return -1;
    }
    char usr_input_buf[USER_INPUT_MAX]; // to capture string to transfer

    // getting user input
    printf("String to Conv: ");
    char *usr_resp = fgets(usr_input_buf, sizeof(usr_input_buf), stdin);
    if (usr_resp == NULL) { // checking for failed fgets
        fprintf(stderr, "ERROR: fgets()\n");
        return -2;
    }
    
    // replacing all spaces with underscore in the user string provided
    size_t usr_text_size = strlen(usr_input_buf);
    int repl_resp = replace_all_spaces_with_underscore(usr_input_buf, usr_text_size);
    if (repl_resp < 0) { // error messages always printed from within func
        return -3;
    }

    // copying the user data to the clipboard
    int cb_copy_res = copy_to_win_clipboard(usr_input_buf);
    if (cb_copy_res < 0) { // error message printed from within the func
        return -4;
    }

    return 0;
}
