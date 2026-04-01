

typedef struct {
    int size;
    char *buffer;
} dstr;


void init_dstr(dstr *this);
void cstr_dstr(dstr *this, const char *cstring);
void expand_dstr(dstr *this, int count);

int len_cstr(const char *cstring);
int cmp_cstr(const char *cstring);

