#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#define max 150
//Estructura.
typedef struct nodo{
    char *titulo;
    char *artista;
    char *album;
    int num_id;
    struct nodo *next;
    struct nodo* prev;
}song;
//Prototipos
int menu();
void insertar(song**);
void insertarPrincipio(song**,int);
void insertarFinal(song**,int);
void insertarDespues(song**,int);
song* seek(song**);
void destroy(song**);
void delSong(song**);
bool isempty(song**);
void desplegar(song*);
char* getdata(char*);
void displayScope(song*);

int main(){
    song *head = NULL; //Inicial.
    song *found = NULL; //Encontrado.
    bool ToF=true;
    int opc;
    setlocale(LC_ALL,"");
    while (ToF==true){
        opc = menu();
        system("cls");
        switch (opc){
        case 1: //Insertar.
            insertar(&head);
            break;
        case 2:{ //Buscar.
            if(isempty(&head)){
                   printf("\t\t¡La lista de reproducción esta vacia!\n\t\tDeberias agregar algunas canciones.\n");
                } else{
                        found = seek(&head);
                        if(found != NULL){
                                printf("¡Encontrado! La canción con el ID = %d es:\n",found->num_id);
                                displayScope(found); //Utilizamos otra función para desplegar el único elemento asi como el elemento anterior y el siguiende de este.
                        }
                    }
            }
            break;
        case 3:{ //Eliminar.
            if(isempty(&head)){
                printf("\t\t¡La lista de reproducción esta vacia!\n\t\tDeberias agregar algunas canciones.\n");
            }else{
                    delSong(&head);
                }
            }
            break;
        case 4: //Imprimir.
            if(isempty(&head)){
                printf("\t\t¡La lista de reproducción esta vacia!\n\t\tDeberias agregar algunas canciones.\n");
            } else{
                desplegar(head);
                }
            break;
        case 5: //Salir.
            ToF = false;
            printf("¡Gracias por participar!\n");
            break;
        }
    }
    free(head);
    return 0;
}

int menu(){
    int opc=0;
    while (opc==0){
        printf("Elija una opción:\n");
        printf("\t1.Para insertar una canción en la lista de reproducción.\n");
        printf("\t2.Para buscar una canción en la lista de reproducción.\n");
        printf("\t3.Para eliminar una canción en la lista de reproducción.\n");
        printf("\t4.Para desplegar la lista de reproducción.\n");
        printf("\t5.Para salir.\n");
        scanf("%d",&opc);
        getchar();
        if(opc<1 || opc>5){
            system("cls");
            printf("Opción no valida. Asegurece de digitar la opción correctamente.\n");
            opc = 0;
        }
    }
    return opc;
}

bool isempty(song **head){
    return *head == NULL; //true or false.
}

char* getdata(char*dato){
    char* nombre;
    nombre = (char*) malloc(max*sizeof(char));
    if(nombre !=NULL){
        printf("Introduzca el nombre %s: \n",dato);
        gets(nombre);
    } else{
            printf("No se puede insertar. Memoria insuficiente.\n");
        }
    return nombre;
}

void insertar(song** head){ //Apuntador doble. Se trata de una referencia a head.
    int opc = 0;
    static int ID = 1;
    while(opc == 0){
        printf("Elija una opción:\n");
        printf("\t1.Para insertar una canción al principio de lista de reproducción.\n");
        printf("\t2.Para insertar una canción al final de lista de reproducción.\n");
        printf("\t3.Para insertar una canción  despues de otra en lista de reproducción.\n"); //Permanente.
        scanf("%d",&opc);
        getchar();
        if(opc<1 || opc>3){
            system("cls");
            printf("Opción no valida. Asegurece de digitar la opción correctamente.\n");
            opc = 0;
        }
    }
    switch (opc){
        case 1:
            insertarPrincipio(head, ID);
            ID++;
            break;
        case 2:
            insertarFinal(head,ID);
            ID++;
            break;
        case 3:
            insertarDespues(head,ID);
            ID++;
            break;
        }
}

void desplegar(song* head){
    song *aux = head;
    if(head !=NULL){
        do{
            printf("ID: %d\n",aux->num_id);
            printf("\tNombre de la canción: %s\n",aux->titulo);
            printf("\tNombre del album: %s\n",aux->album);
            printf("\tNombre del artista: %s\n",aux->artista);
            printf("***********************\n");
            aux = aux->next;
        } while (aux != head);
    } else{
        printf("La lista de reproducción esta vacia.\n");
        }
}


song* seek(song** head){
    /*Por fines didacticos asumiremos que no existe una canción con el mismo ID
    pese a que no exite tal reestricción en las playlist actuales.*/
    song* actual;
    actual = *head;
    int look_ID;
    printf("Introduzca la ID númerica de la canción a buscar:\n");
    scanf("%d",&look_ID);
    printf("Buscando ID %d...\n",look_ID);
    while(actual->num_id !=look_ID){
        if(actual->next == *head){ //Si volvemos al comienzo de la lista podemos asegurar que no existe tal ID.
            printf("La canción con ID %d no se encuentra en la lista de reproducción.\n",look_ID);
            return NULL;
        } else{
                actual = actual->next;
            }
    }
    return actual;
}
void displayScope(song* found){
    song* aux = found;
    song *prev1 = found->prev;
    song *next1 = found->next;
    printf("\tNombre de la canción: %s\n",aux->titulo);
    printf("\tNombre del album: %s\n",aux->album);
    printf("\tNombre del artista: %s\n",aux->artista);
    printf("Datos de la siguiente canción:\n");
    printf("\tNombre de la canción: %s\n",next1->titulo);
    printf("\tNombre del album: %s\n",next1->album);
    printf("\tNombre del artista: %s\n",next1->artista);
    printf("Datos de la canción anterior:\n");
    printf("\tNombre de la canción: %s\n",prev1->titulo);
    printf("\tNombre del album: %s\n",prev1->album);
    printf("\tNombre del artista: %s\n",prev1->artista);
}

void insertarFinal(song**start, int id){
    song* nuevo = malloc(sizeof(song));
    song* last;
    if(nuevo != NULL){
        nuevo->album = getdata("del album");
        nuevo->artista = getdata("del artista");
        nuevo->titulo = getdata("de la canción");
        nuevo->num_id = id;
        if(*start == NULL){ //Si la lita esta vacia.
           nuevo->prev = nuevo;
           nuevo ->next = nuevo;
           *start = nuevo;
           return;
        }
       last = (*start)->prev; //Última canción.
       nuevo->next = *start;
       (*start)->prev = nuevo;
       nuevo->prev = last;
       last->next = nuevo;
    } else {
            printf("Memoria insuficiente.\n");
        }
}

void insertarPrincipio(song**start, int id){
    song* nuevo = malloc(sizeof(song));
    song* last;
    if (nuevo != NULL){
        nuevo->album = getdata("del album");
        nuevo->artista = getdata("del artista");
        nuevo->titulo = getdata("de la canción");
        nuevo->num_id = id;
        if(*start == NULL){ //Si la lita esta vacia.
           nuevo->prev = nuevo;
           nuevo ->next = nuevo;
           *start = nuevo;
           return;
        }
        last = (*start)->prev;
        nuevo->next = *start;
        nuevo->prev = last;
        last->next = nuevo;
        *start = nuevo;
    } else{
           printf("Memoria insuficiente.\n");
        }
}

void insertarDespues(song** start, int id){
    song* found;
    song* next;
    if(isempty(start)){
        printf("!La lista de reproducción esta vacia!\n");
        return;
    }
    found = seek(start);
    getchar();
    if(found == NULL){
        return;
    }
    song *nuevo = malloc(sizeof(song));
    if(nuevo != NULL){
        printf("!Encontrado! El id de la canción es: %d.\n Introduzca los datos de la siguiente canción:\n",found->num_id);
        nuevo->album = getdata("del album");
        nuevo->artista = getdata("del artista");
        nuevo->titulo = getdata("de la canción");
        nuevo->num_id = id;
        next = found->next;
        found->next = nuevo;
        nuevo->prev = found;
        nuevo->next = next;
        next->prev = nuevo;
    } else{
        printf("Memoria insuficiente.\n");
        }
}
void delSong(song** head){
    song* del = seek(head);
    song *prev1;
    int nodo_ID;
    if(del == NULL){
        printf("¡La canción a eliminar no existe!\n");
        return;
    }
    nodo_ID = del->num_id;
    prev1 = del;
    del = del->next;
    if(*head == del && del->next == *head){ //Si solo hay un elemento en la lista.
        *head = NULL;
        printf("El elemento con ID %d ha sido eliminado.\n",nodo_ID);
        free(del);
        return;
    }
    if(*head == del){ //Si la canción a eliminar es la primera:
        *head = del->next;
        del->prev->next = *head;
        (*head)->prev = del->prev;
        printf("El elemento con ID %d ha sido eliminado.\n",nodo_ID);
        free(del);
        return;
    }
    if((*head)->prev == del){ //Si la canción a eliminar es la ultima.
        (*head)->prev = del->prev;
        del->prev->next = *head;
        printf("El elemento con ID %d ha sido eliminado.\n",nodo_ID);
        free(del);
        return;
    } //Ninguno de los anteriores.
    del->next->prev = del->prev;
    del->prev->next = del->next;
    printf("El elemento con ID %d ha sido eliminado.\n",nodo_ID);
    free(del);
}

