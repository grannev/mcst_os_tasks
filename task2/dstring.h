

typedef struct {
    int size;
    char *buffer;
} dstr;


void init_dstr(dstr *this);
void cstr_dstr(dstr *this, const char *cstring);
void expand_dstr(dstr *this, int count);

int len_cstr(const char *cstring);
int cmp_cstr(const char *cstr_left, const char *cstr_right);
void clr_cstr(char *cstring);
int find_symb_cstr(const char *cstring, char ch);
    
