#define MAXNUMTOKENS 500
#define MAXTOKENSIZE 400
#define strsame(A,B) (strcmp(A,B)==0)
#define strdiff(A,B) (strcmp(A,B)!=0)
#define ERROR(PHRASE) {fprintf(stderr,"Fatal Error:%s occured in %s,line %d\n",PHRASE,__FILE__,__LINE__);}
#define FREE(P){prog_free(&P);exit(EXIT_SUCCESS);}
#define ON_ERROR(STR) fprintf(stderr, STR); exit(EXIT_FAILURE)
struct prog
{
    char **wds;
    int cw;/* currunt words */
    int num;
};
typedef struct prog Program;

void testprint(Program *prog);
void test(void);
void testInputFile(Program *prog);

Program *init_P(void);
void prog_free(Program **p);
void InputFile(char *str,Program *prog);

void PROG(Program *p);
void INSTRS(Program *p);
void INSTRUCT(Program *p);

void INC_RND(Program *p);
void SET(Program *p);
void IF(Program *p);
void IN2STR(Program *p);
void VARCON(Program *p);
void CON(Program *p);
void STRCON(Program *p);
void NUMCON(Program *p);
void NUMVAR_STRVAR(Program *p);


