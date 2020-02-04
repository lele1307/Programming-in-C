#define MAXNUMTOKENS 500
#define MAXTOKENSIZE 400
#define STR 1000
#define ROTC 13
#define ROTD 5
#define IFCON 2
#define CON1 0
#define CON2 1
#define EPSILON 0.000001

#define strsame(A,B) (strcmp(A,B)==0)
#define strdiff(A,B) (strcmp(A,B)!=0)
#define ERROR(PHRASE) fprintf(stderr,"Fatal Error %s occured in %s, line %d\n",PHRASE,__FILE__,__LINE__);
#define FREE_STR(P) free(P);
#define FREE(P){Progarr_free(P);exit(EXIT_SUCCESS);}
#define ABORT(STR) fprintf(stderr, STR); exit(EXIT_SUCCESS)

enum bool{false,true};
typedef enum bool bool;
struct val
{
    char name[STR];
    char val[STR];
    int num;
};
typedef struct val VAL;
struct prog
{
    char **wds;
    int cw;/* currunt words */
    int num;/* wds num */

    VAL arr[STR];
    int arrnum;

    char con[IFCON][STR];
    int ifposition;
    double numcon[IFCON];
    char strcon[IFCON][STR];
    int which; /* if which = -1, double set  if which = 1, str set*/

    int file;

    int loop;
    int looposition;
};
typedef struct prog Program;
struct progarr
{
    Program *p[STR];
    int num; /* index of progarr */
};
typedef struct progarr ProgramArr;

/* Parse & Interp Struct Function */
Program *init_P(void);
void prog_free(Program **p);
void Progarr_free(ProgramArr prog);
void printSTRUCT(Program *prog);
void InputFile(char *str,Program *prog,ProgramArr progarr);
void PROG(Program *p,ProgramArr progarr);
void INSTRS(Program *p,ProgramArr progarr);
void INSTRUCT(Program *p,ProgramArr progarr);

/* Parse Function */
void INC_RND(Program *p,ProgramArr progarr);
void SET(Program *p,ProgramArr progarr);
void IF(Program *p,ProgramArr progarr);
void IN2STR(Program *p,ProgramArr progarr);
void VARCON(Program *p,ProgramArr progarr);
void CON(Program *p,ProgramArr progarr);
void STRCON(Program *p,ProgramArr progarr);
void NUMCON(Program *p,ProgramArr progarr);
void NUMVAR_STRVAR(Program *p,ProgramArr progarr);

/* Interp Function */
int TEST_SAMEVALNAME(Program *p,char *str);
char *Getname(char *rawstr);
char *GetSTRCON(char *str);
char *ROT(char *str);

void PRINT(Program *p,ProgramArr progarr);
void PRINT_Plain(char *rawstr,ProgramArr progarr);
void PRINT_ROT13(char *rawstr,ProgramArr progarr);

void JUMP(Program *p);

void READFILE(Program *p,ProgramArr prog);
void CopyVal(Program *p,Program *newfile);

void RND(Program *p,ProgramArr progarr);
void INC(Program *p,ProgramArr progarr);
void SETNUM(Program *p,ProgramArr progarr);
void SETSTR(Program *p,ProgramArr progarr);
void INNUM(Program *p);
void IN2STR_IN(Program *p);
void IN2STR_IN_Single(Program *p);

void IF_RECORD(Program *p);
void IFCOND(Program *p,ProgramArr progarr);
void IF_CHECK(Program *p,ProgramArr progarr);
void IF_SET(Program *p,ProgramArr progarr);
void IFGREATER(Program *p,ProgramArr progarr);
void IFEQUAL(Program *p,ProgramArr progarr);

