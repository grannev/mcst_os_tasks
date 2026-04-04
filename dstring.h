

/* dynamic string */
typedef struct {
    int size;
    char *buffer;
} dstr;

/* initialize dstring with NULL for buffer and 0 for size */
void init_dstr(dstr *this);

/* turn cstring to dstring */
void cstr_dstr(dstr *this, const char *cstring);

/* expand memory for buffer by some value */
void expand_dstr(dstr *this, int count);

/* return len of cstring */
int len_cstr(const char *cstring);

/* compare two cstring, return 1 if every char equals another */
int cmp_cstr(const char *cstr_left, const char *cstr_right);

/* set every char to 0 byte until get to 0 byte of cstring */
void clr_cstr(char *cstring);

/* return index of char in cstring */
int find_symb_cstr(const char *cstring, char ch);

/* count specified char in cstring */
int cnt_char_cstr(const char *cstring, char ch);

