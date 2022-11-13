// Libraries 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

// Struct declarations 
typedef struct projectTasks projectTasks;
typedef struct projectTasksList projectTasksList;
typedef struct taskDocuments taskDocuments; 
typedef struct projectResources projectResources;
typedef struct treeNode treeNode;
typedef struct vertex vertex;
typedef struct edge edge;
typedef struct AdjList AdjList;
//typedef struct 


// struct
struct projectTasks{
	char IdTask[6];
	char description[100];
	char typeTask;
	int effort; 
	int time; 
	char manager[100];
	projectTasks *next;
};

struct projectTasksList{
	projectTasks *first;
};

struct taskDocuments{
	char IDocuments[6];
	char filePath[100];
	char description[100];
	char type[100];
};

struct projectResources{
	char idResource[6];
	char nameResource[100];
	char typeResource[100];
	char resourceCapacity[50];
	int availableQuantity;
	char manager[100];
};

struct treeNode{
	int key;
	struct taskDocuments *taskDocuments;
	struct treeNode *right;
	struct treeNode *left;
};

struct vertex
{
    projectTasks *projectTasks;
    vertex *next;
    edge *ad;
    int visited, finished;
    int amount;
    int *ant;
};

struct edge
{
    vertex *vrt;
    edge *next;
    int time; /// peso
    int effort;

};

struct AdjList
{
    projectTasks *projectTasks;
    AdjList *next;
};

vertex *headAdj = NULL;
AdjList *ini = NULL;
AdjList *finale = NULL;
 

////////// GRAF  ////////// 
projectTasks *createProjectTasks(){
	
	projectTasks projectTasksT;
	
	printf("\nEnter the task ID:");
	scanf("%s", &projectTasksT.IdTask);
	printf("\nEnter the task description:");
	scanf("%s", &projectTasksT.description);
	printf("\nEnter the type of task:");
	printf("\n-----TYPES---- \n    1.Operational Task \n    2.Approval Task \n    3.Contract Signing \n    4.Management Task \n    5.Changes \n    TYPE: ");
	scanf("%s", &projectTasksT.typeTask);
	printf("\nEnter the task effort:");
	scanf("%s", &projectTasksT.effort);
	printf("\nEnter the time required for the task:");
	scanf("%s", &projectTasksT.time);
	printf("\nEnter the task ID:");
	scanf("%s", &projectTasksT.manager);
	//insertardatospos 
	
}


void insertVertex(projectTasks *projectTasksT)
{
    vertex *aux;
    vertex *novus = (vertex *)malloc(sizeof(vertex));
    system("cls");

    novus->projectTasks = projectTasksT;

    novus->next = NULL;
    novus->ad = NULL;
    novus->visited = novus->finished = 0;
    novus->amount = -1;
    novus->ant = 0;
    if (headAdj == NULL)
    {
        headAdj = novus;
    }
    else
    {
        aux = headAdj;
        while (aux->next != NULL)
        {
            aux = aux->next;
        }
        aux->next = novus;
    }
}
/*
void createEdge(treeNode *treeRoot, cyberAttackTypeList *catl, Pila *P)
{
    int ini;
    int fin;
    const char *src;
    edge *novus = (edge *)malloc(sizeof(edge));
    novus->next = NULL;
    vertex *aux;
    vertex *aux2;
    system("cls");

    printf("\nSelect the attacking country. ");
    ini = chooseNacionalityCounter(treeRoot, LtCriminal, catl, P)->ID;

    printf("\nSelect the Attacked country. ");
    fin = chooseNacionalityCounter(treeRoot, LtCriminal, catl, P)->ID;

    printf("\nDuration of attack in seconds: ");
    scanf("%i", &novus->seconds);
    printf("\nAmount of gygabites affected: ");
    scanf("%i", &novus->gb);
    printf("\n");
    novus->attackType = chooseCyberAttackTypeCounter(treeRoot, LtCriminal, catl, P)->name;

    cyberAttackType *gg = catl->first;
    for (gg = catl->first; gg != NULL; gg = gg->next)
    {
        if (strcmp(novus->attackType, gg->name) == 0)
        {
            gg->deletable = 0;
        }
    }

    printf("\n");
    novus->cyberCriminal = chooseCyberCriminalCounter(treeRoot, LtCriminal, catl, P)->organization;
    printf("\n");

    aux = headAdj;
    aux2 = headAdj;

    while (aux2 != NULL)
    {
        if (aux2->country->ID == fin)
        {
            break;
        }
        aux2 = aux2->next;
    }

    while (aux != NULL)
    {
        if (aux->country->ID == ini)
        {
            novus->attacker = aux->country->name;
            novus->attacked = aux2->country->name;
            addEdge(aux, aux2, novus);
            totalAttacks++;
            system("cls");
            printf("\nAttack registered successfully\n");
            sleep(1);
            cyberAttackMenu(treeRoot, LtCriminal, catl, P);
        }
        aux = aux->next;
    }
}

void addEdge(vertex *aux, vertex *aux2, edge *novus)
{
    edge *a;
    if (aux->ad == NULL)
    {
        aux->ad = novus;
        novus->vrt = aux2;
    }
    else
    {
        a = aux->ad;
        while (a->next != NULL)
        {
            a = a->next;
        }
        novus->vrt = aux2;
        a->next = novus;
    }
}

void showGraph(treeNode *treeRoot, listCriminal *LtCriminal, cyberAttackTypeList *catl, Pila *P)
{
    system("cls");
    vertex *aux = headAdj;
    edge *ed;
    printf("GRAPH\n");
    printf("----------\n");
    while (aux != NULL)
    {
        printf("%s--> ", aux->country->name);
        if (aux->ad != NULL)
        {
            ed = aux->ad;
            while (ed != NULL)
            {
                printf("%s", ed->vrt->country->name);
                printf("[%s,", ed->attackType);
                printf(" %s,", ed->cyberCriminal);
                printf(" %igb,", ed->gb);
                printf(" %is]  ", ed->seconds);
                ed = ed->next;
            }
        }
        printf("\n");
        aux = aux->next;
    }
    printf("\n");
    char nothing[100];
    printf("\n<Press any key to return>\n");
    fflush(stdin);
    gets(nothing);
    cyberAttackMenu(treeRoot, LtCriminal, catl, P);
}

void modifyGraph(treeNode *treeRoot, listCriminal *LtCriminal, cyberAttackTypeList *catl, vertex *pv, edge *ar)
{
    int option;
    int x;
    vertex *y = headAdj;
    system("cls");
    printf("%s --> %s\n", pv->country->name, ar->vrt->country->name);
    printf("---------------\n");
    printf("1. Attack duration: %i seconds\n", ar->seconds);
    printf("2. Gb affected: %i\n", ar->gb);
    printf("3. Attack type: %s\n", ar->attackType);
    printf("4. Criminal: %s\n", ar->cyberCriminal);
    printf("5. Attacked country\n");
    printf("6. Attacking country\n");
    printf("7. Go back\n");

    printf("Number to modify: ");
    fflush(stdin);
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        system("cls");
        printf("Enter new duration:\n");
        scanf("%d", &x);
        ar->seconds = x;
        system("cls");
        printf("\nData updated\n");
        sleep(1);
        modifyGraph(treeRoot, LtCriminal, catl, pv, ar, P);
        break;

    case 2:
        system("cls");
        printf("Enter Gb:\n");
        scanf("%d", &x);
        ar->gb = x;
        system("cls");
        printf("\nData updated\n");
        sleep(1);
        modifyGraph(treeRoot, LtCriminal, catl, pv, ar, P);
        break;

    case 3:
        system("cls");
        ar->attackType = chooseCyberAttackType(treeRoot, LtCriminal, catl, P)->name;
        system("cls");
        printf("\nData updated\n");
        sleep(1);
        modifyGraph(treeRoot, LtCriminal, catl, pv, ar, P);
        break;

    case 4:
        system("cls");
        ar->cyberCriminal = chooseCyberCriminal(treeRoot, LtCriminal, catl, P)->organization;
        system("cls");
        printf("\nData updated\n");
        sleep(1);
        modifyGraph(treeRoot, LtCriminal, catl, pv, ar, P);
        break;

    case 5:
        system("cls");
        printf("\nSelect the new Attacked country. ");
        x = chooseNacionality(treeRoot, LtCriminal, catl, P)->ID;
        while (y != NULL)
        {
            if (y->country->ID == x)
            {
                break;
            }
            y = y->next;
        }
        ar->vrt = y;
        printf("\nData updated\n");
        sleep(1);
        modifyGraph(treeRoot, LtCriminal, catl, pv, ar, P);
        break;

    case 6:
        system("cls");
        vertex *r = pv;
        vertex *t = headAdj;
        int id;
        vertex *q;
        edge *x = ar;
        edge *y;
        edge *m;

        printf("\nSelect the new Attacking country. ");
        id = chooseNacionality(treeRoot, LtCriminal, catl, P)->ID;

        if (r->ad == x)
        {
            r->ad = x->next;
            x->next = NULL;
            while (t != NULL)
            {
                if (t->country->ID == id)
                {
                    q = t;
                    break;
                }
                t = t->next;
            }
        }

        else
        {
            y = r->ad;
            while (y->next != x)
            {
                y = y->next;
            }
            y->next = x->next;
            x->next = NULL;
            fflush(stdin);
            while (t != NULL)
            {
                if (t->country->ID == id)
                {
                    q = t;
                    break;
                }
                t = t->next;
            }
        }

        if (q->ad == NULL)
        {
            q->ad = x;
        }
        else
        {
            m = q->ad;
            while (m->next != NULL)
            {
                m = m->next;
            }
            m->next = x;
        }

        printf("\nData updated\n");
        sleep(1);
        cyberAttackMenu(treeRoot, LtCriminal, catl, P);
        break;

    case 7:
        cyberAttackMenu(treeRoot, LtCriminal, catl, P);
        break;

    default:
        system("cls");
        printf("\n\nInvalid input.\n");
        sleep(2);
        modifyGraph(treeRoot, LtCriminal, catl, pv, ar, P);
    }
}

void updateGraph(treeNode *treeRoot, listCriminal *LtCriminal, cyberAttackTypeList *catl, Pila *P)
{
    system("cls");
    vertex *pv = headAdj;
    vertex *pp = headAdj;
    vertex *xx;
    edge *ar;
    edge *qq;
    int id;
    int id2;

    printf("\nSelect the attacking country. ");
    id = chooseNacionality(treeRoot, LtCriminal, catl, P)->ID;
    fflush(stdin);
    while (pp != NULL)
    {
        if (pp->country->ID == id)
        {
            if (pp->ad == NULL)
            {
                printf("\n*This country has not carried out attacks*");
                sleep(2);
                cyberAttackMenu(treeRoot, LtCriminal, catl, P);
            }
            break;
        }
        pp = pp->next;
    }
    system("cls");
    printf("\nSelect the Attacked country. ");
    id2 = chooseNacionality(treeRoot, LtCriminal, catl, P)->ID;
    pp = headAdj;
    while (pp != NULL)
    {
        if (pp->country->ID == id)
        {
            qq = pp->ad;
            while (qq != NULL)
            {
                if (qq->vrt->country->ID == id2)
                {
                    break;
                }
                qq = qq->next;
            }
        }
        pp = pp->next;
    }
    if (qq == NULL)
    {
        printf("\n*The attacker has not hit this country*");
        sleep(2);
        updateGraph(treeRoot, LtCriminal, catl, P);
    }

    system("cls");

    while (pv != NULL)
    {
        if (pv->country->ID == id)
        {
            break;
        }
        pv = pv->next;
    }
    ar = pv->ad;
    while (ar != NULL)
    {
        if (ar->vrt->country->ID == id2)
        {
            modifyGraph(treeRoot, LtCriminal, catl, pv, ar, P);
        }
        ar = ar->next;
    }
}

void reboot()
{
    if (headAdj != NULL)
    {
        vertex *aux = headAdj;
        while (aux != NULL)
        {
            aux->visited = aux->finished = 0;
            aux = aux->next;
        }
    }
}*/

int main(){
	
	createProjectTasks();
}
