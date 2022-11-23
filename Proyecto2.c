// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <conio.h>


// Struct 
typedef struct projectTasks projectTasks;
typedef struct treeNode treeNode;
typedef struct vertex vertex;
typedef struct edge edge;
typedef struct projectTasksList projectTasksList;
typedef struct treeNode treeNode;
typedef struct documents documents;
typedef struct resources resources;
typedef struct listResources listResources;

struct projectTasks{
	char *IDTask;
	char *description;
	char *typeTask;
	char *effort; 
	char *time; 
	char *manager;
	projectTasks *next;
};

struct edge
{
    vertex *vrt;
    edge *next;
    int time; 
    int effort;

};

struct vertex
{
    projectTasks *projectTasks;
    vertex *next;
    edge *adj;
    int visited, finished;
    int amount;
    char *previous;
};

struct projectTasksList{
	projectTasks *projectTasks;
	projectTasksList *next;
 };

struct documents
{
    char *IDTask; 
	int *IDocumen;
    char *filePath;
    char *description;
    char *typeD;
    int *deletable;
};

struct treeNode
{
    int key;
    struct documents *documents;
    struct treeNode *right;
    struct treeNode *left;
};

struct resources{
	char ID[10];
	char name[100];
	char type[100];
	char capacity[100];
	char amount[100];
	char manager[100];
	resources *next;
};

struct listResources{
	resources *head;
};

projectTasksList *str = NULL;
projectTasksList *end = NULL;
vertex *start = NULL;


char *mystrcpy(char *dst, const char *src)
{
    char *ptr = dst;
    while ((*dst++ = *src++))
        ;
    return ptr;
}
//------------------------------------------------------ /RESOURCES/ ------------------------------------------------------
listResources *listNew(void)
{
	listResources *Ltr;
	Ltr = (listResources *) malloc(sizeof(listResources));
	Ltr->head = NULL;
	return Ltr;
}

resources* createNode(resources dataR)
{
	resources *novus;
	novus = (resources *) malloc(sizeof(resources));
	*novus = dataR;
	novus->next = NULL;	
	
	return novus;
}

void insertDataR(listResources *Ltr, resources dataR)
{
	resources *novus = createNode(dataR);
	resources *n, *aux;
	
	if(Ltr->head == NULL) 
	{
		Ltr->head = novus;
		return;
	}
	else{
		n = Ltr->head;
		while(n != NULL){
			aux = n;
			n = n->next;
		}
	}
	aux->next = novus;
}

void addResources(listResources *Ltr){
	
	system("cls");
	resources dataR;
	
	printf("ID: ");
	scanf("%s", &dataR.ID);
	printf("\nName resource: ");
	scanf("%s", &dataR.name);
	printf("\nType: \nHumans \nMaterials \nFinancial \nTime \nEtc: ");
	scanf("%s", &dataR.type);
	printf("\nCapaticy: \nMonthly \nJournal \nHours: ");
	scanf("%s", &dataR.capacity);
	printf("\nAvailable quantity: ");
	scanf("%s", &dataR.amount);
	printf("\nManager: ");
	scanf("%s", &dataR.manager);
	
	insertDataR(Ltr, dataR);
	printf("\n [ Successfully registered resource ]\n");
	getch();

}

void showResources(listResources *Ltr) 
{
	system("cls");
	resources *i;
	if(Ltr->head == NULL)
		printf("[ No resources found ]\n");
	else{
		printf("Resources: \n \n");
		for(i = Ltr->head; i!= NULL; i = i->next)
		{
			printf("ID Resource: %s \n", i->ID);
			printf("Name: %s \n", i->name);
			printf("Type: %s \n", i->type);
			printf("Capacity: %s \n", i->capacity);
			printf("Avaible quantify: %s \n", i->amount);
			printf("Manager: %s \n", i->manager);		
			printf("\n");
		}
	}
	getch();
}

//------------------------------------------------------ /GRAPH/ ------------------------------------------------------

void insertVertex(projectTasks *projectTasksT)
{
    vertex *aux;
    vertex *newVar = (vertex *)malloc(sizeof(vertex));
    system("cls");

    newVar->projectTasks = projectTasksT;

    newVar->next = NULL;
    newVar->adj = NULL;
    newVar->visited = newVar->finished = 0;
    newVar->amount = -1;
    newVar->previous = 0;	
    
    if (start == NULL)
    {
        start = newVar;
    }
    else
    {
        aux = start;
        while (aux->next != NULL)
        {
            aux = aux->next;
        }
        aux->next = newVar;
    }
}
// create and add edge the graph

void addEdge(vertex *aux, vertex *aux2, edge *newVar)
{
    edge *a;
    if (aux->adj == NULL)
    {
        aux->adj = newVar;
        newVar->vrt = aux2;
    }
    else
    {
        a = aux->adj;
        while (a->next != NULL)
        {
            a = a->next;
        }
        newVar->vrt = aux2;
        a->next = newVar;
    }
}
void showOnlyTasks()
{
    vertex *aux = start;
	while (aux != NULL)
    {
        printf("ID: %s \n", aux->projectTasks->IDTask);
        aux = aux->next;
    }
    printf ("\n [ ENTER ] \n");
    getch();
	
}

int taskExist(char *temTask){
	vertex *aux = start;
	
	while(aux != NULL){
		if(strcmp(aux->projectTasks->IDTask, temTask) == 0)
			return 1;
		aux = aux->next;
	}
	return 0;
}

void createEdge()
{
    const char *src;
    edge *newVar = (edge *)malloc(sizeof(edge));
    newVar->next = NULL;
    
	vertex *aux;
    vertex *aux2;

    system("cls");

	char starT[10];
	char endT[10];
	
	printf ("------ Available Task------: \n");
	if(start == NULL){
		printf("\n [ No tasks found ]");
		getch();
		system("cls");
		menuTask();
	}else{
		showOnlyTasks();
    	printf("\nSelect start task. ");
    	scanf("%s", &starT);
    	if(taskExist(starT) == 1){
    		printf("\nSelect end task. ");
    		scanf("%s", &endT);
    		if(taskExist(endT) == 1){
    			printf("\nTask effort: ");
    			scanf("%i", &newVar->effort);
    			printf("\nAmount of time required: ");
    			scanf("%i", &newVar->time);
    			printf("\n");

    			aux = start;
    			aux2 = start;

    			while (aux2 != NULL)
    			{
        			if (strcmp(aux2->projectTasks->IDTask, endT) == 0)
        		{
            		break;
        		}
        			aux2 = aux2->next;
    			}
    			if(aux2==NULL){
    				printf("[ Warning: Task not found ]\n");
    				return;
				}
   				while (aux != NULL)
    			{
        			if (strcmp(aux->projectTasks->IDTask, starT) == 0)
        			{
            			addEdge(aux, aux2, newVar);
            			puts("\n [ Successfully registered association ]\n");
            			getch();
						system("cls");
						menuTask();   
        			}
        		aux = aux->next;
    			}
   				if(aux==NULL)
    				printf("[ Warning: Task not found ]\n");
			}
			else{
				printf("[ No tasks found ]");
				getch();
				system("cls");
				menuTask();
			}
		}else{
			printf("[ No tasks found ]");
			getch();
			system("cls");
			menuTask();
		}
	}
}

// show graph 
void showGraph()
{
	system("cls");
    vertex *aux = start;
    edge *ed;
    printf("GRAPH\n");
    printf("[ Associated tasks ]\n");
    printf("-------------------------\n");
    
    if(aux == NULL){
    	printf("[ No tasks found ]");
		getch();
		system("cls");
		menuTask();
	}else{
	
    	while (aux != NULL)
    	{
        	printf("%s--> ", aux->projectTasks->IDTask);
        	if (aux->adj != NULL)
        	{
            	ed = aux->adj;
            	while (ed != NULL)
            	{
                	printf("%s", ed->vrt->projectTasks->IDTask); 
                	printf(" %d,", ed->effort);
                	printf(" %d]  ", ed->time);
                	ed = ed->next;
            	}
        	}
        	printf("\n");
        	aux = aux->next;
    	}
    	printf("\n");
    	printf("[ ENTER ]");
    	getch();
		menuTask();
	}
}

// adding tasks 
void addTasks()
{
    system("cls");
    printf("[ Add Tasks ]");
    const char *src;
    
    int option;
    projectTasks *newTasks;
    newTasks = (projectTasks *)malloc(sizeof(projectTasks));
    insertVertex(newTasks);

    char IDTask[10];
    printf("\nID tasks:");
    fflush(stdin);
    gets(IDTask);
    
    if(taskExist(IDTask) == 1)
	{
		printf("[ Task already exists ]");
		printf("\n 1) You want to return to the main menu?: \n 2) You want to add another task?: ");
		scanf("%d", &option);
		if(option == 1)
		{
			printf("[ ENTER ]");
			getch();
		} else{
			addTasks();
		}
	}else{
    	src = IDTask;
    	char *dst1 = malloc(sizeof(char) * (strlen(src) + 1));
    	newTasks->IDTask = mystrcpy(dst1, src);


    	char description[100];
    	printf("Description:");
    	fflush(stdin);
    	gets(description);
    	src = description;
   		char *dst2 = malloc(sizeof(char) * (strlen(src) + 1));
    	newTasks->description = mystrcpy(dst2, src);
    
    	char typeTask[100];
		printf("\n-----TYPES TASKS ---- \n    1.Operational Task \n    2.Approval Task \n    3.Contract Signing \n    4.Management Task \n    5.Changes \n    TYPE: ");
    	printf("\nEnter the type of task:");
    	fflush(stdin);
    	gets(typeTask);
    	src = typeTask;
    	char *dst3 = malloc(sizeof(char) * (strlen(src) + 1));
    	newTasks->typeTask = mystrcpy(dst3, src);
    
    	char efforts[100];
    	printf("\nEffort:");
    	fflush(stdin);
    	gets(efforts);
    	src = efforts;
    	char *dst5 = malloc(sizeof(char) * (strlen(src) + 1));
    	newTasks->effort = mystrcpy(dst5, src);

    	char times[100];
    	printf("Time:");
    	fflush(stdin);
    	gets(times);
    	src = times;
    	char *dst6 = malloc(sizeof(char) * (strlen(src) + 1));
    	newTasks->time = mystrcpy(dst6, src);
    
    
    	char manager[100];
    	printf("Manager:");
    	fflush(stdin);
    	gets(manager);
    	src = manager;
    	char *dst4 = malloc(sizeof(char) * (strlen(src) + 1));
    	newTasks->manager = mystrcpy(dst4, src);
	}
    system("cls");
    printf("[ Task successfully registered ]");
    printf("[ ENTER ]");
    getch();
	menuTask();
}
// modificar tarea
void updateTasks()
{
	system("cls");
	vertex *aux;
	aux = start;
    
	int option;
	printf("Modify task information \n");
	
    if (aux == NULL){
    	printf("\n [ No tasks found ]");
    	getch();
    	system("cls");
		menuTask();
	}else{
		char key[10];
		printf("Enter the ID to modify: \n");
    	scanf("%s",&key);
    	if(taskExist(key) == 1){
    		while(aux != NULL){
				if(strcmp(aux->projectTasks->IDTask, key) == 0){
					while(option != 6){
						system("cls");
						printf("You want to modify: \n 1)Description \n 2)Type Task \n 3)Effort \n 4)Time \n 5)Manager \n 6) SALIR/n");
						scanf("%d", &option);
						if(option == 1){
							printf("Current description: %s\n",aux->projectTasks->description);
							puts("Enter new description: ");
							scanf("%s",aux->projectTasks->description);	
							puts(" Correctly Modified ]");
							getch();
							} else if( option == 2){
							printf("Current Type: %s\n",aux->projectTasks->typeTask);
							puts("Enter new type: ");
							scanf("%s",aux->projectTasks->typeTask);	
							puts(" Correctly Modified ]");
							getch();				
						}else if( option == 3){
							printf("Current Effort: %s\n",aux->projectTasks->effort);
							puts("Enter new effort: ");
							scanf("%s",aux->projectTasks->typeTask);	
							puts(" Correctly Modified ]");
							getch();
						}else if( option == 4){
							printf("Current Time: %s\n",aux->projectTasks->time);
							puts("Enter new time: ");
							scanf("%s",aux->projectTasks->time);	
							puts(" Correctly Modified ]");
							getch();
						}else if( option == 5){
							printf("Current manager: %s\n",aux->projectTasks->manager);
							puts("Enter new manager: ");
							scanf("%s",aux->projectTasks->manager);	
							puts("[ Correctly Modified ]");
							getch();
						}
						else if(option == 6){
							printf("[ ENTER ]");
							menuTask();
						}
					}
					aux = aux->next;
				}
				else {
					aux = aux->next;
				}
        
			}
   		}else{
   				printf("[ No tasks found ]");
				getch();
				system("cls");
				menuTask();
		   }
	}
}
// ver información de tarea 
void showCompleteInformationTasks()
{
    system("cls");
	vertex *aux = start;
    printf("Tasks Information \n");
    printf("-------------------\n");
    if(aux == NULL){
    	printf("\n [ No tasks found ]");
    	getch();
    	system("cls");
    	menuTask();
	}else 
	{
    	while (aux != NULL)
    	{
        	printf("ID: %s", aux->projectTasks->IDTask);
        	printf("\nDescription: %s", aux->projectTasks->description);
    		printf("\nType task: %s", aux->projectTasks->typeTask);
    		printf("\nEffort: %s", aux->projectTasks->effort);
    		printf("\nTime: %s", aux->projectTasks->time);
    		printf("\nManager: %s \n", aux->projectTasks->manager);
        	printf("\n");
        	aux = aux->next;
    	}
    	printf("\n");
    	printf("[ ENTER ]");
    	getch();
    	menuTask();
	}
}

void insertPile(vertex* aux)
{
	
	projectTasksList *newVar=(projectTasksList*)malloc(sizeof(projectTasksList));
	newVar->projectTasks = aux->projectTasks;
	newVar->next = NULL;
	if(str == NULL)
	{
		str = newVar;
		end = newVar;
	}else
	{
	   newVar->next = str;
	   str = newVar;    	
	}
}

projectTasks *desencolar()
{
	projectTasksList  *aux;
	if(str == NULL)
	{
		return NULL;
	}else
	{
		aux = str ;
		str = str->next;
		aux->next=NULL;
		if(str == NULL)
			end = NULL;
	}
	projectTasks *result = aux->projectTasks;
	free(aux);
	return result;
}

void restart(){
	
	if(start != NULL)
	{
		vertex *aux = start;
		while(aux!=NULL){
			aux->visited =aux->finished=0;
		    aux=aux->next;
		}
	}
}

/* 
Entradas tarea inicial(char), tarea final(char)
salidas 
restricciones 
*/
void dijkstra(){
	
	system("cls");
	vertex *aux = start;
	char ini[10];
	char fin[10];
	fflush(stdin);
	
	printf("Select start task: ");
	scanf("%s \n", &ini);
	if(taskExist(ini) == 1){
		printf("Select end task: ");
		scanf("%s \n", &fin);
		if(taskExist(fin) == 1){
			while(aux != NULL)
			{
				if(strcmp(aux->projectTasks->IDTask, ini) == 0)
				{
					
					aux->finished = 1;
					aux->amount = 0;
					break;
				}
				aux = aux->next;
			}		
			if(aux->adj == NULL)
			{
				printf("[ No tasks found ]");
				getch();
				return;
			}
			while(aux != NULL)
			{
				edge *a = aux->adj;
	    		while(a != NULL)
				{
		    		if(a->vrt->amount == -1 || (aux->amount + a->effort) < a->vrt->amount)
					{
		    			a->vrt->amount = aux->amount + a->effort;
		        		a->vrt->previous = aux->projectTasks->IDTask;
					}
		    		a = a->next;
	    		}
	    		aux = start;
	    		vertex *min = start;
	    		while(min->previous == 0 || min->finished ==1)
				min = min->next;
	    		while(aux != NULL)
				{
	    			if(aux->amount < min->amount && aux->finished == 0 && aux->previous != 0)
					min = aux;
	    			aux = aux->next;
				}
				aux = min;
				aux->finished = 1;
				if(strcmp(aux->projectTasks->IDTask, fin) == 0)
					break;
			}
			while(aux->previous != 0)
			{
				insertPile(aux);
				char *temp = aux->previous;
				aux = start;
				while(aux->projectTasks->IDTask != temp)
				{
		  			aux=aux->next;	
				}
			}
			insertPile(aux);
			while(str != NULL){
		
				printf("[%s] ",desencolar()->IDTask);
			}
				printf("\n");
			restart();
		}else{
			printf("[ No tasks found ]");
			getch();
			system("cls");
			funcionMenu();
		}
	}else{
		printf("[ No tasks found ]");
		getch();
		system("cls");
		funcionMenu();
	}
}
//------------------------------------------------------ TREE ------------------------------------------------------
struct treeNode *search(struct treeNode *root, int x)
{
    if (root == NULL)
    {
        return;
    }
    if (root->key == x)
    {
        return root;
    }
    else if (x > root->key)
    {
        return search(root->right, x);
    }
    else
    {
        return search(root->left, x);
    }
}

struct treeNode *newNode(int x, struct documents *documents)
{
    struct treeNode *p = malloc(sizeof(struct treeNode));
    p->key = x;
    p->documents = documents;
    p->left = p->right = NULL;

    return p;
}

struct treeNode *insert(struct treeNode *root, int x, struct documents *documents)
{
    if (root == NULL)
        return newNode(x, documents);
    if(x < root->key)
    	root->left = insert(root->left, x, documents);
    else
        root->right = insert(root->right, x, documents);

    return root;   	
}

void addDocument(treeNode *treeRoot){
	
	system("cls");
    printf("[Add Document]");
    const char *src;
    documents *newDocument;
    newDocument = (documents *)malloc(sizeof(documents));
    
    char IdTask[10];
    printf("\nID tasks:");
    fflush(stdin);
    gets(IdTask);
    
    if(taskExist(IdTask) == 1)
	{
    	src = IdTask;
    	char *dst = malloc(sizeof(char) * (strlen(src) + 1));
    	newDocument->IDTask = mystrcpy(dst, src);
    	
    	int *ID;
    	printf("\nID Document:");
    	scanf("%d", &ID);
    	fflush(stdin);
    	newDocument->IDocumen = ID;
    	
    	char filePath[100];
    	printf("File path:");
    	fflush(stdin);
    	gets(filePath);
    	src = filePath;
   		char *dst1 = malloc(sizeof(char) * (strlen(src) + 1));
    	newDocument->filePath = mystrcpy(dst1, src);
    	
    	char description[100];
    	printf("Description:");
    	fflush(stdin);
    	gets(description);
    	src = description;
   		char *dst2 = malloc(sizeof(char) * (strlen(src) + 1));
    	newDocument->description = mystrcpy(dst2, src);
    	
		char type[100];
    	printf("Type:");
    	fflush(stdin);
    	gets(type);
    	src = type;
   		char *dst3 = malloc(sizeof(char) * (strlen(src) + 1));
    	newDocument->typeD = mystrcpy(dst3, src);
    	
    	newDocument->deletable = 0;
    	
    	treeRoot = insert(treeRoot, newDocument->IDocumen, newDocument);

    }else{
    	system("cls");
    	printf("[ No documents found ]");
		getch();
		menuDocuments(treeRoot);	
	}
	    	
	system("cls");
    printf("[ Document added successfully ]");
    getch();
    menuDocuments(treeRoot);
    	
}
void showDocument(treeNode *treeNode)
{
    printf("\nID Tasks :%s", treeNode->documents->IDTask);
	printf("\nID Document:%d", treeNode->documents->IDocumen);
    printf("\nDescription:%s", treeNode->documents->description);
    printf("\nFile path :%s", treeNode->documents->filePath);
    printf("\nType document:%s\n", treeNode->documents->typeD);
    getch();
}

void inOrder(struct treeNode *root)
{
    if (root != NULL)
    {
        inOrder(root->left);
        showDocument(root);
        inOrder(root->right);
    }
}
struct node *minValueNode(struct node *node)
{
    struct treeNode *current = node;

    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

struct treeNode *deleteNode(struct treeNode *root, int key)
{
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);

    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    else
    {
        if (root->left == NULL)
        {
            struct treeNode *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct treeNode *temp = root->left;
            free(root);
            return temp;
        }

        struct treeNode *temp = minValueNode(root->right);

        root->key = temp->key;

        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

void deleteDocument(treeNode *treeRoot)
{
    if (treeRoot == NULL)
    {
        system("cls");
        printf("[ No documents to delete ]");
        menuDocuments(treeRoot);
    }
    else
    {
        system("cls");
        printf("[ Delete Document ]\n");

        int key;
        printf("Document's key:");
        scanf("%d", &key);

        if (search(treeRoot, key) == NULL)
        {
            system("cls");
            printf("[ The document code wasn't found in the records ]");
            menuDocuments(treeRoot);
        }
        else
        {
            if (search(treeRoot, key)->documents->deletable == 1)
            {
                system("cls");
                printf("[ Error: the document is being used ]");
                menuDocuments(treeRoot);
            }

            treeRoot = deleteNode(treeRoot, key);
            system("cls");
            printf("[ Document deleted successfully ]");
            system("cls");
            menuDocuments(treeRoot);
        }
    }
}
void updateDocument(treeNode *treeRoot)
{
    if (treeRoot == NULL)
    {
        system("cls");
        printf("[ No documents to update ]");
        system("cls");
        menuDocuments(treeRoot);
    }
    else
    {
        system("cls");
        printf("[ Update Document ]\n");
        int key;
        printf("Document's key:");
        scanf("%d", &key);

        if (search(treeRoot, key) == NULL)
        {
            system("cls");
            printf("[ The document code wasn't found in the records ]");
            menuDocuments(treeRoot);
        }
        else
        {
            documents *s;
            s = search(treeRoot, key)->key;
            system("cls");
            printf("-------------------\n");
            int opt;
            printf("Property to change:\n1.File Path \n2.Description \n3.Type document \n4.Go back\n");
            scanf("%d", &opt);
            documents *auxDocument;
            auxDocument = search(treeRoot, key)->documents;
			
			switch( opt ){
				case 1:
					printf("Current file Path: %s\n",auxDocument->filePath);
					puts("Enter new file Path: ");
					scanf("%s",auxDocument->filePath);	
					puts(" Correctly Modified ]");
					menuDocuments(treeRoot);    
					break;				
				case 2:
					printf("Current description: %s\n",auxDocument->description);
					puts("Enter new description: ");
					scanf("%s",auxDocument->description);	
					puts(" Correctly Modified ]");
					menuDocuments(treeRoot);      			
					break;				
					
				case 3:
					printf("Current Type: %s\n",auxDocument->typeD);
					puts("Enter new typen: ");
					scanf("%s",auxDocument->typeD);	
					puts(" Correctly Modified ]");
					menuDocuments(treeRoot);	
				case 4: 
					menuDocuments(treeRoot);
					break;
				default:
					system("cls");
					printf("\n[ Invalid input ]\n");
					updateDocument(treeRoot);	
			} 
        }
    }
}

//------------------------------------------------------ files ------------------------------------------------------

void insertTaskToList(char *phrase)
{
    // TOKEN DELIMITATOR
    char delimiter[] = ";";

    // FIRST CUT
    char *token = strtok(phrase, delimiter);

    // CREATE A VEHICLE
    projectTasks *newTask;
    newTask = (projectTasks *)malloc(sizeof(projectTasks));

    const char *src;

    // GIVE PROPERTIES
    src = token;
    char *dst = malloc(sizeof(char) * (strlen(src) + 1));
    newTask->IDTask = mystrcpy(dst, src);

    token = strtok(NULL, delimiter);
    src = token;
    char *dst2 = malloc(sizeof(char) * (strlen(src) + 1));
    newTask->description = mystrcpy(dst2, src);

    token = strtok(NULL, delimiter);
    src = token;
    char *dst3 = malloc(sizeof(char) * (strlen(src) + 1));
    newTask->typeTask = mystrcpy(dst3, src);

    token = strtok(NULL, delimiter);
    src = token;
    char *dst4 = malloc(sizeof(char) * (strlen(src) + 1));
    newTask->effort = mystrcpy(dst4, src);

    token = strtok(NULL, delimiter);
    src = token;
    char *dst5 = malloc(sizeof(char) * (strlen(src) + 1));
    newTask->time = mystrcpy(dst5, src);

    token = strtok(NULL, delimiter);
    src = token;
    char *dst6 = malloc(sizeof(char) * (strlen(src) + 1));
    newTask->manager = mystrcpy(dst6, src);

    token = strtok(NULL, delimiter);
    src = token;
    

    vertex *novus = (vertex *)malloc(sizeof(vertex));
    vertex *aux, *n;
    
    
    novus->projectTasks = newTask;
    
	novus->next = NULL;
    
    if(start == NULL)
	{
    	start = novus;
    	
	}else{
		aux  = start;
		while(aux->next != NULL){
			
			aux = aux->next;
		}
		aux->next = novus;
	}
}

void uploadFilesTasks()
{
    char fileName[] = "tasks.txt";

    FILE *pEnt = fopen(fileName, "r");

    if (pEnt == NULL)
    {
        printf("Problem with opening the %s file. Terminate the program.\n", fileName);
        exit(-1);
    }

    char lineTask[1000];

    while (fgets(lineTask, sizeof(lineTask), pEnt))
    {
        insertTaskToList(lineTask);
    }

    fclose(pEnt);
}

int sizeOfTaskList()
{
    int counter = 0;
    vertex *aux;
    for (aux = start; aux != NULL; aux = aux->next)
    {
        counter++;
    }
    return counter;
}

void saveListOfTasksInFiles()
{
    char line[1000] = "";

    FILE *file;
    file = fopen("tasks.txt", "w");
    int counter = 0;

    vertex *aux;

    for (aux = start; aux != NULL; aux = aux->next)
    {
        if (counter != 0)
        {
            strcat(line, "\n");
        }

        strcat(line, aux->projectTasks->IDTask);
        strcat(line, ";");

        strcat(line, aux->projectTasks->description);
        strcat(line, ";");

        strcat(line, aux->projectTasks->typeTask);
        strcat(line, ";");

        strcat(line, aux->projectTasks->effort);
        strcat(line, ";");

        strcat(line, aux->projectTasks->time);
        strcat(line, ";");

        strcat(line, aux->projectTasks->manager);
        strcat(line, ";");

        if (counter < sizeOfTaskList() && !isalpha(line[strlen(line) - 1]))
        {
            line[strlen(line) - 1] = '\0';
        }
        counter++;
    }
    fprintf(file, line);
    fclose(file);
}

//------------------------------------------------------ MENUS ------------------------------------------------------

int funcionMenu(treeNode *treeRoot){
	
    listResources *Ltr;
    Ltr = listNew();
	int option;
    int opt;
    
	
	
	uploadFilesTasks();
	
	do
    {
        // Menú
        system("cls");
    	printf("\n1) Tasks");
		printf("\n2) Documents");
		printf("\n3) Resources: ");
		printf("\n4) Tree of tasks "); // arbol de expansión mínima
		printf("\n5) Recommend critical route "); // Dijkstra
		printf("\n6) EXIT y guardar \n");
		scanf("%d", &option);


        switch ( option )
        {			
            case 1:
            	menuTask(treeRoot);
            	break;
					
            case 2: 
            	menuDocuments(treeRoot);
				break;
				
            case 3:
            	system("cls");
            	printf("\n 1) You want to add a resource \n 2) View all resources    ");
    			scanf("\n %d", &opt);
				if(opt == 1){
					addResources(Ltr);
				}else if(opt == 2){
					showResources(Ltr);
				}
                break;
                
            case 4: 
            	break;
            
			case 5:
				dijkstra();
            	break;
            
			case 6:
				saveListOfTasksInFiles();
    	}
    } while ( option != 6 );

    return 0;
}
int menuTask(treeNode *treeRoot){
	
	int option;
	
	system("cls");
    printf("\n1) Add task"); // agregar vertice 
	printf("\n2) Associate tasks "); // agregar arista
	printf("\n3) Show task association "); // listas de adyacencia / grafo
	printf("\n4) Show complete task information "); // información de las tareas 
	printf("\n5) Modify information tasks "); // modificar tarea
	printf("\n6) Go back \n");
	scanf("%i", &option);
		
	switch ( option )
	{ 
		case 1:
			addTasks();
			break;
				
		case 2:
			createEdge();
			break;
				
		case 3:
			showGraph();
			break;
				
		case 4:
			showCompleteInformationTasks();
			break;
				
		case 5:
			updateTasks();
			break;
				
		case 6:
			funcionMenu(treeRoot);
			break;
		
		default: 
			system("cls");
			printf("[ Invalid Input ]");
			menuTask(treeRoot);
			break;
	}
}


int menuDocuments(treeNode *treeRoot){
	
	int option;
	
	system("cls");
    printf("\n1) Add document");
	printf("\n2) Show document"); 
	printf("\n3) Delete Document"); 
	printf("\n4) Modify document information");  
	printf("\n5) Exit");
	scanf("%i", &option);
		
	switch ( option )
	{ 
		case 1:
			addDocument(treeRoot);
			break;
				
		case 2:
			inOrder(treeRoot);
			break;
				
		case 3: 
			deleteDocument(treeRoot);
			break;
				
		case 4:
			updateDocument(treeRoot);
			break;
				
		case 5:
			funcionMenu(treeRoot);
			break;
			
		default: 
			system("cls");
			printf("[ Invalid Input ]");
			menuDocuments(treeRoot);
			break;
		}
}


int main(){
	
	struct treeNode *root = NULL;
	funcionMenu( root);
}



